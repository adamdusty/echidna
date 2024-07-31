#include "echidna/webgpu/device.hpp"

namespace echidna::webgpu {

auto device::create_bind_group(const WGPUBindGroupDescriptor& desc) const -> bind_group {
    return bind_group{wgpuDeviceCreateBindGroup(_handle, &desc)};
}

auto device::create_bind_group_layout(const WGPUBindGroupLayoutDescriptor& desc
) const -> bind_group_layout {
    return bind_group_layout{wgpuDeviceCreateBindGroupLayout(_handle, &desc)};
}

auto device::create_buffer(const WGPUBufferDescriptor& desc) const -> buffer {
    return buffer{wgpuDeviceCreateBuffer(_handle, &desc)};
}

auto device::create_buffer(buffer_usage usage, std::uint64_t size) const -> buffer {
    auto desc = WGPUBufferDescriptor{
        .nextInChain      = nullptr,
        .label            = nullptr,
        .usage            = usage,
        .size             = size,
        .mappedAtCreation = static_cast<WGPUBool>(false),
    };
    return buffer{wgpuDeviceCreateBuffer(_handle, &desc)};
}

auto device::create_command_encoder(const char* label) const -> command_encoder {
    auto desc = WGPUCommandEncoderDescriptor{.nextInChain = nullptr, .label = label};
    return command_encoder{wgpuDeviceCreateCommandEncoder(_handle, &desc)};
}

auto device::create_command_encoder(const WGPUCommandEncoderDescriptor& desc
) const -> command_encoder {
    return command_encoder{wgpuDeviceCreateCommandEncoder(_handle, &desc)};
}

auto device::create_compute_pipeline(const WGPUComputePipelineDescriptor& desc
) const -> compute_pipeline {
    return compute_pipeline{wgpuDeviceCreateComputePipeline(_handle, &desc)};
}

auto device::create_pipeline_layout(const WGPUPipelineLayoutDescriptor& desc
) const -> pipeline_layout {
    return pipeline_layout{wgpuDeviceCreatePipelineLayout(_handle, &desc)};
}

auto device::create_render_pipeline(const WGPURenderPipelineDescriptor& desc
) const -> render_pipeline {
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
        features.emplace_back(feat);
    }

    return features;
}

auto device::limits() const -> WGPUSupportedLimits {
    auto limits = WGPUSupportedLimits{};
    wgpuDeviceGetLimits(_handle, &limits);
    return limits;
}

auto device::has_feature(feature_name feature) const -> bool {
    return static_cast<bool>(wgpuDeviceHasFeature(_handle, feature));
}

auto device::get_queue() const -> queue {
    return queue{wgpuDeviceGetQueue(_handle)};
}

auto device::set_uncaptured_error_callback(WGPUErrorCallback callback, void* user_data) const
    -> void {
    wgpuDeviceSetUncapturedErrorCallback(_handle, callback, user_data);
}

auto device::create_texture(const WGPUTextureDescriptor& desc) const -> texture {
    return texture{wgpuDeviceCreateTexture(_handle, &desc)};
}

auto device::create_shader_module(const WGPUShaderModuleDescriptor& desc) const -> shader_module {
    return shader_module{wgpuDeviceCreateShaderModule(_handle, &desc)};
}

} // namespace echidna::webgpu