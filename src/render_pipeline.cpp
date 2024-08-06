#include "echidna/webgpu/render_pipeline.hpp"

namespace echidna::webgpu {

auto render_pipeline::bind_group_layout(std::uint32_t index
) const -> echidna::webgpu::bind_group_layout {
    return wgpuRenderPipelineGetBindGroupLayout(_handle.get(), index);
}

} // namespace echidna::webgpu