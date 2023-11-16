#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class bind_group {
    HANDLE_IMPL(bind_group, WGPUBindGroup)
};

} // namespace echidna