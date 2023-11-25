#pragma once

#include "echidna/bind_group_layout.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT render_pipeline {
    HANDLE_IMPL(render_pipeline, WGPURenderPipeline)
    ~render_pipeline() {
        if(_handle != nullptr) {
            wgpuRenderPipelineRelease(_handle);
        }
    }

    auto bind_group_layout(std::uint32_t index) const -> bind_group_layout;
};

} // namespace echidna