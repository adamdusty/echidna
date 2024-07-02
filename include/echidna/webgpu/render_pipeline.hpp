#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group_layout.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT render_pipeline : public handle_base<render_pipeline, WGPURenderPipeline> {
    friend handle_base<render_pipeline, WGPURenderPipeline>;
    static auto release(WGPURenderPipeline handle) { wgpuRenderPipelineRelease(handle); }
    static auto reference(WGPURenderPipeline handle) { wgpuRenderPipelineReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto bind_group_layout(std::uint32_t index) const -> bind_group_layout;
};

} // namespace echidna::webgpu