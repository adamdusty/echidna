#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group.hpp"
#include "echidna/webgpu/bind_group_layout.hpp"
#include "echidna/webgpu/buffer.hpp"
#include "echidna/webgpu/command_encoder.hpp"
#include "echidna/webgpu/compute_pipeline.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include "echidna/webgpu/pipeline_layout.hpp"
#include "echidna/webgpu/query_set.hpp"
#include "echidna/webgpu/queue.hpp"
#include "echidna/webgpu/render_pipeline.hpp"
#include "echidna/webgpu/shader.hpp"
#include "echidna/webgpu/texture.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT device : public handle_base<device, WGPUDevice> {
    friend handle_base<device, WGPUDevice>;
    static auto release(WGPUDevice handle) { wgpuDeviceRelease(handle); }
    static auto reference(WGPUDevice handle) { wgpuDeviceReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto create_bind_group(const WGPUBindGroupDescriptor& desc) const -> bind_group;
    auto create_bind_group_layout(const WGPUBindGroupLayoutDescriptor& desc) const -> bind_group_layout;
    auto create_buffer(const WGPUBufferDescriptor& desc) const -> buffer;
    auto create_buffer(buffer_usage usage, std::uint64_t size) const -> buffer;
    auto create_command_encoder(const char* label = nullptr) const -> command_encoder;
    auto create_command_encoder(const WGPUCommandEncoderDescriptor& desc) const -> command_encoder;
    auto create_compute_pipeline(const WGPUComputePipelineDescriptor& desc) const -> compute_pipeline;
    auto create_pipeline_layout(const WGPUPipelineLayoutDescriptor& desc) const -> pipeline_layout;
    auto create_render_pipeline(const WGPURenderPipelineDescriptor& desc) const -> render_pipeline;
    auto create_query_set(const WGPUQuerySetDescriptor& desc) const -> query_set;
    auto features() const -> std::vector<feature_name>;
    auto limits() const -> WGPUSupportedLimits;
    auto has_feature(feature_name feature) const -> bool;
    auto get_queue() const -> queue;
    auto set_uncaptured_error_callback(WGPUErrorCallback callback, void* user_data = nullptr) const -> void;

    auto create_texture(const WGPUTextureDescriptor& desc) const -> texture;

    auto create_shader_module(const WGPUShaderModuleDescriptor& desc) const -> shader_module;
    // auto shader_moudle_from_wgsl(const char* code) const -> shader_module;

    // auto set_label(const char* label) const -> void; Unimplemented by wgpu-native
};

// Device error callback that prints wgpu error message to stderr
static constexpr auto device_error_stderr = [](WGPUErrorType type, const char* msg, void*) {
    std::cerr << "Device error: " << type;
    if(msg != nullptr) {
        std::cerr << "(message: " << msg << ")";
    }
};

} // namespace echidna::webgpu

// clang-format off
// WGPU_EXPORT void wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
// WGPU_EXPORT void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
// clang-format on
