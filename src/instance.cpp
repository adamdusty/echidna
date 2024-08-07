#include "echidna/webgpu/instance.hpp"

#include <cassert>
#include <iostream>

namespace echidna::webgpu {

/**
 * https://github.com/webgpu-native/webgpu-headers/issues/117
 * check in-flight GPU work and free resources no longer used by GPU
 * issue mapping callbacks
 * not block on any GPU work
 */
auto instance::process_events() const -> void {
    wgpuInstanceProcessEvents(_handle.get());
}

auto instance::create_surface(const WGPUSurfaceDescriptor& descriptor) const -> surface {
    WGPUSurfaceDescriptor wgpu_desc = descriptor;
    return wgpuInstanceCreateSurface(_handle.get(), &wgpu_desc);
}

auto instance::request_adapter(const WGPURequestAdapterOptions& options) const -> adapter {
    struct user_data {
        WGPUAdapter adapter = nullptr;
        bool request_ended  = false;
    };

    auto data = user_data{};

    auto callback = [](WGPURequestAdapterStatus status,
                       WGPUAdapter adapter,
                       char const* message,
                       void* user_data_ptr) {
        user_data& user_data = *static_cast<struct user_data*>(user_data_ptr);
        if(status == request_adapter_status::success) {
            user_data.adapter = adapter;
        } else {
            std::cerr << "Could not get WebGPU adapter: " << message << '\n';
        }

        user_data.request_ended = true;
    };

    wgpuInstanceRequestAdapter(_handle.get(), &options, callback, &data);
    assert(data.request_ended);

    return adapter{data.adapter};
}

} // namespace echidna::webgpu