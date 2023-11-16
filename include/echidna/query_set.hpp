#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class query_set {
    HANDLE_IMPL(query_set, WGPUQuerySet)
};

} // namespace echidna