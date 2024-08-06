#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT bind_group : public handle_base<bind_group, WGPUBindGroupImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu