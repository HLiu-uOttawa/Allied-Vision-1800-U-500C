/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#include "AcquisitionHelperChunk.h"

#include <exception>
#include <iostream>

int main()
{
    std::cout << "///////////////////////////////////\n";
    std::cout << "/// VmbCPP Chunk Access Example ///\n";
    std::cout << "///////////////////////////////////\n\n";

    try
    {
        VmbCPP::Examples::AcquisitionHelperChunk acquisitionHelper;

        acquisitionHelper.EnableChunk();
        acquisitionHelper.Start();

        std::cout << "Press <enter> to stop acquisition...\n";
        getchar();
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
    // AcquisitionHelperChunk's destructor will stop the acquisition and shutdown the VmbCPP API
}
