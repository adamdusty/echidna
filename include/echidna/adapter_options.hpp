#pragma once

#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/surface.hpp"

namespace echidna {

// Create WGPUAdapterRequestOptions using surface
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