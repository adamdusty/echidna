#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT compute_pass_encoder {
    HANDLE_IMPL(compute_pass_encoder, WGPUComputePassEncoder)
    ~compute_pass_encoder() {
        if(_handle != nullptr) {
            wgpuComputePassEncoderRelease(_handle);
        }
    }
};

} // namespace echidna