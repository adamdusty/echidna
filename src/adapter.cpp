#include "echidna/webgpu/adapter.hpp"

#include <cassert>
#include <iostream>

namespace echidna::webgpu {

auto adapter::limits() const -> WGPUSupportedLimits {
    auto limits = WGPUSupportedLimits{};
    wgpuAdapterGetLimits(_handle, &limits);
    return limits;
}

auto adapter::properties() const -> WGPUAdapterProperties {
    auto props = WGPUAdapterProperties{};
    wgpuAdapterGetProperties(_handle, &props);
    return props;
}

auto adapter::features() const -> std::vector<feature_name> {
    auto wgpu_features = std::vector<WGPUFeatureName>{};
    auto feature_count = wgpuAdapterEnumerateFeatures(_handle, nullptr);
    wgpu_features.resize(feature_count);
    wgpuAdapterEnumerateFeatures(_handle, wgpu_features.data());

    auto features = std::vector<feature_name>{};
    for(const auto& feat: wgpu_features) {
        features.emplace_back(feat);
    }

    return features;
}

auto adapter::has_feature(feature_name feature) const -> bool {
    return static_cast<bool>(wgpuAdapterHasFeature(_handle, feature));
}

auto adapter::request_device(const WGPUDeviceDescriptor& desc) const -> device {
    struct user_data {
        WGPUDevice device  = nullptr;
        bool request_ended = false;
    };

    auto data = user_data{};

    auto callback = [](WGPURequestDeviceStatus status,
                       WGPUDevice device,
                       const char* message,
                       void* user_data_ptr) {
        auto& callback_request_data = *static_cast<user_data*>(user_data_ptr); // NOLINT

        if(status == WGPURequestDeviceStatus_Success) {
            callback_request_data.device = device;
        } else {
            std::cout << "Could not get WebGPU adapter: " << message << '\n';
        }

        callback_request_data.request_ended = true;
    };

    wgpuAdapterRequestDevice(_handle, &desc, callback, &data);
    assert(data.request_ended);

    return device{data.device};
}

} // namespace echidna::webgpu