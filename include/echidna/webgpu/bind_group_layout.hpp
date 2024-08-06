#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT bind_group_layout
    : public handle_base<bind_group_layout, WGPUBindGroupLayoutImpl> {

    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu