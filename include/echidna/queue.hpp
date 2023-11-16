#pragma once

#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

constexpr auto queue_descriptor(const char* label = nullptr) {
    return WGPUQueueDescriptor{
        .nextInChain = nullptr,
        .label       = label,
    };
}

class queue {
    HANDLE_IMPL(queue, WGPUQueue)
};

} // namespace echidna