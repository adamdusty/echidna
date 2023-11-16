#pragma once

#include "echidna/chained.hpp"
#include "echidna/device.hpp"
#include "echidna/enums.hpp"
#include "echidna/limits.hpp"
#include "echidna/macros.hpp"
#include "echidna/surface.hpp"
#include <cstdint>
#include <iostream>
#include <utility>
#include <webgpu.h>

namespace echidna {

using adapter_properties      = WGPUAdapterProperties;
using adapter_features        = WGPUFeatureName;
using adapter_request_options = WGPURequestAdapterOptions;

constexpr auto adapter_options(const surface& surf,
                               power_preference pref = power_preference::undefined,
                               backend_type backend  = backend_type::undefined,
                               bool force_fallback   = false) {
    return WGPURequestAdapterOptions{
        .nextInChain          = nullptr,
        .compatibleSurface    = surf,
        .powerPreference      = static_cast<WGPUPowerPreference>(pref),
        .backendType          = static_cast<WGPUBackendType>(backend),
        .forceFallbackAdapter = static_cast<WGPUBool>(force_fallback),
    };
}

class adapter {
    HANDLE_IMPL(adapter, WGPUAdapter)

    auto limits() const -> wgpu_supported_limits;
    auto properties() const -> adapter_properties;
    auto features() const -> std::vector<feature_name>;
    auto has_feature(feature_name feature) const -> bool;
    auto request_device(const WGPUDeviceDescriptor& desc) const -> device;
};

} // namespace echidna