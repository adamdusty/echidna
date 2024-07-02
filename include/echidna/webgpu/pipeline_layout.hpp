#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT pipeline_layout : public handle_base<pipeline_layout, WGPUPipelineLayout> {
    friend handle_base<pipeline_layout, WGPUPipelineLayout>;
    static auto release(WGPUPipelineLayout handle) { wgpuPipelineLayoutRelease(handle); }
    static auto reference(WGPUPipelineLayout handle) { wgpuPipelineLayoutReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu