#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT command_buffer : public handle_base<command_buffer, WGPUCommandBuffer> {
    friend handle_base<command_buffer, WGPUCommandBuffer>;
    static auto release(WGPUCommandBuffer handle) { wgpuCommandBufferRelease(handle); }
    static auto reference(WGPUCommandBuffer handle) { wgpuCommandBufferReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu