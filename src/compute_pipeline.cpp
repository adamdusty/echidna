#include "echidna/compute_pipeline.hpp"

namespace echidna {

auto compute_pipeline::bind_group_layout(std::uint32_t index) const -> echidna::bind_group_layout {
    return echidna::bind_group_layout{wgpuComputePipelineGetBindGroupLayout(_handle, index)};
}

} // namespace echidna