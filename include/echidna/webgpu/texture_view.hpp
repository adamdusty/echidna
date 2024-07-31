#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT texture_view : public handle_base<texture_view, WGPUTextureView> {
    friend handle_base<texture_view, WGPUTextureView>;
    static auto release(WGPUTextureView handle) { wgpuTextureViewRelease(handle); }
    static auto reference(WGPUTextureView handle) { wgpuTextureViewReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu