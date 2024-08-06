#pragma once

#include <webgpu.h>

#include "echidna/export.hpp"
#include "echidna/webgpu/adapter.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/surface.hpp"

namespace echidna::webgpu {

struct ECHIDNA_EXPORT instance : public handle_base<instance, WGPUInstanceImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;

    instance() {
        auto desc = WGPUInstanceDescriptor{.nextInChain = nullptr};
        _handle   = handle_type(wgpuCreateInstance(&desc));
    }
    explicit instance(const WGPUInstanceDescriptor& desc) :
        handle_base(wgpuCreateInstance(&desc)) {}

    auto process_events() const -> void;
    auto create_surface(const WGPUSurfaceDescriptor& descriptor) const -> surface;
    auto request_adapter(const WGPURequestAdapterOptions& options) const -> adapter;
};

} // namespace echidna::webgpu