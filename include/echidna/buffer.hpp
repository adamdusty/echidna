#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class buffer {
    HANDLE_IMPL(buffer, WGPUBuffer)
};

} // namespace echidna