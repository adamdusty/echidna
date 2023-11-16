#pragma once

#include "echidna/enums.hpp"
#include "echidna/limits.hpp"
#include "echidna/macros.hpp"
#include "echidna/queue.hpp"
#include <algorithm>
#include <vector>
#include <webgpu.h>

namespace echidna {

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<wgpu_required_limits>& required_limits,
                       const WGPUQueueDescriptor& desc,
                       WGPUDeviceLostCallback callback,
                       void* user_data) -> WGPUDeviceDescriptor;

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<wgpu_required_limits>& required_limits) -> WGPUDeviceDescriptor;

auto device_descriptor(const char* label = nullptr) -> WGPUDeviceDescriptor;

class device {
    HANDLE_IMPL(device, WGPUDevice)
};

} // namespace echidna