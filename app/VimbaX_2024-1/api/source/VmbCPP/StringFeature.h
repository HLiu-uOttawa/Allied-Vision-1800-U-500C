/*=============================================================================
  Copyright (C) 2012-2022 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        StringFeature.h

  Description: Definition of class VmbCPP::StringFeature.
               Intended for use in the implementation of VmbCPP.

-------------------------------------------------------------------------------

  THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF TITLE,
  NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR  PURPOSE ARE
  DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, 
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED  
  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#ifndef VMBCPP_STRINGFEATURE_H
#define VMBCPP_STRINGFEATURE_H

/**
* \file        StringFeature.h
*
* \brief       Definition of class VmbCPP::StringFeature.
*              Intended for use in the implementation of VmbCPP.
*/

#include <VmbC/VmbCommonTypes.h>

#include "BaseFeature.h"

namespace VmbCPP {

class StringFeature final : public BaseFeature 
{
public:
    StringFeature(const VmbFeatureInfo& featureInfo, FeatureContainer& featureContainer);

protected:
    virtual VmbErrorType SetValue(const char *pValue) noexcept override;

    // Array functions to pass data across DLL boundaries
    virtual VmbErrorType GetValue(char * const pValue, VmbUint32_t &length) const noexcept override;
};

}  // namespace VmbCPP

#endif
