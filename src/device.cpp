#include "echidna/device.hpp"

namespace echidna {

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<wgpu_required_limits>& required_limits,
                       const WGPUQueueDescriptor& desc,
                       WGPUDeviceLostCallback callback,
                       void* user_data) -> WGPUDeviceDescriptor {
    return WGPUDeviceDescriptor{
        .nextInChain          = nullptr,
        .label                = label,
        .requiredFeatureCount = required_features.size(),
        .requiredFeatures     = reinterpret_cast<const WGPUFeatureName*>(required_features.data()),
        .requiredLimits       = reinterpret_cast<const WGPURequiredLimits*>(required_limits.data()),
        .defaultQueue         = desc,
        .deviceLostCallback   = callback,
        .deviceLostUserdata   = user_data,
    };
}

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<wgpu_required_limits>& required_limits) -> WGPUDeviceDescriptor {
    return device_descriptor(label, required_features, required_limits, queue_descriptor(), nullptr, nullptr);
}

auto device_descriptor(const char* label) -> WGPUDeviceDescriptor {
    return WGPUDeviceDescriptor{
        .nextInChain          = nullptr,
        .label                = label,
        .requiredFeatureCount = 0,
        .requiredFeatures     = nullptr,
        .requiredLimits       = nullptr,
        .defaultQueue         = queue_descriptor(),
        .deviceLostCallback   = nullptr,
        .deviceLostUserdata   = nullptr,
    };
}

} // namespace echidna