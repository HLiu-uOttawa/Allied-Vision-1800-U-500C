/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#pragma once

#include <VmbCPP/VmbCPP.h>
#include <vector>
#include <mutex>

namespace VmbCPP {
namespace Examples {

class AcquisitionHelperChunk
{
private:
    VmbSystem&                  m_vmbSystem;
    CameraPtr                   m_camera;
    std::vector<std::string>    m_chunkFeatures;

public:
    /**
     * \brief The constructor will initialize the API and open the given camera
     *
     * \param[in] cameraId  zero terminated C string with the camera id for the camera to be used
     */
    AcquisitionHelperChunk(const char* cameraId);

    /**
     * \brief The constructor will initialize the API and open the first available camera
     */
    AcquisitionHelperChunk();

    /**
     * \brief The destructor will stop the acquisition and shutdown the API
     */
    ~AcquisitionHelperChunk();

    /**
     * \brief Enable the default Chunk features
     */
    void EnableChunk();

    /**
     * \brief Start the acquisition. Chunk features of incoming frames will be printed to console.
     */
    void Start();

    /**
     * \brief Stop the acquisition
     */
    void Stop();
};

}} // namespace VmbCPP::Examples
