#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class render_pipeline {
    HANDLE_IMPL(render_pipeline, WGPURenderPipeline)
};

} // namespace echidna