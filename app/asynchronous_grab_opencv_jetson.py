import sys
import os
from typing import Optional
from queue import Queue
import cv2
from vmbpy import *
from datetime import datetime


# 定义存储目录
SAVE_DIR = "captured_images"
if not os.path.exists(SAVE_DIR):
    os.makedirs(SAVE_DIR)

# 设定 OpenCV 兼容的像素格式
opencv_display_format = PixelFormat.Bgr8


def print_preamble():
    print('///////////////////////////////////////////////////')
    print('/// VmbPy Asynchronous Grab - Save Image Mode ///')
    print('///////////////////////////////////////////////////\n')


def print_usage():
    print('Usage:')
    print('    python async_grab_save.py [camera_id]')
    print('    python async_grab_save.py [/h] [-h]')
    print()
    print('Parameters:')
    print('    camera_id   ID of the camera to use (using first camera if not specified)')
    print()


def abort(reason: str, return_code: int = 1, usage: bool = False):
    print(reason + '\n')

    if usage:
        print_usage()

    sys.exit(return_code)


def parse_args() -> Optional[str]:
    args = sys.argv[1:]
    argc = len(args)

    for arg in args:
        if arg in ('/h', '-h'):
            print_usage()
            sys.exit(0)

    if argc > 1:
        abort(reason="Invalid number of arguments. Abort.", return_code=2, usage=True)

    return None if argc == 0 else args[0]


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
        try:
            cam.ExposureAuto.set('Continuous')
        except (AttributeError, VmbFeatureError):
            pass

        try:
            cam.BalanceWhiteAuto.set('Continuous')
        except (AttributeError, VmbFeatureError):
            pass

        try:
            stream = cam.get_streams()[0]
            stream.GVSPAdjustPacketSize.run()
            while not stream.GVSPAdjustPacketSize.is_done():
                pass
        except (AttributeError, VmbFeatureError):
            pass


def setup_pixel_format(cam: Camera):
    cam_formats = cam.get_pixel_formats()
    cam_color_formats = intersect_pixel_formats(cam_formats, COLOR_PIXEL_FORMATS)
    convertible_color_formats = tuple(f for f in cam_color_formats
                                      if opencv_display_format in f.get_convertible_formats())

    cam_mono_formats = intersect_pixel_formats(cam_formats, MONO_PIXEL_FORMATS)
    convertible_mono_formats = tuple(f for f in cam_mono_formats
                                     if opencv_display_format in f.get_convertible_formats())

    if opencv_display_format in cam_formats:
        cam.set_pixel_format(opencv_display_format)
    elif convertible_color_formats:
        cam.set_pixel_format(convertible_color_formats[0])
    elif convertible_mono_formats:
        cam.set_pixel_format(convertible_mono_formats[0])
    else:
        abort('Camera does not support an OpenCV compatible format. Abort.')


class Handler:
    def __init__(self):
        self.display_queue = Queue(10)
        self.image_counter = 0  # 记录帧数，用于命名文件

    def save_image(self, image):
        timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S.%f")[:-3]

        filename = os.path.join(SAVE_DIR, f"frame_{self.image_counter:05d}_{timestamp}.png")
        cv2.imwrite(filename, image)
        print(f"Saved: {filename}")
        self.image_counter += 1

    def __call__(self, cam: Camera, stream: Stream, frame: Frame):
        if frame.get_status() == FrameStatus.Complete:
            print('{} acquired {}'.format(cam, frame), flush=True)

            if frame.get_pixel_format() == opencv_display_format:
                image = frame.as_opencv_image()
            else:
                image = frame.convert_pixel_format(opencv_display_format).as_opencv_image()

            self.save_image(image)

        cam.queue_frame(frame)


def main():
    print_preamble()
    cam_id = parse_args()

    with VmbSystem.get_instance():
        with get_camera(cam_id) as cam:
            setup_camera(cam)
            setup_pixel_format(cam)
            handler = Handler()

            try:
                cam.start_streaming(handler=handler, buffer_count=10)

                print("Streaming... Press Ctrl+C to stop.")

                while True:
                    pass  # 无限循环，保持采集

            except KeyboardInterrupt:
                print("\nStopping capture...")
            finally:
                cam.stop_streaming()


if __name__ == '__main__':
    main()
