#pragma once

#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT texture_view {
    HANDLE_IMPL(texture_view, WGPUTextureView)
    ~texture_view() {
        if(_handle != nullptr) {
            wgpuTextureViewRelease(_handle);
        }
    }
};

constexpr auto texture_view_descriptor(const char* label,
                                       texture_format format,
                                       textureview_dimension dimension,
                                       std::uint32_t mip_level,
                                       std::uint32_t mip_level_count,
                                       std::uint32_t base_array,
                                       std::uint32_t array_layer_count,
                                       texture_aspect aspect) -> WGPUTextureViewDescriptor {
    return {
        .nextInChain     = nullptr,
        .label           = label,
        .format          = static_cast<WGPUTextureFormat>(format),
        .dimension       = static_cast<WGPUTextureViewDimension>(dimension),
        .baseMipLevel    = mip_level,
        .mipLevelCount   = mip_level_count,
        .baseArrayLayer  = base_array,
        .arrayLayerCount = array_layer_count,
        .aspect          = static_cast<WGPUTextureAspect>(aspect),
    };
}

} // namespace echidna