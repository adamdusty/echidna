#pragma once

#include "echidna/webgpu/enums.hpp"
#include <webgpu.h>

namespace echidna {

/**
 * @param surf Surface that adapter is guaranteed to be compatible with
 * @param backend
 * @param pref
 * @param force_fallback Force fallback adapter, typically a software implementation.
 */
constexpr auto adapter_options(
    WGPUSurface surf      = nullptr,
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