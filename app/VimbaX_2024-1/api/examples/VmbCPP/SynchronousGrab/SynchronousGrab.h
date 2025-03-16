/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#ifndef AVT_VMBAPI_EXAMPLES_SYNCHRONOUS_GRAB
#define AVT_VMBAPI_EXAMPLES_SYNCHRONOUS_GRAB

#include <VmbCPP/VmbCPP.h>

namespace VmbCPP {
    namespace Examples {

        class SynchronousGrab
        {
        private:
            VmbSystem& m_vmbSystem;
            CameraPtr  m_camera;
            FramePtr   frame;

        public:
            /**
             * \brief The constructor will initialize the API and open the given camera
             *
             * \param[in] pCameraId zero terminated C string with the camera id for the camera to be used
             */
            SynchronousGrab(const char* cameraId);

            /**
             * \brief The constructor will initialize the API and open the first available camera
             */
            SynchronousGrab();

            /**
             * \brief The destructor will shutdown the API
             */
            ~SynchronousGrab();

            /**
             * \brief Aquire single image.
             */
            void AcquireImage();
        };

    }
} // namespace VmbCPP

#endif
