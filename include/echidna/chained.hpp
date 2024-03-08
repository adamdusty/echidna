#pragma once

#include <webgpu.h>

#include "echidna/webgpu/enums.hpp"

namespace echidna {

constexpr auto chained_struct(const WGPUChainedStruct* next, stype _type) {
    return WGPUChainedStruct{
        .next  = next,
        .sType = static_cast<WGPUSType>(_type),
    };
}

constexpr auto chained_struct(stype type) {
    return chained_struct(nullptr, type);
}

constexpr auto chained_struct() {
    return chained_struct(nullptr, stype::invalid);
}

} // namespace echidna