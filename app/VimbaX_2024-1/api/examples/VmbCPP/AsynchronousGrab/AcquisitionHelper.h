/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#ifndef ASYNCHRONOUS_GRAB_H_
#define ASYNCHRONOUS_GRAB_H_

#include <VmbCPP/VmbCPP.h>

namespace VmbCPP {
namespace Examples {

class AcquisitionHelper
{
private:
    VmbSystem&  m_vmbSystem;
    CameraPtr   m_camera;

public:
    /**
     * \brief The constructor will initialize the API and open the given camera
     *
     * \param[in] pCameraId  zero terminated C string with the camera id for the camera to be used
     */
    AcquisitionHelper(const char* cameraId);

    /**
     * \brief The constructor will initialize the API and open the first available camera
     */
    AcquisitionHelper();

    /**
     * \brief The destructor will stop the acquisition and shutdown the API
     */
    ~AcquisitionHelper();

    /**
     * \brief Start the acquisition.
     */
    void Start();

    /**
     * \brief Stop the acquisition.
     */
    void Stop();
};

}} // namespace VmbCPP

#endif
