#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT bind_group : public handle_base<bind_group, WGPUBindGroup> {
    friend handle_base<bind_group, WGPUBindGroup>;
    static auto release(WGPUBindGroup handle) { wgpuBindGroupRelease(handle); }
    static auto reference(WGPUBindGroup handle) { wgpuBindGroupReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};
} // namespace echidna::webgpu