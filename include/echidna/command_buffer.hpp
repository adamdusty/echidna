#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class command_buffer {
    HANDLE_IMPL(command_buffer, WGPUCommandBuffer)
};

} // namespace echidna