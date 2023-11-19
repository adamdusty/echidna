#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT command_buffer {
    HANDLE_IMPL(command_buffer, WGPUCommandBuffer)
    ~command_buffer() {
        if(_handle != nullptr) {
            wgpuCommandBufferRelease(_handle);
        }
    }
};

} // namespace echidna