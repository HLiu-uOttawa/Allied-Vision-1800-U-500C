import sys
from typing import Optional, Tuple

from vmbpy import *

import os
import cv2
import numpy as np

from datetime import datetime

SAVE_DIR = "captured_frames"
os.makedirs(SAVE_DIR, exist_ok=True)
frame_count = 0


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


def abort(reason: str, return_code: int = 1, usage: bool = False):
    print(reason + '\n')

    if usage:
        print_usage()

    sys.exit(return_code)


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

    if argc > 2:
        abort(reason="Invalid number of arguments. Abort.", return_code=2, usage=True)

    return (cam_id if cam_id else None, allocation_mode)


def get_camera(camera_id: Optional[str]) -> Camera:
    with VmbSystem.get_instance() as vmb:
        if camera_id:
            try:
                return vmb.get_camera_by_id(camera_id)

            except VmbCameraError:
                abort('Failed to access Camera \'{}\'. Abort.'.format(camera_id))

        else:
            cams = vmb.get_all_cameras()
            if not cams:
                abort('No Cameras accessible. Abort.')

            return cams[0]


def setup_camera(cam: Camera):
    with cam:

        # Enable auto exposure time setting if camera supports it
        try:
            cam.ExposureAuto.set('Continuous')
        except (AttributeError, VmbFeatureError):
            print("error: cam.ExposureAuto")
            pass

        # Enable white balancing if camera supports it
        try:
            cam.BalanceWhiteAuto.set('Continuous')
        except (AttributeError, VmbFeatureError):
            print("error: cam.BalanceWhiteAuto")
            pass

        # Try to adjust GeV packet size. This Feature is only available for GigE - Cameras.
        try:
            stream = cam.get_streams()[0]
            stream.GVSPAdjustPacketSize.run()

            while not stream.GVSPAdjustPacketSize.is_done():
                pass

        except (AttributeError, VmbFeatureError):
            pass


def frame_handler(cam: Camera, stream: Stream, frame: Frame):
    print('{} acquired {}'.format(cam, frame), flush=True)

    cam.queue_frame(frame)


def frame_handler_x(cam: Camera, stream: Stream, frame: Frame):
    global frame_count
    print('{} acquired {}'.format(cam, frame), flush=True)
    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S.%f")[:-3]

    np_image = frame.as_numpy_ndarray()

    filename = os.path.join(SAVE_DIR, f"frame_{frame_count:05d}_{timestamp}.png")

    cv2.imwrite(filename, np_image)
    # print(f"Frame saved: {filename}")

    frame_count += 1

    cam.queue_frame(frame)


def main():
    print_preamble()
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
                input()

            finally:
                cam.stop_streaming()


if __name__ == '__main__':
    main()
