/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#ifndef AVT_VMBAPI_EXAMPLES_LISTCAMERAS
#define AVT_VMBAPI_EXAMPLES_LISTCAMERAS

namespace VmbCPP {
    namespace Examples {

        class ListCameras
        {
        public:
            //
            // Starts Vimba
            // Gets all connected cameras
            // And prints out information about the camera name, model name, serial number, ID and the corresponding interface ID
            //
            static void Print();
        };

    }
}

#endif
