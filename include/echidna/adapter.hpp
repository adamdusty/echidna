#pragma once

#include "echidna/chained.hpp"
#include "echidna/device.hpp"
#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include "echidna/limits.hpp"
#include "echidna/surface.hpp"
#include <cstdint>
#include <iostream>
#include <utility>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT adapter : public handle_base<adapter, WGPUAdapter> {
    friend handle_base<adapter, WGPUAdapter>;
    static auto release(WGPUAdapter handle) { wgpuAdapterRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

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