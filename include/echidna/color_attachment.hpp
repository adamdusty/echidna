#pragma once

#include "echidna/texture_view.hpp"
#include <webgpu.h>

namespace echidna {

constexpr auto renderpass_color_attachment(const WGPUChainedStruct& next,
                                           const texture_view& view,
                                           const texture_view& target,
                                           load_op load,
                                           store_op store,
                                           WGPUColor clear) -> WGPURenderPassColorAttachment {
    return WGPURenderPassColorAttachment{
        .nextInChain   = &next,
        .view          = view,
        .resolveTarget = target,
        .loadOp        = static_cast<WGPULoadOp>(load),
        .storeOp       = static_cast<WGPUStoreOp>(store),
        .clearValue    = clear,
    };
}

constexpr auto renderpass_color_attachment(const texture_view& view,
                                           const texture_view& target,
                                           load_op load,
                                           store_op store,
                                           WGPUColor clear) -> WGPURenderPassColorAttachment {
    return WGPURenderPassColorAttachment{
        .nextInChain   = nullptr,
        .view          = view,
        .resolveTarget = target,
        .loadOp        = static_cast<WGPULoadOp>(load),
        .storeOp       = static_cast<WGPUStoreOp>(store),
        .clearValue    = clear,
    };
}

constexpr auto renderpass_color_attachment(const texture_view& view, load_op load, store_op store, WGPUColor clear)
    -> WGPURenderPassColorAttachment {
    return WGPURenderPassColorAttachment{
        .nextInChain   = nullptr,
        .view          = view,
        .resolveTarget = nullptr,
        .loadOp        = static_cast<WGPULoadOp>(load),
        .storeOp       = static_cast<WGPUStoreOp>(store),
        .clearValue    = clear,
    };
}

constexpr auto renderpass_color_attachment(load_op load, store_op store, WGPUColor clear)
    -> WGPURenderPassColorAttachment {
    return WGPURenderPassColorAttachment{
        .nextInChain   = nullptr,
        .view          = nullptr,
        .resolveTarget = nullptr,
        .loadOp        = static_cast<WGPULoadOp>(load),
        .storeOp       = static_cast<WGPUStoreOp>(store),
        .clearValue    = clear,
    };
}

} // namespace echidna