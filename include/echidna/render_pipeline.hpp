#pragma once

#include "echidna/bind_group_layout.hpp"
#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT render_pipeline : public handle_base<render_pipeline, WGPURenderPipeline> {
    friend handle_base<render_pipeline, WGPURenderPipeline>;
    static auto release(WGPURenderPipeline handle) { wgpuRenderPipelineRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto bind_group_layout(std::uint32_t index) const -> bind_group_layout;
};

} // namespace echidna