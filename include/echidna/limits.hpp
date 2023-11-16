#pragma once

#include <webgpu.h>

namespace echidna {

using wgpu_limits           = WGPULimits;
using wgpu_required_limits  = WGPURequiredLimits;
using wgpu_supported_limits = WGPUSupportedLimits;

constexpr auto wgpu_limits_zero() {
    return WGPULimits{
        .maxTextureDimension1D                     = 0,
        .maxTextureDimension2D                     = 0,
        .maxTextureDimension3D                     = 0,
        .maxTextureArrayLayers                     = 0,
        .maxBindGroups                             = 0,
        .maxBindGroupsPlusVertexBuffers            = 0,
        .maxBindingsPerBindGroup                   = 0,
        .maxDynamicUniformBuffersPerPipelineLayout = 0,
        .maxDynamicStorageBuffersPerPipelineLayout = 0,
        .maxSampledTexturesPerShaderStage          = 0,
        .maxSamplersPerShaderStage                 = 0,
        .maxStorageBuffersPerShaderStage           = 0,
        .maxStorageTexturesPerShaderStage          = 0,
        .maxUniformBuffersPerShaderStage           = 0,
        .maxUniformBufferBindingSize               = 0,
        .maxStorageBufferBindingSize               = 0,
        .minUniformBufferOffsetAlignment           = 64,
        .minStorageBufferOffsetAlignment           = 32,
        .maxVertexBuffers                          = 0,
        .maxBufferSize                             = 0,
        .maxVertexAttributes                       = 0,
        .maxVertexBufferArrayStride                = 0,
        .maxInterStageShaderComponents             = 0,
        .maxInterStageShaderVariables              = 0,
        .maxColorAttachments                       = 0,
        .maxColorAttachmentBytesPerSample          = 0,
        .maxComputeWorkgroupStorageSize            = 0,
        .maxComputeInvocationsPerWorkgroup         = 0,
        .maxComputeWorkgroupSizeX                  = 0,
        .maxComputeWorkgroupSizeY                  = 0,
        .maxComputeWorkgroupSizeZ                  = 0,
        .maxComputeWorkgroupsPerDimension          = 0,
    };
}

} // namespace echidna