#pragma once

#include "echidna/bind_group.hpp"
#include "echidna/bind_group_layout.hpp"
#include "echidna/buffer.hpp"
#include "echidna/command_encoder.hpp"
#include "echidna/compute_pipeline.hpp"
#include "echidna/enums.hpp"
#include "echidna/limits.hpp"
#include "echidna/macros.hpp"
#include "echidna/pipeline_layout.hpp"
#include "echidna/query_set.hpp"
#include "echidna/queue.hpp"
#include "echidna/render_pipeline.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <webgpu.h>

namespace echidna {

// Device error callback that prints wgpu error message to stderr
static constexpr auto device_error_stderr = [](WGPUErrorType type, const char* msg, void*) {
    std::cerr << "Device error: " << type;
    if(msg != nullptr) {
        std::cerr << "(message: " << msg << ")";
    }
};

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<WGPURequiredLimits>& required_limits,
                       const WGPUQueueDescriptor& desc,
                       WGPUDeviceLostCallback callback,
                       void* user_data) -> WGPUDeviceDescriptor;

auto device_descriptor(const char* label,
                       const std::vector<feature_name>& required_features,
                       std::vector<WGPURequiredLimits>& required_limits) -> WGPUDeviceDescriptor;

auto device_descriptor(const char* label = nullptr) -> WGPUDeviceDescriptor;

class device {
    HANDLE_IMPL(device, WGPUDevice)

    auto create_bind_group(const WGPUBindGroupDescriptor& desc) const -> bind_group;
    auto create_bind_group_layout(const WGPUBindGroupLayoutDescriptor& desc) const -> bind_group_layout;
    auto create_buffer(const WGPUBufferDescriptor& desc) const -> buffer;
    auto create_command_encoder(const WGPUCommandEncoderDescriptor& desc) const -> command_encoder;
    auto create_compute_pipeline(const WGPUComputePipelineDescriptor& desc) const -> compute_pipeline;
    auto create_pipeline_layout(const WGPUPipelineLayoutDescriptor& desc) const -> pipeline_layout;
    auto create_render_pipeline(const WGPURenderPipelineDescriptor& desc) const -> render_pipeline;
    auto create_query_set(const WGPUQuerySetDescriptor& desc) const -> query_set;
    auto features() const -> std::vector<feature_name>;
    auto limits() const -> WGPUSupportedLimits;
    auto has_feature(feature_name feature) const -> bool;
    auto get_queue() const -> queue;
    // auto set_label(const char* label) const -> void; Unimplemented by wgpu-native
    auto set_uncaptured_error_callback(WGPUErrorCallback callback, void* user_data = nullptr) const -> void;
};

} // namespace echidna

// clang-format off
// WGPU_EXPORT void wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on
