#pragma once

#include <utility>

#include <webgpu.h>

#include "echidna/adapter.hpp"
#include "echidna/chained.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include "echidna/surface.hpp"

namespace echidna {

template<typename E, typename W>
class handle_base {
protected:
    W _handle;

public:
    handle_base() = default;
    handle_base(W handle) : _handle(handle) {}
    handle_base(handle_base&& other) noexcept : _handle(std::exchange(other._handle, nullptr)) {}
    ~handle_base() {
        if(_handle) {
            E::release(_handle);
        }
    }

    auto operator=(handle_base&& other) noexcept -> E& { // NOLINT
        _handle = std::exchange(other._handle, nullptr);
        return static_cast<E&>(*this);
    }

    constexpr explicit operator bool() { return _handle != nullptr; }
    constexpr operator W() const { return _handle; }
    constexpr auto get() -> W { return _handle; }
};

class ECHIDNA_EXPORT instance : public handle_base<instance, WGPUInstance> {
    // HANDLE_IMPL(instance, WGPUInstance)
    friend handle_base<instance, WGPUInstance>;
    static auto release(WGPUInstance handle) { wgpuInstanceRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    instance(const WGPUInstanceDescriptor& desc) : handle_base(wgpuCreateInstance(&desc)) {}
    ~instance() {
        if(_handle != nullptr) {
            wgpuInstanceRelease(_handle);
        }
    }

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