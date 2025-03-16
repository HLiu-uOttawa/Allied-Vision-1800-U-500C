/*=============================================================================
  Copyright (C) 2013 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#include <string>
#include <cstring>
#include <iostream>

#include "SynchronousGrab.h"
#include <VmbCPP/VmbCPP.h>
#include <exception>

int main(int argc, char* argv[])
{
    std::cout << "\n";
    std::cout << "///////////////////////////////////////\n";
    std::cout << "/// VmbCPP Synchronous Grab Example ///\n";
    std::cout << "///////////////////////////////////////\n\n";

    try
    {
        VmbCPP::Examples::SynchronousGrab synchronousGrab;
        synchronousGrab.AcquireImage();
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }    

    std::cout << std::endl;
}

