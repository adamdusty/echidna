#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include <vector>
#include <webgpu.h>

namespace echidna {

// struct ECHIDNA_EXPORT device_descriptor {
//     const char* label                               = nullptr;
//     std::vector<WGPUFeatureName> required_features  = {};
//     std::vector<WGPURequiredLimits> required_limits = {};
//     WGPUQueueDescriptor queue_desc                  = {.nextInChain = nullptr, .label = nullptr};
//     WGPUDeviceLostCallback callback                 = nullptr;
//     void* user_data                                 = nullptr;

//     operator WGPUDeviceDescriptor() {
//         return WGPUDeviceDescriptor{
//             .nextInChain          = nullptr,
//             .label                = label,
//             .requiredFeatureCount = required_features.size(),
//             .requiredFeatures     = required_features.data(),
//             .requiredLimits       = required_limits.data(),
//             .defaultQueue         = queue_desc,
//             .deviceLostCallback   = callback,
//             .deviceLostUserdata   = user_data,
//         };
//     }

//     constexpr device_descriptor() = default;

//     constexpr device_descriptor(
//         const char* label,
//         std::vector<feature_name>& required_features,
//         std::vector<WGPURequiredLimits>& required_limits,
//         const WGPUQueueDescriptor& desc,
//         WGPUDeviceLostCallback callback,
//         void* user_data
//     ) :
//         label(label), queue_desc(desc), callback(callback), user_data(user_data), required_limits(required_limits) {
//         for(const auto feat: required_features) {
//             this->required_features.emplace_back(static_cast<WGPUFeatureName>(feat));
//         }
//     }

//     constexpr device_descriptor(
//         const char* label,
//         std::vector<feature_name>& required_features,
//         std::vector<WGPURequiredLimits>& required_limits
//     ) :
//         label(label), required_limits(required_limits) {
//         for(const auto feat: required_features) {
//             this->required_features.emplace_back(static_cast<WGPUFeatureName>(feat));
//         }
//     }

//     constexpr device_descriptor(const char* label) : label(label) {}
// };

} // namespace echidna