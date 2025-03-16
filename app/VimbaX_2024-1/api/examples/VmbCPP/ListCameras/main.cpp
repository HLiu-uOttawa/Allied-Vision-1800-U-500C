/*=============================================================================
  Copyright (C) 2012 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#include <iostream>

#include "ListCameras.h"

int main(int argc, char* argv[])
{
    std::cout << "\n";
    std::cout << "///////////////////////////////////\n";
    std::cout << "/// VmbCPP List Cameras Example ///\n";
    std::cout << "///////////////////////////////////\n\n";

    if (1 < argc)
    {
        std::cout << "No parameters expected. Execution will not be affected by the provided parameter(s).\n\n";
    }

    VmbCPP::Examples::ListCameras::Print();

    std::cout << "\n";
}
