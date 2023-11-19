#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT pipeline_layout {
    HANDLE_IMPL(pipeline_layout, WGPUPipelineLayout)
    ~pipeline_layout() {
        if(_handle != nullptr) {
            wgpuPipelineLayoutRelease(_handle);
        }
    }
};

} // namespace echidna