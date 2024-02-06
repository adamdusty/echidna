#pragma once

#include "echidna/enums.hpp"
#include <webgpu.h>

namespace echidna {

constexpr auto blend_component(blend_op op, blend_factor src, blend_factor dst) -> WGPUBlendComponent {
    return WGPUBlendComponent{
        .operation = static_cast<WGPUBlendOperation>(op),
        .srcFactor = static_cast<WGPUBlendFactor>(src),
        .dstFactor = static_cast<WGPUBlendFactor>(dst),
    };
}

constexpr auto color_target_state(texture_format fmt, const WGPUBlendState& state, color_write_mask mask)
    -> WGPUColorTargetState {
    return WGPUColorTargetState{
        .nextInChain = nullptr,
        .format      = static_cast<WGPUTextureFormat>(fmt),
        .blend       = &state,
        .writeMask   = static_cast<WGPUColorWriteMaskFlags>(mask),
    };
}

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

constexpr auto vertex_format_size(vertex_format fmt) -> std::uint64_t {
    switch(fmt) {
        using enum vertex_format;
    case undefined:
        return 0;
    case uint8x2:
    case sint8x2:
    case unorm8x2:
    case snorm8x2:
        return sizeof(std::uint8_t) * 2;
    case uint8x4:
    case sint8x4:
    case unorm8x4:
    case snorm8x4:
        return sizeof(std::uint8_t) * 4;
    case uint16x2:
    case sint16x2:
    case unorm16x2:
    case snorm16x2:
    case float16x2:
        return sizeof(std::uint16_t) * 2;
    case uint16x4:
    case sint16x4:
    case unorm16x4:
    case snorm16x4:
    case float16x4:
        return sizeof(std::uint16_t) * 4;
    case uint32:
    case sint32:
    case float32:
        return sizeof(std::uint32_t);
    case uint32x2:
    case sint32x2:
    case float32x2:
        return sizeof(std::uint32_t) * 2;
    case uint32x3:
    case sint32x3:
    case float32x3:
        return sizeof(std::uint32_t) * 3;
    case uint32x4:
    case sint32x4:
    case float32x4:
        return sizeof(std::uint32_t) * 4;
    default:
        return 0;
    }
}

struct vertex_info {
    std::vector<WGPUVertexAttribute> attribs;
    WGPUVertexBufferLayout layout;
};

constexpr auto vertex_buffer_layout(vertex_format fmt1) -> vertex_info {
    auto info = vertex_info{};
    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt1), 0, 0);
    info.layout = WGPUVertexBufferLayout{
        .arrayStride    = vertex_format_size(fmt1),
        .stepMode       = static_cast<WGPUVertexStepMode>(vertex_step_mode::vertex),
        .attributeCount = 1,
        .attributes     = info.attribs.data(),
    };

    return info;
}

constexpr auto vertex_buffer_layout(vertex_format fmt1, vertex_format fmt2) -> vertex_info {
    auto info = vertex_info{};

    std::uint64_t size = 0;
    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt1), 0, 0);
    size += vertex_format_size(fmt1);

    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt2), size, 1);
    size += vertex_format_size(fmt2);

    info.layout = WGPUVertexBufferLayout{
        .arrayStride    = size,
        .stepMode       = static_cast<WGPUVertexStepMode>(vertex_step_mode::vertex),
        .attributeCount = 2,
        .attributes     = info.attribs.data(),
    };

    return info;
}

constexpr auto vertex_buffer_layout(vertex_format fmt1, vertex_format fmt2, vertex_format fmt3) -> vertex_info {
    auto info = vertex_info{};

    std::uint64_t size = 0;
    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt1), 0, 0);
    size += vertex_format_size(fmt1);

    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt2), size, 1);
    size += vertex_format_size(fmt2);

    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt3), size, 2);
    size += vertex_format_size(fmt3);

    info.layout = WGPUVertexBufferLayout{
        .arrayStride    = size,
        .stepMode       = static_cast<WGPUVertexStepMode>(vertex_step_mode::vertex),
        .attributeCount = 3,
        .attributes     = info.attribs.data(),
    };

    return info;
}

constexpr auto vertex_buffer_layout(vertex_format fmt1, vertex_format fmt2, vertex_format fmt3, vertex_format fmt4)
    -> vertex_info {
    auto info = vertex_info{};

    std::uint64_t size = 0;
    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt1), 0, 0);
    size += vertex_format_size(fmt1);

    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt2), size, 1);
    size += vertex_format_size(fmt2);

    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt3), size, 2);
    size += vertex_format_size(fmt3);

    info.attribs.emplace_back(static_cast<WGPUVertexFormat>(fmt4), size, 3);
    size += vertex_format_size(fmt4);

    info.layout = WGPUVertexBufferLayout{
        .arrayStride    = size,
        .stepMode       = static_cast<WGPUVertexStepMode>(vertex_step_mode::vertex),
        .attributeCount = 4,
        .attributes     = info.attribs.data(),
    };

    return info;
}

} // namespace echidna