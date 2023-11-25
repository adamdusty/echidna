#include "echidna/render_pipeline.hpp"

namespace echidna {

auto render_pipeline::bind_group_layout(std::uint32_t index) const -> echidna::bind_group_layout {
    return echidna::bind_group_layout{wgpuRenderPipelineGetBindGroupLayout(_handle, index)};
}

} // namespace echidna