#include "echidna/webgpu/compute_pipeline.hpp"

namespace echidna::webgpu {

auto compute_pipeline::bind_group_layout(std::uint32_t index
) const -> echidna::webgpu::bind_group_layout {
    return echidna::webgpu::bind_group_layout{
        wgpuComputePipelineGetBindGroupLayout(_handle.get(), index)
    };
}

} // namespace echidna::webgpu