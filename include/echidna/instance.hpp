#pragma once

#include <webgpu.h>

#include "echidna/adapter.hpp"
#include "echidna/chained.hpp"
#include "echidna/macros.hpp"
#include "echidna/surface.hpp"

namespace echidna {

constexpr auto instance_descriptor(const WGPUChainedStruct& next) {
    return WGPUInstanceDescriptor{.nextInChain = &next};
}

constexpr auto instance_descriptor() {
    return WGPUInstanceDescriptor{.nextInChain = nullptr};
}

class instance {
    HANDLE_IMPL(instance, WGPUInstance)

    auto process_events() const -> void;
    auto create_surface(const WGPUSurfaceDescriptor& descriptor) const -> surface;
    auto request_adapter(const WGPURequestAdapterOptions& options) const -> adapter;
};

} // namespace echidna