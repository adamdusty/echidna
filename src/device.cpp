#include "echidna/device.hpp"

namespace echidna {

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<WGPURequiredLimits>& required_limits,
                       const WGPUQueueDescriptor& desc,
                       WGPUDeviceLostCallback callback,
                       void* user_data) -> WGPUDeviceDescriptor {
    return WGPUDeviceDescriptor{
        .nextInChain          = nullptr,
        .label                = label,
        .requiredFeatureCount = required_features.size(),
        .requiredFeatures     = reinterpret_cast<const WGPUFeatureName*>(required_features.data()),
        .requiredLimits       = reinterpret_cast<const WGPURequiredLimits*>(required_limits.data()),
        .defaultQueue         = desc,
        .deviceLostCallback   = callback,
        .deviceLostUserdata   = user_data,
    };
}

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<WGPURequiredLimits>& required_limits) -> WGPUDeviceDescriptor {
    return device_descriptor(label, required_features, required_limits, queue_descriptor(), nullptr, nullptr);
}

auto device_descriptor(const char* label) -> WGPUDeviceDescriptor {
    return WGPUDeviceDescriptor{
        .nextInChain          = nullptr,
        .label                = label,
        .requiredFeatureCount = 0,
        .requiredFeatures     = nullptr,
        .requiredLimits       = nullptr,
        .defaultQueue         = queue_descriptor(),
        .deviceLostCallback   = nullptr,
        .deviceLostUserdata   = nullptr,
    };
}

auto device::create_bind_group(const WGPUBindGroupDescriptor& desc) const -> bind_group {
    return bind_group{wgpuDeviceCreateBindGroup(_handle, &desc)};
}

auto device::create_bind_group_layout(const WGPUBindGroupLayoutDescriptor& desc) const -> bind_group_layout {
    return bind_group_layout{wgpuDeviceCreateBindGroupLayout(_handle, &desc)};
}

auto device::create_buffer(const WGPUBufferDescriptor& desc) const -> buffer {
    return buffer{wgpuDeviceCreateBuffer(_handle, &desc)};
}

auto device::create_command_encoder(const WGPUCommandEncoderDescriptor& desc) const -> command_encoder {
    return command_encoder{wgpuDeviceCreateCommandEncoder(_handle, &desc)};
}

auto device::create_compute_pipeline(const WGPUComputePipelineDescriptor& desc) const -> compute_pipeline {
    return compute_pipeline{wgpuDeviceCreateComputePipeline(_handle, &desc)};
}

auto device::create_pipeline_layout(const WGPUPipelineLayoutDescriptor& desc) const -> pipeline_layout {
    return pipeline_layout{wgpuDeviceCreatePipelineLayout(_handle, &desc)};
}

auto device::create_render_pipeline(const WGPURenderPipelineDescriptor& desc) const -> render_pipeline {
    return render_pipeline{wgpuDeviceCreateRenderPipeline(_handle, &desc)};
}

auto device::create_query_set(const WGPUQuerySetDescriptor& desc) const -> query_set {
    return query_set{wgpuDeviceCreateQuerySet(_handle, &desc)};
}

auto device::features() const -> std::vector<feature_name> {
    auto wgpu_features = std::vector<WGPUFeatureName>{};
    auto feature_count = wgpuDeviceEnumerateFeatures(_handle, nullptr);
    wgpu_features.resize(feature_count);
    wgpuDeviceEnumerateFeatures(_handle, wgpu_features.data());

    auto features = std::vector<feature_name>{};
    for(const auto& feat: wgpu_features) {
        features.emplace_back(static_cast<feature_name>(feat));
    }

    return features;
}

auto device::limits() const -> WGPUSupportedLimits {
    auto limits = WGPUSupportedLimits{};
    wgpuDeviceGetLimits(_handle, &limits);
    return limits;
}

auto device::has_feature(feature_name feature) const -> bool {
    return static_cast<bool>(wgpuDeviceHasFeature(_handle, static_cast<WGPUFeatureName>(feature)));
}

auto device::get_queue() const -> queue {
    return queue{wgpuDeviceGetQueue(_handle)};
}

auto device::set_label(const char* label) const -> void {
    wgpuDeviceSetLabel(_handle, label);
}

auto device::set_uncaptured_error_callback(WGPUErrorCallback callback, void* user_data) const -> void {
    wgpuDeviceSetUncapturedErrorCallback(_handle, callback, user_data);
}

} // namespace echidna