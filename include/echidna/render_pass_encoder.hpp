#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT render_pass_encoder {
    HANDLE_IMPL(render_pass_encoder, WGPURenderPassEncoder)
    ~render_pass_encoder() {
        if(_handle != nullptr) {
            wgpuRenderPassEncoderRelease(_handle);
        }
    }
};

} // namespace echidna