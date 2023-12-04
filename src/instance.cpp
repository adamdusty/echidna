#include "echidna/instance.hpp"

#include <cassert>
#include <utility>

namespace echidna {

auto instance::process_events() const -> void {
    wgpuInstanceProcessEvents(_handle);
}

auto instance::create_surface(const WGPUSurfaceDescriptor& descriptor) const -> surface {
    auto* surf = wgpuInstanceCreateSurface(_handle, &descriptor);
    return surface(surf);
}

auto instance::request_adapter(const WGPURequestAdapterOptions& options) const -> adapter {
    struct user_data {
        WGPUAdapter adapter = nullptr;
        bool request_ended  = false;
    };

    auto data = user_data{};

    auto callback = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const* message, void* user_data_ptr) {
        // NOLINTNEXTLINE
        user_data& user_data = *static_cast<struct user_data*>(user_data_ptr);
        if(status == request_adapter_status::success) {
            user_data.adapter = adapter;
        } else {
            std::cout << "Could not get WebGPU adapter: " << message << '\n';
        }

        user_data.request_ended = true;
    };

    wgpuInstanceRequestAdapter(_handle, &options, callback, &data);
    assert(data.request_ended);

    return adapter{data.adapter};
}

} // namespace echidna