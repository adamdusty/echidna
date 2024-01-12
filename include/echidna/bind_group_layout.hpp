#pragma once

#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT bind_group_layout : public handle_base<bind_group_layout, WGPUBindGroupLayout> {
    friend handle_base<bind_group_layout, WGPUBindGroupLayout>;
    static auto release(WGPUBindGroupLayout handle) { wgpuBindGroupLayoutRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna