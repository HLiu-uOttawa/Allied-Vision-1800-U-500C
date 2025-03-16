/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#ifndef EVENTHANDLING_H
#define EVENTHANDLING_H

#include <VmbCPP/VmbCPP.h>

namespace VmbCPP {
namespace Examples {

class EventHandling
{
public:
    /**
     * \brief Demonstrate the camera event functionality of VmbCPP
     */
    void CameraEventDemo(std::string cameraID);

private:
    /**
     * \brief Helper function to activate camera event notifications
     */
    VmbErrorType ActivateNotification();

    /**
     * \brief Helper function to create and register a feature observer
     */
    VmbErrorType RegisterEventObserver();

    CameraPtr m_Camera = CameraPtr();
    static const VmbInt32_t k_AquisitionTimeout = 2000;
};

} // namespace Examples
} // namespace VmbCPP

#endif // EVENTHANDLING_H