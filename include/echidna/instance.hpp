#pragma once

#include <webgpu.h>

#include "echidna/adapter.hpp"
#include "echidna/chained.hpp"
#include "echidna/surface.hpp"

namespace echidna {

constexpr auto instance_descriptor(const WGPUChainedStruct& next) {
    return WGPUInstanceDescriptor{.nextInChain = &next};
}

constexpr auto instance_descriptor() {
    return WGPUInstanceDescriptor{.nextInChain = nullptr};
}

class instance {
    WGPUInstance _handle{nullptr};

public:
    explicit operator bool() { return _handle != nullptr; }
    constexpr operator WGPUInstance() const { return _handle; }

    instance();
    explicit instance(const WGPUInstanceDescriptor&);
    ~instance();
    instance(instance&)       = delete;
    auto operator=(instance&) = delete;
    instance(instance&& other) noexcept;
    auto operator=(instance&& other) noexcept -> instance&;

    auto process_events() const -> void;
    auto create_surface(const WGPUSurfaceDescriptor& descriptor) const -> surface;
    auto request_adapter(const WGPURequestAdapterOptions& options) const -> adapter;
};

} // namespace echidna