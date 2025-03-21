import os, sys
import numpy as np

import cv2

import time
import multiprocessing as mp
from typing import Optional, Tuple

from vmbpy import *
from ultralytics import YOLO
from datetime import datetime

# YOLOv8 model path (initialized inside yolo_process to avoid fork issues)
YOLO_MODEL_PATH = "yolov8n.pt"
SAVE_DIR = "captured_frames"

# Camera parameters
CAM_ID = None  # Default to the first available camera
ALLOCATION_MODE = AllocationMode.AnnounceFrame
TIMEOUT_MS = 1000  # Camera timeout in milliseconds
FRAME_QUEUE_SIZE = 3  # Limit queue size to prevent excessive memory usage

def print_preamble():
    print('///////////////////////////////////////')
    print('/// Capture Frames & Save as files ////')
    print('///////////////////////////////////////\n')


def print_usage():
    print('Usage:')
    print('    python asynchronous_grab.py [/x] [-x] [camera_id]')
    print('    python asynchronous_grab.py [/h] [-h]')
    print()
    print('Parameters:')
    print('    /x, -x      If set, use AllocAndAnnounce mode of buffer allocation')
    print('    camera_id   ID of the camera to use (using first camera if not specified)')
    print()

def parse_args() -> Tuple[Optional[str], AllocationMode]:
    args = sys.argv[1:]
    argc = len(args)

    allocation_mode = AllocationMode.AnnounceFrame
    cam_id = ""
    for arg in args:
        if arg in ('/h', '-h'):
            print_usage()
            sys.exit(0)
        elif arg in ('/x', '-x'):
            allocation_mode = AllocationMode.AllocAndAnnounceFrame
        elif not cam_id:
            cam_id = arg


    return (cam_id if cam_id else None, allocation_mode)

def get_camera(camera_id: Optional[str]) -> Camera:
    """Retrieve a Vimba camera instance by ID or return the first available camera."""
    with VmbSystem.get_instance() as vmb:
        if camera_id:
            try:
                return vmb.get_camera_by_id(camera_id)
            except VmbCameraError:
                print(f"[ERROR] Failed to access Camera '{camera_id}'.")
                return None
        else:
            cams = vmb.get_all_cameras()
            if not cams:
                print("[ERROR] No cameras accessible.")
                return None
            return cams[0]


def setup_camera(cam: Camera):
    """Configure camera settings."""
    with cam:
        # Enable auto exposure
        try:
            cam.ExposureAuto.set('Continuous')
        except (AttributeError, VmbFeatureError):
            print("[Warning] Camera auto exposure not supported.")

        # Enable auto white balance
        try:
            cam.BalanceWhiteAuto.set('Continuous')
        except (AttributeError, VmbFeatureError):
            print("[Warning] Camera white balance auto not supported.")

        # Adjust GigE Vision packet size if supported
        try:
            stream = cam.get_streams()[0]
            stream.GVSPAdjustPacketSize.run()
            while not stream.GVSPAdjustPacketSize.is_done():
                pass
        except (AttributeError, VmbFeatureError):
            pass



def frame_handler_x(cam: Camera, stream: Stream, frame: Frame):

    print('{} acquired {}'.format(cam, frame), flush=True)
    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S.%f")[:-3]

    np_image = frame.as_numpy_ndarray()

    filename = os.path.join(SAVE_DIR, f"frame_{timestamp}.png")

    cv2.imwrite(filename, np_image)

    cam.queue_frame(frame)


# def vcam_process(frame_queue, stop_event):
def vcam_process():
    """Camera process: continuously captures frames and stores them in `frame_queue`."""
    cam_id, allocation_mode = parse_args()
    with VmbSystem.get_instance():
        with get_camera(cam_id) as cam:

            setup_camera(cam)
            print('Press <enter> to stop Frame acquisition.')

            try:
                # Start Streaming with a custom a buffer of 10 Frames (defaults to 5)
                cam.start_streaming(handler=frame_handler_x,
                                    buffer_count=10,
                                    allocation_mode=allocation_mode)
                # input()

            finally:
                cam.stop_streaming()


def yolo_process(frame_queue, stop_event):
    """YOLO tracking process: retrieves frames from `frame_queue` and performs tracking."""


    print("[INFO] YOLO Tracking started...")
    model = YOLO(YOLO_MODEL_PATH)  # Initialize YOLO model inside the process

    while not stop_event.is_set():
        try:
            # Retrieve the latest frame (avoiding stale frames)
            frame = frame_queue.get(timeout=1)

            # Run YOLO tracking
            model.track(source=frame, stream=True, show=True)

        except mp.queues.Empty:  # Use multiprocessing.queues.Empty
            pass  # Skip if the queue is empty

        if cv2.waitKey(1) & 0xFF == ord('q'):
            stop_event.set()  # Trigger stop event

    cv2.destroyAllWindows()
    print("[INFO] YOLO Tracking stopped.")


def main():
    """Launches virtual camera and YOLO tracking processes."""
    frame_queue = mp.Queue(maxsize=FRAME_QUEUE_SIZE)  # Shared queue for inter-process communication
    stop_event = mp.Event()  # Stop signal for all processes

    # # Start camera process
    # vcam_proc = mp.Process(target=vcam_process, args=(frame_queue, stop_event))
    # vcam_proc.start()
    # vcam_process()
    print_preamble()


    # Start YOLO tracking process
    yolo_proc = mp.Process(target=yolo_process, args=(frame_queue, stop_event))
    yolo_proc.start()

    try:
        while True:
            time.sleep(1)  # Keep the main process alive
    except KeyboardInterrupt:
        print("\n[INFO] User interrupted, stopping all processes...")
        stop_event.set()  # Trigger stop signal for all processes

    # Wait for processes to exit
    # vcam_proc.join()
    yolo_proc.join()

    cam_id, allocation_mode = parse_args()

    with VmbSystem.get_instance():
        with get_camera(cam_id) as cam:

            setup_camera(cam)
            print('Press <enter> to stop Frame acquisition.')

            try:
                # Start Streaming with a custom a buffer of 10 Frames (defaults to 5)
                # AllocationMode.AllocAndAnnounceFrame
                cam.start_streaming(handler=frame_handler_x,
                                    buffer_count=10,
                                    allocation_mode=allocation_mode)
                input()

            finally:
                cam.stop_streaming()

if __name__ == "__main__":
    # mp.set_start_method('spawn', force=True)  # Required for Windows and Linux compatibility
    main()
