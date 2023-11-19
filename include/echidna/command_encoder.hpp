#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT command_encoder {
    HANDLE_IMPL(command_encoder, WGPUCommandEncoder)
    ~command_encoder() {
        if(_handle != nullptr) {
            wgpuCommandEncoderRelease(_handle);
        }
    }
};

} // namespace echidna