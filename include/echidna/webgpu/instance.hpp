#pragma once

#include <webgpu.h>

#include "echidna/export.hpp"
#include "echidna/webgpu/adapter.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/structs.hpp"
#include "echidna/webgpu/surface.hpp"
#include "echidna/webgpu/surface_descriptor.hpp"

namespace echidna::webgpu {

class ECHIDNA_EXPORT instance : public handle_base<instance, WGPUInstance> {
    friend handle_base<instance, WGPUInstance>;
    static auto release(WGPUInstance handle) { wgpuInstanceRelease(handle); }
    static auto reference(WGPUInstance handle) { wgpuInstanceReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    explicit instance(const WGPUInstanceDescriptor& desc) :
        handle_base(wgpuCreateInstance(&desc)) {}

    auto process_events() const -> void;
    auto create_surface(const surface_descriptor& descriptor) const -> surface;
    auto request_adapter(const request_adapter_options& options) const -> adapter;
};

// constexpr auto instance_descriptor(const WGPUChainedStruct& next) {
//     return WGPUInstanceDescriptor{.nextInChain = &next};
// }

// constexpr auto instance_descriptor() {
//     return WGPUInstanceDescriptor{.nextInChain = nullptr};
// }

} // namespace echidna::webgpu