#include "echidna/device.hpp"

#include "echidna/chained.hpp"

namespace echidna {

auto device_descriptor(const char* label,
                       std::vector<feature_name>& required_features,
                       std::vector<WGPURequiredLimits>& required_limits,
                       const WGPUQueueDescriptor& desc,
                       WGPUDeviceLostCallback callback,
                       void* user_data) -> WGPUDeviceDescriptor {

    auto wgpu_features = std::vector<WGPUFeatureName>();
    auto wgpu_limits   = std::vector<WGPURequiredLimits>();

    for(auto feat: required_features) {
        wgpu_features.emplace_back(static_cast<WGPUFeatureName>(feat));
    }

    for(auto limit: required_limits) {
        wgpu_limits.emplace_back(static_cast<WGPURequiredLimits>(limit));
    }

    return WGPUDeviceDescriptor{
        .nextInChain          = nullptr,
        .label                = label,
        .requiredFeatureCount = required_features.size(),
        .requiredFeatures     = wgpu_features.data(),
        .requiredLimits       = wgpu_limits.data(),
        .defaultQueue         = desc,
        .deviceLostCallback   = callback,
        .deviceLostUserdata   = user_data,
    };
}

auto device_descriptor(const char* label,
                       std::vector<feature_name>& required_features,
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

auto device::create_command_encoder(const char* label) const -> command_encoder {
    auto desc = WGPUCommandEncoderDescriptor{.nextInChain = nullptr, .label = label};
    return command_encoder{wgpuDeviceCreateCommandEncoder(_handle, &desc)};
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

// auto device::set_label(const char* label) const -> void {
//     wgpuDeviceSetLabel(_handle, label);
// }

auto device::set_uncaptured_error_callback(WGPUErrorCallback callback, void* user_data) const -> void {
    wgpuDeviceSetUncapturedErrorCallback(_handle, callback, user_data);
}

auto device::create_texture(const WGPUTextureDescriptor& desc) const -> texture {
    return texture{wgpuDeviceCreateTexture(_handle, &desc)};
}

auto device::create_shader_module(const WGPUShaderModuleDescriptor& desc) const -> shader_module {
    return shader_module{wgpuDeviceCreateShaderModule(_handle, &desc)};
}

auto device::shader_moudle_from_wgsl(const char* code) const -> shader_module {
    auto code_desc = wgsl_descriptor(code);
    auto mod_desc  = WGPUShaderModuleDescriptor{
         .nextInChain = &code_desc.chain,
         .label       = nullptr,
         .hintCount   = 0,
         .hints       = nullptr,
    };

    return create_shader_module(mod_desc);
}

} // namespace echidna