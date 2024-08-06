#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT command_buffer : public handle_base<command_buffer, WGPUCommandBufferImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu