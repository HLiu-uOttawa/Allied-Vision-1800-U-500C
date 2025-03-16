/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#include <iostream>
#include "EventHandling.h"
#include "EventObserver.h"

namespace VmbCPP {
namespace Examples {

void EventHandling::CameraEventDemo(std::string cameraID)
{
    // Get a reference to the VmbSystem singleton
    VmbSystem& sys = VmbSystem::GetInstance(); 
            
    // Initialize the Vmb API
    VmbErrorType err = sys.Startup();           
    if (err == VmbErrorSuccess)
    {
        // No camera ID provided
        if (cameraID.empty())
        {
            // Vector of std::shared_ptr<AVT::VmbAPI::Camera> objects
            CameraPtrVector cameras;

            // Get a list of cameras currently connected to the system
            err = sys.GetCameras(cameras);
            if (err == VmbErrorSuccess && cameras.empty() == false)
            {
                // Use the first camera found in the list
                m_Camera = cameras[0];

                // Open the camera
                err = m_Camera->Open(VmbAccessModeFull);
            }
            else
            {
                std::cout << "Error! Could not get a list of cameras or no cameras detected. Error code: " << err << "\n";
            }
        }
        // Camera ID provided by user
        else
        {
            // Open the specified camera
            err = sys.OpenCameraByID(cameraID.c_str(), VmbAccessModeFull, m_Camera);   
        }

        if (err == VmbErrorSuccess && m_Camera != nullptr)
        {
            // Activate the notification for the desired camera event
            err = ActivateNotification();
            if (err == VmbErrorSuccess)
            {
                // Register the event callback 
                err = RegisterEventObserver();
                if (err == VmbErrorSuccess)
                {
                    // Trigger the event
                    std::cout << "Acquiring image to trigger event...\n";
                    FramePtr pFrame;
                    m_Camera->AcquireSingleImage(pFrame, k_AquisitionTimeout);
                }
            }
        }
        else
        {
            std::cout << "Could not open camera or no camera available. Error code: " << err << "\n";
        }
        

        // Close Vmb API
        sys.Shutdown();         
    }
}


VmbErrorType EventHandling::ActivateNotification()
{
    std::cout << "Activating notifications for 'AcquisitionStart' events.\n";

    // EventSelector is used to specify the particular Event to control
    FeaturePtr feature;
    VmbErrorType err = m_Camera->GetFeatureByName("EventSelector", feature);

    if (err == VmbErrorSuccess)
    {
        // Configure the AcquisitionStart camera event. 
        err = feature->SetValue("AcquisitionStart");
        if (err == VmbErrorSuccess)
        {
            // EventNotification is used to enable/disable the notification of the event specified by EventSelector.
            err = m_Camera->GetFeatureByName("EventNotification", feature);
            if (err == VmbErrorSuccess)
            {
                err = feature->SetValue("On");
            }
        }
    }

    return err;
}


VmbErrorType EventHandling::RegisterEventObserver()
{
    std::cout << "Registering observer for 'EventAcquisitionStart' feature.\n";

    // Each of the events listed in the EventSelector enumeration will have a corresponding event identifier feature. 
    // This feature will be used as a unique identifier of the event to register the callback function. 
    FeaturePtr pFeature;
    VmbErrorType err = m_Camera->GetFeatureByName("EventAcquisitionStart", pFeature);

    if (err == VmbErrorSuccess)
    {
        // register a callback function to be notified that the event happened
        err = pFeature->RegisterObserver(IFeatureObserverPtr(new EventObserver()));

        if (err != VmbErrorSuccess)
        {
            std::cout << "Could not register observer. Error code: " << err << "\n";
        }
    }

    return err;
}

} // namespace Examples
} // namespace VmbCPP

