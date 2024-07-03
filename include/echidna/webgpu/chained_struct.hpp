#pragma once

#include <webgpu.h>

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"

namespace echidna::webgpu {

using chained_struct     = WGPUChainedStruct;
using chained_struct_out = WGPUChainedStructOut;

constexpr auto make_chained(chained_struct* next, stype stype) -> chained_struct {
    return chained_struct{.next = next, .sType = static_cast<WGPUSType>(stype)};
}

constexpr auto make_chained(stype stype) -> chained_struct {
    return make_chained(nullptr, stype);
}

} // namespace echidna::webgpu