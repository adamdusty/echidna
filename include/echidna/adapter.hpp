#pragma once

#include "echidna/chained.hpp"
#include "echidna/device.hpp"
#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/limits.hpp"
#include "echidna/macros.hpp"
#include "echidna/surface.hpp"
#include <cstdint>
#include <iostream>
#include <utility>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT adapter {
    HANDLE_IMPL(adapter, WGPUAdapter)
    ~adapter() {
        if(_handle != nullptr) {
            wgpuAdapterRelease(_handle);
        }
    }

    auto limits() const -> WGPUSupportedLimits;
    auto properties() const -> WGPUAdapterProperties;
    auto features() const -> std::vector<feature_name>;
    auto has_feature(feature_name feature) const -> bool;
    auto request_device(const WGPUDeviceDescriptor& desc) const -> device;
};

constexpr auto adapter_options(
    const surface& surf,
    backend_type backend  = backend_type::undefined,
    power_preference pref = power_preference::undefined,
    bool force_fallback   = false
) {
    return WGPURequestAdapterOptions{
        .nextInChain          = nullptr,
        .compatibleSurface    = surf,
        .powerPreference      = static_cast<WGPUPowerPreference>(pref),
        .backendType          = static_cast<WGPUBackendType>(backend),
        .forceFallbackAdapter = static_cast<WGPUBool>(force_fallback),
    };
}

} // namespace echidna