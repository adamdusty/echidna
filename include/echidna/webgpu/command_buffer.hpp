#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT command_buffer : public handle_base<command_buffer, WGPUCommandBuffer> {
    friend handle_base<command_buffer, WGPUCommandBuffer>;
    static auto release(WGPUCommandBuffer handle) { wgpuCommandBufferRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna