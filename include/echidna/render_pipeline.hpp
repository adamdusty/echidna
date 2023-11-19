#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT render_pipeline {
    HANDLE_IMPL(render_pipeline, WGPURenderPipeline)
    ~render_pipeline() {
        if(_handle != nullptr) {
            wgpuRenderPipelineRelease(_handle);
        }
    }
};

} // namespace echidna