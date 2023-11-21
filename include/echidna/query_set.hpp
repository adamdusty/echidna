#pragma once

#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT query_set {
    HANDLE_IMPL(query_set, WGPUQuerySet)
    ~query_set() {
        if(_handle != nullptr) {
            wgpuQuerySetDestroy(_handle);
            wgpuQuerySetRelease(_handle);
        }
    }

    auto count() const -> std::uint32_t;
    auto type() const -> query_type;
};

} // namespace echidna

// WGPU_EXPORT void wgpuQuerySetDestroy(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;