#pragma once

#include <utility>

#include <webgpu.h>

#include "echidna/adapter.hpp"
#include "echidna/chained.hpp"
#include "echidna/export.hpp"
#include "echidna/handle.hpp"
#include "echidna/surface.hpp"

namespace echidna {

class ECHIDNA_EXPORT instance : public handle_base<instance, WGPUInstance> {
    friend handle_base<instance, WGPUInstance>;
    static auto release(WGPUInstance handle) { wgpuInstanceRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    static auto create() -> instance {
        auto desc = WGPUInstanceDescriptor{};
        return instance(desc);
    }

    instance(const WGPUInstanceDescriptor& desc) : handle_base(wgpuCreateInstance(&desc)) {}

    auto process_events() const -> void;
    auto create_surface(const WGPUSurfaceDescriptor& descriptor) const -> surface;
    auto request_adapter(const WGPURequestAdapterOptions& options) const -> adapter;
};

constexpr auto instance_descriptor(const WGPUChainedStruct& next) {
    return WGPUInstanceDescriptor{.nextInChain = &next};
}

constexpr auto instance_descriptor() {
    return WGPUInstanceDescriptor{.nextInChain = nullptr};
}

} // namespace echidna