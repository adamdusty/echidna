#pragma once

#include "echidna/enums.hpp"
#include <webgpu.h>

namespace echidna {

constexpr auto primitive_state(
    primitive_topology topology,
    index_format index_format,
    front_face front_face,
    cull_mode cull_mode
) -> WGPUPrimitiveState {
    return WGPUPrimitiveState{
        .nextInChain      = nullptr,
        .topology         = static_cast<WGPUPrimitiveTopology>(topology),
        .stripIndexFormat = static_cast<WGPUIndexFormat>(index_format),
        .frontFace        = static_cast<WGPUFrontFace>(front_face),
        .cullMode         = static_cast<WGPUCullMode>(cull_mode),
    };
}

} // namespace echidna