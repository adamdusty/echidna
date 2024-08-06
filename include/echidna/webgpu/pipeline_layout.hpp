#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT pipeline_layout
    : public handle_base<pipeline_layout, WGPUPipelineLayoutImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu