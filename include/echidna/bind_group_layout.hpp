#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class bind_group_layout {
    HANDLE_IMPL(bind_group_layout, WGPUBindGroupLayout)
};

} // namespace echidna