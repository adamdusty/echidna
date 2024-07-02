#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT query_set : public handle_base<query_set, WGPUQuerySet> {
    friend handle_base<query_set, WGPUQuerySet>;
    static auto release(WGPUQuerySet handle) { wgpuQuerySetRelease(handle); }
    static auto reference(WGPUQuerySet handle) { wgpuQuerySetReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto count() const -> std::uint32_t;
    auto type() const -> query_type;
};

} // namespace echidna::webgpu

// WGPU_EXPORT void wgpuQuerySetDestroy(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;