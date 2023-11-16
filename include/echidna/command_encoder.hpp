#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class command_encoder {
    HANDLE_IMPL(command_encoder, WGPUCommandEncoder)
};

} // namespace echidna