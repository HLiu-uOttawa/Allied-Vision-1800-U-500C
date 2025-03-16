/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

#include <VmbCPP/VmbCPP.h>
#include <VmbCPP/IFeatureObserver.h>

namespace VmbCPP {
namespace Examples {

class EventObserver : public VmbCPP::IFeatureObserver
{            
public:
    /**
    * \brief This function will be called when the observed camera feature has changed
    */
    virtual void FeatureChanged(const FeaturePtr& pFeature);
};

} // namespace Examples
} // namespace VmbCPP

#endif // EVENTOBSERVER_H