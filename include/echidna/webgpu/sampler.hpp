#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT sampler : public handle_base<sampler, WGPUSampler> {
    friend handle_base<sampler, WGPUSampler>;
    static auto release(WGPUSampler handle) { wgpuSamplerRelease(handle); }
    static auto reference(WGPUSampler handle) { wgpuSamplerReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu