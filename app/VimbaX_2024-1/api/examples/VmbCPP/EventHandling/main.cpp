/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#include <iostream>
#include "EventHandling.h"

int main(int argc, char* argv[])
{
    std::cout << "\n";
    std::cout << "/////////////////////////////////////\n";
    std::cout << "/// VmbCPP Event Handling Example ///\n";
    std::cout << "/////////////////////////////////////\n\n";

    if (2 < argc)
    {
        std::cout << "Usage: EventHandling [CameraID]\n\n";
        std::cout << "Parameters:   CameraID    ID of the camera to use (using first camera if not specified)\n";
    }
    else if (2 == argc)
    {
        VmbCPP::Examples::EventHandling eventHandler;
        eventHandler.CameraEventDemo(argv[1]);
    }
    else
    {
        VmbCPP::Examples::EventHandling eventHandler;
        eventHandler.CameraEventDemo("");
    }

    std::cout << "\n";
}
