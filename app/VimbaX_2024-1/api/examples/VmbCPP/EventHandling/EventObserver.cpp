/*=============================================================================
  Copyright (C) 2012-2023 Allied Vision Technologies.  All Rights Reserved.
  Subject to the BSD 3-Clause License.
=============================================================================*/

#include <iostream>
#include "EventObserver.h"

namespace VmbCPP {
namespace Examples {
            
void EventObserver::FeatureChanged(const FeaturePtr& feature)
{
    // Here an action can be perform based on the event that has occured
    // For example, print the event feature name and unique identifier value  
    if (feature != nullptr)
    {
        std::string featureName("");
        VmbInt64_t featureValue;

        feature->GetName(featureName);
        feature->GetValue(featureValue);

        std::cout << "\nEvent " << featureName << " occurred. Value:" << featureValue << "\n";
    }
}

} // namespace Examples
} // namespace VmbCPP