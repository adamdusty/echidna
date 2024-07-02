#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group_layout.hpp"
#include "echidna/webgpu/buffer.hpp"
#include "echidna/webgpu/device.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/pipeline_layout.hpp"
#include "echidna/webgpu/query_set.hpp"
#include "echidna/webgpu/sampler.hpp"
#include "echidna/webgpu/shader.hpp"
#include "echidna/webgpu/surface.hpp"
#include "echidna/webgpu/texture.hpp"
#include "echidna/webgpu/texture_view.hpp"

#include <algorithm>
#include <bit>
#include <cstdint>
#include <string>
#include <vector>
#include <webgpu.h>

namespace echidna::webgpu {

using chained_struct     = WGPUChainedStruct;
using chained_struct_out = WGPUChainedStructOut;

using device_lost_callback = WGPUDeviceLostCallback;

struct ECHIDNA_EXPORT adapter_properties {
    chained_struct_out* next;
    std::uint32_t vendor_id;
    std::string vendor;
    std::string architecture;
    std::uint32_t device_id;
    std::string device;
    std::string description;
    backend_type backend_type;
    adapter_type adapter_type;

    constexpr adapter_properties(WGPUAdapterProperties& p) :
        next(p.nextInChain),
        vendor_id(p.vendorID),
        vendor(p.vendorName),
        architecture(p.architecture),
        device_id(p.deviceID),
        device(p.name),
        description(p.driverDescription),
        backend_type(static_cast<echidna::webgpu::backend_type>(p.backendType)),
        adapter_type(static_cast<echidna::webgpu::adapter_type>(p.adapterType)) {}

    constexpr operator WGPUAdapterProperties() const {
        return WGPUAdapterProperties{
            .nextInChain       = std::bit_cast<WGPUChainedStructOut*>(next),
            .vendorID          = vendor_id,
            .vendorName        = vendor.c_str(),
            .architecture      = architecture.c_str(),
            .deviceID          = device_id,
            .name              = device.c_str(),
            .driverDescription = description.c_str(),
            .adapterType       = static_cast<WGPUAdapterType>(adapter_type),
            .backendType       = static_cast<WGPUBackendType>(backend_type),
        };
    }
};

struct ECHIDNA_EXPORT bind_group_entry {
    const chained_struct* next;
    std::uint32_t binding;
    buffer buffer;
    std::uint64_t offset;
    std::uint64_t size;
    sampler sampler;
    texture_view texture_view;

    constexpr bind_group_entry(const WGPUBindGroupEntry& e) :
        next(e.nextInChain),
        binding(e.binding),
        buffer(e.buffer),
        offset(e.offset),
        size(e.size),
        sampler(e.sampler),
        texture_view(e.textureView) {}

    constexpr operator WGPUBindGroupEntry() const {
        return WGPUBindGroupEntry{
            .nextInChain = next,
            .binding     = binding,
            .buffer      = buffer,
            .offset      = offset,
            .size        = size,
            .sampler     = sampler,
            .textureView = texture_view,
        };
    }
};

struct ECHIDNA_EXPORT blend_component {
    blend_op op;
    blend_factor src;
    blend_factor dst;

    constexpr blend_component(const WGPUBlendComponent& bc) :
        op(static_cast<blend_op>(bc.operation)),
        src(static_cast<blend_factor>(bc.srcFactor)),
        dst(static_cast<blend_factor>(bc.dstFactor)) {}

    constexpr operator WGPUBlendComponent() const {
        return WGPUBlendComponent{
            .operation = static_cast<WGPUBlendOperation>(op),
            .srcFactor = static_cast<WGPUBlendFactor>(src),
            .dstFactor = static_cast<WGPUBlendFactor>(dst),
        };
    }
};

struct ECHIDNA_EXPORT buffer_binding_layout {
    const chained_struct* next;
    buffer_binding_type type;
    bool dynamic_offset;
    std::uint64_t min_binding_size;

    constexpr buffer_binding_layout(const WGPUBufferBindingLayout& b) :
        next(b.nextInChain),
        type(static_cast<buffer_binding_type>(b.type)),
        dynamic_offset(static_cast<bool>(b.hasDynamicOffset)),
        min_binding_size(b.minBindingSize) {}

    constexpr operator WGPUBufferBindingLayout() const {
        return WGPUBufferBindingLayout{
            .nextInChain      = next,
            .type             = static_cast<WGPUBufferBindingType>(type),
            .hasDynamicOffset = static_cast<WGPUBool>(dynamic_offset),
            .minBindingSize   = min_binding_size,
        };
    };
};

struct ECHIDNA_EXPORT buffer_descriptor {
    const chained_struct* next;
    std::string label;
    buffer_usage usage;
    std::uint64_t size;
    bool mapped_at_creation;

    constexpr buffer_descriptor(const WGPUBufferDescriptor& bd) :
        next(bd.nextInChain),
        label(bd.label),
        usage(static_cast<buffer_usage>(bd.usage)),
        size(bd.size),
        mapped_at_creation(static_cast<bool>(bd.mappedAtCreation)) {}

    constexpr operator WGPUBufferDescriptor() const {
        return WGPUBufferDescriptor{
            .nextInChain      = next,
            .label            = label.c_str(),
            .usage            = static_cast<WGPUBufferUsage>(usage),
            .size             = size,
            .mappedAtCreation = static_cast<WGPUBool>(mapped_at_creation),
        };
    }
};

struct ECHIDNA_EXPORT color {
    double red;
    double green;
    double blue;
    double alpha;

    constexpr color(const WGPUColor& c) : red(c.r), green(c.g), blue(c.b), alpha(c.a) {}
    constexpr operator WGPUColor() const { return WGPUColor{.r = red, .g = green, .b = blue, .a = alpha}; }
};

struct ECHIDNA_EXPORT command_buffer_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr command_buffer_descriptor(const WGPUCommandBufferDescriptor& cbd) :
        next(cbd.nextInChain), label(cbd.label) {}

    constexpr operator WGPUCommandBufferDescriptor() const {
        return WGPUCommandBufferDescriptor{.nextInChain = next, .label = label.c_str()};
    }
};

struct ECHIDNA_EXPORT command_encoder_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr command_encoder_descriptor(const WGPUCommandEncoderDescriptor& ced) :
        next(ced.nextInChain), label(ced.label) {}

    constexpr operator WGPUCommandEncoderDescriptor() const {
        return WGPUCommandEncoderDescriptor{.nextInChain = next, .label = label.c_str()};
    }
};

struct ECHIDNA_EXPORT compilation_message {
    const chained_struct* next;
    std::string message;
    compilation_message_type type;
    std::uint64_t line;
    std::uint64_t col;
    std::uint64_t offset;
    std::uint64_t length;
    std::uint64_t utf16_col;
    std::uint64_t utf16_offset;
    std::uint64_t utf16_length;

    constexpr compilation_message(const WGPUCompilationMessage& cm) :
        next(cm.nextInChain),
        message(cm.message),
        type(static_cast<compilation_message_type>(cm.type)),
        line(cm.lineNum),
        col(cm.linePos),
        offset(cm.offset),
        length(cm.length),
        utf16_col(cm.utf16LinePos),
        utf16_offset(cm.utf16Offset),
        utf16_length(cm.utf16Length) {}

    constexpr operator WGPUCompilationMessage() const {
        return WGPUCompilationMessage{
            .nextInChain  = next,
            .type         = static_cast<WGPUCompilationMessageType>(type),
            .lineNum      = line,
            .linePos      = col,
            .offset       = offset,
            .length       = length,
            .utf16LinePos = utf16_col,
            .utf16Offset  = utf16_offset,
            .utf16Length  = utf16_length,
        };
    }
};

struct ECHIDNA_EXPORT compute_pass_timestamp_writes {
    query_set set;
    std::uint32_t beginning_index;
    std::uint32_t end_index;

    constexpr compute_pass_timestamp_writes(const WGPUComputePassTimestampWrites& ctw) :
        set(ctw.querySet), beginning_index(ctw.beginningOfPassWriteIndex), end_index(ctw.endOfPassWriteIndex) {}

    constexpr operator WGPUComputePassTimestampWrites() const {
        return WGPUComputePassTimestampWrites{
            .querySet                  = set,
            .beginningOfPassWriteIndex = beginning_index,
            .endOfPassWriteIndex       = end_index,
        };
    }
};

struct ECHIDNA_EXPORT constant_entry {
    const chained_struct* next;
    std::string key;
    double value;

    constant_entry(const WGPUConstantEntry& e) : next(e.nextInChain), key(e.key), value(e.value) {}

    constexpr operator WGPUConstantEntry() const {
        return WGPUConstantEntry{
            .nextInChain = next,
            .key         = key.c_str(),
            .value       = value,
        };
    }
};

struct ECHIDNA_EXPORT extent3d {
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t depth;

    constexpr extent3d(const WGPUExtent3D& e) : width(e.width), height(e.height), depth(e.depthOrArrayLayers) {}

    constexpr operator WGPUExtent3D() const {
        return WGPUExtent3D{.width = width, .height = height, .depthOrArrayLayers = depth};
    }
};

struct ECHIDNA_EXPORT instance_descriptor {
    const chained_struct* next;

    constexpr instance_descriptor(const WGPUInstanceDescriptor& i) : next((i.nextInChain)) {}

    constexpr operator WGPUInstanceDescriptor() const { return WGPUInstanceDescriptor{.nextInChain = next}; }
};

struct ECHIDNA_EXPORT limits {
    std::uint32_t max_texture_dimension_1d;
    std::uint32_t max_texture_dimension_2d;
    std::uint32_t max_texture_dimension_3d;
    std::uint32_t max_texture_array_layers;
    std::uint32_t max_bind_groups;
    std::uint32_t max_bind_groups_plus_vertex_buffers;
    std::uint32_t max_bindings_per_group;
    std::uint32_t max_dynamic_uniform_buffers_per_pipeline_layout;
    std::uint32_t max_dynamic_storage_buffers_per_pipeline_layout;
    std::uint32_t max_sampled_textures_per_shader_stage;
    std::uint32_t max_samplers_per_shader_stage;
    std::uint32_t max_storage_buffers_per_shader_stage;
    std::uint32_t max_storage_textures_per_shader_stage;
    std::uint32_t max_uniform_buffers_per_shader_stage;
    std::uint64_t max_uniform_buffer_binding_size;
    std::uint64_t max_storage_buffer_binding_size;
    std::uint32_t min_uniform_buffer_offset_alignment;
    std::uint32_t min_storage_buffer_offset_alignment;
    std::uint32_t max_vertex_buffers;
    std::uint64_t max_buffer_size;
    std::uint32_t max_vertex_attributes;
    std::uint32_t max_vertex_buffer_array_stride;
    std::uint32_t max_inter_stage_shader_components;
    std::uint32_t max_inter_stage_shader_variables;
    std::uint32_t max_color_attachments;
    std::uint32_t max_color_attachment_bytes_per_sample;
    std::uint32_t max_compute_workgroup_storage_size;
    std::uint32_t max_compute_invocations_per_workgroup;
    std::uint32_t max_compute_workgroup_size_X;
    std::uint32_t max_compute_workgroup_size_Y;
    std::uint32_t max_compute_workgroup_size_Z;
    std::uint32_t max_compute_workgroups_per_dimension;

    constexpr limits(const WGPULimits& lim) :
        max_texture_dimension_1d(lim.maxTextureDimension1D),
        max_texture_dimension_2d(lim.maxTextureDimension2D),
        max_texture_dimension_3d(lim.maxTextureDimension3D),
        max_texture_array_layers(lim.maxTextureArrayLayers),
        max_bind_groups(lim.maxBindGroups),
        max_bind_groups_plus_vertex_buffers(lim.maxBindGroupsPlusVertexBuffers),
        max_bindings_per_group(lim.maxBindingsPerBindGroup),
        max_dynamic_uniform_buffers_per_pipeline_layout(lim.maxDynamicUniformBuffersPerPipelineLayout),
        max_dynamic_storage_buffers_per_pipeline_layout(lim.maxDynamicStorageBuffersPerPipelineLayout),
        max_sampled_textures_per_shader_stage(lim.maxSampledTexturesPerShaderStage),
        max_samplers_per_shader_stage(lim.maxSamplersPerShaderStage),
        max_storage_buffers_per_shader_stage(lim.maxStorageBuffersPerShaderStage),
        max_storage_textures_per_shader_stage(lim.maxStorageTexturesPerShaderStage),
        max_uniform_buffers_per_shader_stage(lim.maxUniformBuffersPerShaderStage),
        max_uniform_buffer_binding_size(lim.maxUniformBufferBindingSize),
        max_storage_buffer_binding_size(lim.maxStorageBufferBindingSize),
        min_uniform_buffer_offset_alignment(lim.minUniformBufferOffsetAlignment),
        min_storage_buffer_offset_alignment(lim.minStorageBufferOffsetAlignment),
        max_vertex_buffers(lim.maxVertexBuffers),
        max_buffer_size(lim.maxBufferSize),
        max_vertex_attributes(lim.maxVertexAttributes),
        max_vertex_buffer_array_stride(lim.maxVertexBufferArrayStride),
        max_inter_stage_shader_components(lim.maxInterStageShaderComponents),
        max_inter_stage_shader_variables(lim.maxInterStageShaderVariables),
        max_color_attachments(lim.maxColorAttachments),
        max_color_attachment_bytes_per_sample(lim.maxColorAttachmentBytesPerSample),
        max_compute_workgroup_storage_size(lim.maxComputeWorkgroupStorageSize),
        max_compute_invocations_per_workgroup(lim.maxComputeInvocationsPerWorkgroup),
        max_compute_workgroup_size_X(lim.maxComputeWorkgroupSizeX),
        max_compute_workgroup_size_Y(lim.maxComputeWorkgroupSizeY),
        max_compute_workgroup_size_Z(lim.maxComputeWorkgroupSizeZ),
        max_compute_workgroups_per_dimension(lim.maxComputeWorkgroupsPerDimension) {}

    constexpr operator WGPULimits() const {
        return WGPULimits{
            .maxTextureDimension1D                     = max_texture_dimension_1d,
            .maxTextureDimension2D                     = max_texture_dimension_2d,
            .maxTextureDimension3D                     = max_texture_dimension_3d,
            .maxTextureArrayLayers                     = max_texture_array_layers,
            .maxBindGroups                             = max_bind_groups,
            .maxBindGroupsPlusVertexBuffers            = max_bind_groups_plus_vertex_buffers,
            .maxBindingsPerBindGroup                   = max_bindings_per_group,
            .maxDynamicUniformBuffersPerPipelineLayout = max_dynamic_uniform_buffers_per_pipeline_layout,
            .maxDynamicStorageBuffersPerPipelineLayout = max_dynamic_storage_buffers_per_pipeline_layout,
            .maxSampledTexturesPerShaderStage          = max_sampled_textures_per_shader_stage,
            .maxSamplersPerShaderStage                 = max_samplers_per_shader_stage,
            .maxStorageBuffersPerShaderStage           = max_storage_buffers_per_shader_stage,
            .maxStorageTexturesPerShaderStage          = max_storage_textures_per_shader_stage,
            .maxUniformBuffersPerShaderStage           = max_uniform_buffers_per_shader_stage,
            .maxUniformBufferBindingSize               = max_uniform_buffer_binding_size,
            .maxStorageBufferBindingSize               = max_storage_buffer_binding_size,
            .minUniformBufferOffsetAlignment           = min_uniform_buffer_offset_alignment,
            .minStorageBufferOffsetAlignment           = min_storage_buffer_offset_alignment,
            .maxVertexBuffers                          = max_vertex_buffers,
            .maxBufferSize                             = max_buffer_size,
            .maxVertexAttributes                       = max_vertex_attributes,
            .maxVertexBufferArrayStride                = max_vertex_buffer_array_stride,
            .maxInterStageShaderComponents             = max_inter_stage_shader_components,
            .maxInterStageShaderVariables              = max_inter_stage_shader_variables,
            .maxColorAttachments                       = max_color_attachments,
            .maxColorAttachmentBytesPerSample          = max_color_attachment_bytes_per_sample,
            .maxComputeWorkgroupStorageSize            = max_compute_workgroup_storage_size,
            .maxComputeInvocationsPerWorkgroup         = max_compute_invocations_per_workgroup,
            .maxComputeWorkgroupSizeX                  = max_compute_workgroup_size_X,
            .maxComputeWorkgroupSizeY                  = max_compute_workgroup_size_Y,
            .maxComputeWorkgroupSizeZ                  = max_compute_workgroup_size_Z,
            .maxComputeWorkgroupsPerDimension          = max_compute_workgroups_per_dimension,
        };
    }
};

struct ECHIDNA_EXPORT multisample_state {
    const chained_struct* next;
    std::uint32_t count;
    std::uint32_t mask;
    bool alpha_to_coverage_enabled;

    constexpr multisample_state(const WGPUMultisampleState& s) :
        next(s.nextInChain),
        count(s.count),
        mask(s.mask),
        alpha_to_coverage_enabled(static_cast<bool>(s.alphaToCoverageEnabled)) {}

    constexpr operator WGPUMultisampleState() const {
        return WGPUMultisampleState{
            .nextInChain            = next,
            .count                  = count,
            .mask                   = mask,
            .alphaToCoverageEnabled = static_cast<WGPUBool>(alpha_to_coverage_enabled),
        };
    }
};

struct ECHIDNA_EXPORT origin3d {
    std::uint32_t x;
    std::uint32_t y;
    std::uint32_t z;

    constexpr origin3d(const WGPUOrigin3D& o) : x(o.x), y(o.y), z(o.z) {}
    constexpr operator WGPUOrigin3D() const { return WGPUOrigin3D{.x = x, .y = y, .z = z}; }
};

class pipeline_layout_descriptor {
    std::vector<WGPUBindGroupLayout> wgpu_layouts;

    constexpr auto get_wgpu_layouts() -> std::vector<WGPUBindGroupLayout> {
        wgpu_layouts = std::vector<WGPUBindGroupLayout>(layouts.begin(), layouts.end());
        return wgpu_layouts;
    }

public:
    const chained_struct* next;
    std::string label;
    std::vector<bind_group_layout> layouts;

    constexpr pipeline_layout_descriptor(const WGPUPipelineLayoutDescriptor& pld) :
        next(pld.nextInChain),
        label(pld.label),
        layouts(pld.bindGroupLayouts, pld.bindGroupLayouts + pld.bindGroupLayoutCount) {}

    constexpr operator WGPUPipelineLayoutDescriptor() {
        return WGPUPipelineLayoutDescriptor{
            .nextInChain          = next,
            .label                = label.c_str(),
            .bindGroupLayoutCount = layouts.size(),
            .bindGroupLayouts     = this->get_wgpu_layouts().data(),
        };
    }
};

struct ECHIDNA_EXPORT primitive_depth_clip_control {
    chained_struct chain;
    bool unclipped_depth;

    constexpr primitive_depth_clip_control(WGPUPrimitiveDepthClipControl& pdc) :
        chain(pdc.chain), unclipped_depth(static_cast<bool>(pdc.unclippedDepth)) {}

    constexpr operator WGPUPrimitiveDepthClipControl() const {
        return WGPUPrimitiveDepthClipControl{
            .chain          = chain,
            .unclippedDepth = static_cast<WGPUBool>(unclipped_depth),
        };
    }
};

struct ECHIDNA_EXPORT primitive_state {
    const chained_struct* next;
    primitive_topology topology;
    index_format strip_index_format;
    front_face front_face;
    cull_mode cull_mode;

    constexpr primitive_state(const WGPUPrimitiveState& p) :
        next((p.nextInChain)),
        topology(static_cast<primitive_topology>(p.topology)),
        strip_index_format(static_cast<index_format>(p.stripIndexFormat)),
        front_face(static_cast<echidna::webgpu::front_face>(p.frontFace)),
        cull_mode(static_cast<echidna::webgpu::cull_mode>(p.cullMode)) {}

    constexpr operator WGPUPrimitiveState() const {
        return WGPUPrimitiveState{
            .nextInChain      = next,
            .topology         = static_cast<WGPUPrimitiveTopology>(topology),
            .stripIndexFormat = static_cast<WGPUIndexFormat>(strip_index_format),
            .frontFace        = static_cast<WGPUFrontFace>(front_face),
            .cullMode         = static_cast<WGPUCullMode>(cull_mode),
        };
    }
};

struct ECHIDNA_EXPORT query_set_descriptor {
    const chained_struct* next;
    std::string label;
    query_type type;
    std::uint32_t count;

    constexpr query_set_descriptor(const WGPUQuerySetDescriptor& q) :
        next(q.nextInChain), label(q.label), type(static_cast<query_type>(q.type)), count(q.count) {}

    constexpr operator WGPUQuerySetDescriptor() const {
        return WGPUQuerySetDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .type        = static_cast<WGPUQueryType>(type),
            .count       = count,
        };
    }
};

struct ECHIDNA_EXPORT queue_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr queue_descriptor(const WGPUQueueDescriptor& q) : next(q.nextInChain), label(q.label) {}
    constexpr operator WGPUQueueDescriptor() { return {.nextInChain = next, .label = label.c_str()}; }
};

struct ECHIDNA_EXPORT render_bundle_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr render_bundle_descriptor(const WGPURenderBundleDescriptor& q) : next(q.nextInChain), label(q.label) {}
    constexpr operator WGPURenderBundleDescriptor() const { return {.nextInChain = next, .label = label.c_str()}; }
};

struct ECHIDNA_EXPORT render_pass_depth_stencil_attachment {
    texture_view view;
    load_op depth_load_op;
    store_op depth_store_op;
    float depth_clear_value;
    bool depth_read_only;
    load_op stencil_load_op;
    store_op stencil_store_op;
    std::uint32_t stencil_clear_value;
    bool stencil_read_only;

    constexpr render_pass_depth_stencil_attachment(const WGPURenderPassDepthStencilAttachment& a) :
        view(a.view),
        depth_load_op(static_cast<load_op>(a.depthLoadOp)),
        depth_store_op(static_cast<store_op>(a.depthStoreOp)),
        depth_clear_value(a.depthClearValue),
        depth_read_only(static_cast<bool>(a.depthReadOnly)),
        stencil_load_op(static_cast<load_op>(a.stencilLoadOp)),
        stencil_store_op(static_cast<store_op>(a.stencilStoreOp)),
        stencil_clear_value(a.stencilClearValue),
        stencil_read_only(static_cast<bool>(a.stencilReadOnly)) {}

    constexpr operator WGPURenderPassDepthStencilAttachment() const {
        return WGPURenderPassDepthStencilAttachment{
            .view              = view,
            .depthLoadOp       = static_cast<WGPULoadOp>(depth_load_op),
            .depthStoreOp      = static_cast<WGPUStoreOp>(depth_store_op),
            .depthClearValue   = depth_clear_value,
            .depthReadOnly     = static_cast<WGPUBool>(depth_read_only),
            .stencilLoadOp     = static_cast<WGPULoadOp>(stencil_load_op),
            .stencilStoreOp    = static_cast<WGPUStoreOp>(stencil_store_op),
            .stencilClearValue = stencil_clear_value,
            .stencilReadOnly   = static_cast<WGPUBool>(stencil_read_only),
        };
    }
};

struct ECHIDNA_EXPORT render_pass_descriptor_max_draw_count {
    chained_struct chain;
    std::uint64_t max_draw_count;

    constexpr render_pass_descriptor_max_draw_count(const WGPURenderPassDescriptorMaxDrawCount& mdc) :
        chain(mdc.chain), max_draw_count(mdc.maxDrawCount) {}

    constexpr operator WGPURenderPassDescriptorMaxDrawCount() const {
        return WGPURenderPassDescriptorMaxDrawCount{
            .chain        = chain,
            .maxDrawCount = max_draw_count,
        };
    }
};

struct ECHIDNA_EXPORT render_pass_timestamp_writes {
    query_set set;
    std::uint32_t beginning_index;
    std::uint32_t end_index;

    constexpr render_pass_timestamp_writes(const WGPURenderPassTimestampWrites& w) :
        set(w.querySet), beginning_index(w.beginningOfPassWriteIndex), end_index(w.endOfPassWriteIndex) {}

    constexpr operator WGPURenderPassTimestampWrites() const {
        return WGPURenderPassTimestampWrites{
            .querySet                  = set,
            .beginningOfPassWriteIndex = beginning_index,
            .endOfPassWriteIndex       = end_index,
        };
    }
};

struct ECHIDNA_EXPORT request_adapter_options {
    const chained_struct* next;
    surface compatible_surface;
    power_preference power_preference;
    backend_type backend;
    bool force_fallback;

    constexpr request_adapter_options(const WGPURequestAdapterOptions& o) :
        next(o.nextInChain),
        compatible_surface(o.compatibleSurface),
        power_preference(static_cast<echidna::webgpu::power_preference>(o.powerPreference)),
        backend(static_cast<backend_type>(o.backendType)),
        force_fallback(static_cast<bool>(o.forceFallbackAdapter)) {}

    constexpr operator WGPURequestAdapterOptions() {
        return WGPURequestAdapterOptions{
            .nextInChain          = next,
            .compatibleSurface    = compatible_surface,
            .powerPreference      = static_cast<WGPUPowerPreference>(power_preference),
            .backendType          = static_cast<WGPUBackendType>(backend),
            .forceFallbackAdapter = static_cast<WGPUBool>(force_fallback),
        };
    }
};

struct ECHIDNA_EXPORT sampler_binding_layout {
    const chained_struct* next;
    sampler_binding_type type;

    constexpr sampler_binding_layout(const WGPUSamplerBindingLayout& l) :
        next(l.nextInChain), type(static_cast<sampler_binding_type>(l.type)) {}

    constexpr operator WGPUSamplerBindingLayout() const {
        return WGPUSamplerBindingLayout{
            .nextInChain = next,
            .type        = static_cast<WGPUSamplerBindingType>(type),
        };
    }
};

struct ECHIDNA_EXPORT sampler_descriptor {
    const chained_struct* next;
    std::string label;
    address_mode address_mode_u;
    address_mode address_mode_v;
    address_mode address_mode_w;
    filter_mode mag_filter;
    filter_mode min_filter;
    mipmap_filter_mode mip_map_filter;
    float lod_min_clamp;
    float lod_max_clamp;
    compare_function compare;
    std::uint16_t max_anisotropy;

    constexpr sampler_descriptor(const WGPUSamplerDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        address_mode_u(static_cast<address_mode>(d.addressModeU)),
        address_mode_v(static_cast<address_mode>(d.addressModeV)),
        address_mode_w(static_cast<address_mode>(d.addressModeW)),
        mag_filter(static_cast<filter_mode>(d.magFilter)),
        min_filter(static_cast<filter_mode>(d.minFilter)),
        mip_map_filter(static_cast<mipmap_filter_mode>(d.mipmapFilter)),
        lod_min_clamp(d.lodMinClamp),
        lod_max_clamp(d.lodMaxClamp),
        compare(static_cast<compare_function>(d.compare)),
        max_anisotropy(d.maxAnisotropy) {}

    constexpr operator WGPUSamplerDescriptor() const {
        return WGPUSamplerDescriptor{
            .nextInChain   = next,
            .label         = label.c_str(),
            .addressModeU  = static_cast<WGPUAddressMode>(address_mode_u),
            .addressModeV  = static_cast<WGPUAddressMode>(address_mode_v),
            .addressModeW  = static_cast<WGPUAddressMode>(address_mode_w),
            .magFilter     = static_cast<WGPUFilterMode>(mag_filter),
            .minFilter     = static_cast<WGPUFilterMode>(min_filter),
            .mipmapFilter  = static_cast<WGPUMipmapFilterMode>(mip_map_filter),
            .lodMinClamp   = lod_min_clamp,
            .lodMaxClamp   = lod_max_clamp,
            .compare       = static_cast<WGPUCompareFunction>(compare),
            .maxAnisotropy = max_anisotropy,
        };
    }
};

struct ECHIDNA_EXPORT shader_module_compilation_hint {
    const chained_struct* next;
    std::string entry_point;
    pipeline_layout layout;

    constexpr shader_module_compilation_hint(const WGPUShaderModuleCompilationHint& h) :
        next(h.nextInChain), entry_point(h.entryPoint), layout(h.layout) {}

    constexpr operator WGPUShaderModuleCompilationHint() const {
        return WGPUShaderModuleCompilationHint{
            .nextInChain = next,
            .entryPoint  = entry_point.c_str(),
            .layout      = layout,
        };
    }
};

struct ECHIDNA_EXPORT shader_module_spirv_descriptor {
    chained_struct chain;
    std::uint32_t size;
    const std::uint32_t* code;

    constexpr shader_module_spirv_descriptor(const WGPUShaderModuleSPIRVDescriptor& d) :
        chain(d.chain), size(d.codeSize), code(d.code) {}

    constexpr operator WGPUShaderModuleSPIRVDescriptor() const {
        return WGPUShaderModuleSPIRVDescriptor{
            .chain    = chain,
            .codeSize = size,
            .code     = code,
        };
    }
};

struct ECHIDNA_EXPORT shader_module_wgsl_descriptor {
    chained_struct chain;
    std::string code;

    constexpr shader_module_wgsl_descriptor(const WGPUShaderModuleWGSLDescriptor& d) : chain(d.chain), code(d.code) {}
    constexpr operator WGPUShaderModuleWGSLDescriptor() const { return {.chain = chain, .code = code.c_str()}; }
};

struct ECHIDNA_EXPORT stencil_face_state {
    compare_function compare;
    stencil_op fail;
    stencil_op depth_fail;
    stencil_op pass;

    constexpr stencil_face_state(const WGPUStencilFaceState& s) :
        compare(static_cast<compare_function>(s.compare)),
        fail(static_cast<stencil_op>(s.failOp)),
        depth_fail(static_cast<stencil_op>(s.depthFailOp)),
        pass(static_cast<stencil_op>(s.passOp)) {}

    constexpr operator WGPUStencilFaceState() const {
        return WGPUStencilFaceState{
            .compare     = static_cast<WGPUCompareFunction>(compare),
            .failOp      = static_cast<WGPUStencilOperation>(fail),
            .depthFailOp = static_cast<WGPUStencilOperation>(depth_fail),
            .passOp      = static_cast<WGPUStencilOperation>(pass),
        };
    }
};

struct ECHIDNA_EXPORT storage_texture_binding_layout {
    const chained_struct* next;
    storage_texture_access access;
    texture_format format;
    texture_view_dimension view_dimension;

    constexpr storage_texture_binding_layout(const WGPUStorageTextureBindingLayout& l) :
        next(l.nextInChain),
        access(static_cast<storage_texture_access>(l.access)),
        format(static_cast<texture_format>(l.format)),
        view_dimension(static_cast<texture_view_dimension>(l.viewDimension)) {}

    constexpr operator WGPUStorageTextureBindingLayout() const {
        return WGPUStorageTextureBindingLayout{
            .nextInChain   = next,
            .access        = static_cast<WGPUStorageTextureAccess>(access),
            .format        = static_cast<WGPUTextureFormat>(format),
            .viewDimension = static_cast<WGPUTextureViewDimension>(view_dimension),
        };
    }
};

class surface_capabilities {
    std::vector<WGPUTextureFormat> wgpu_fmts;
    std::vector<WGPUPresentMode> wgpu_pm;
    std::vector<WGPUCompositeAlphaMode> wgpu_cam;

    constexpr auto get_wgpu_fmts() {
        std::transform(formats.begin(), formats.end(), std::back_inserter(wgpu_fmts), [](auto f) {
            return static_cast<WGPUTextureFormat>(f);
        });
        return wgpu_fmts;
    }

    constexpr auto get_wgpu_pm() {
        std::transform(present_modes.begin(), present_modes.end(), std::back_inserter(wgpu_pm), [](auto pm) {
            return static_cast<WGPUPresentMode>(pm);
        });
        return wgpu_pm;
    }

    constexpr auto get_wgpu_cam() {
        std::transform(formats.begin(), formats.end(), std::back_inserter(wgpu_cam), [](auto am) {
            return static_cast<WGPUCompositeAlphaMode>(am);
        });
        return wgpu_cam;
    }

public:
    std::vector<texture_format> formats;
    std::vector<present_mode> present_modes;
    std::vector<composite_alpha_mode> alpha_modes;

    constexpr surface_capabilities(const WGPUSurfaceCapabilities& c) {
        std::transform(c.formats, c.formats + c.formatCount, std::back_inserter(formats), [](auto f) {
            return static_cast<texture_format>(f);
        });

        std::transform(
            c.presentModes,
            c.presentModes + c.presentModeCount,
            std::back_inserter(present_modes),
            [](auto pm) { return static_cast<present_mode>(pm); }
        );

        std::transform(c.alphaModes, c.alphaModes + c.alphaModeCount, std::back_inserter(alpha_modes), [](auto am) {
            return static_cast<composite_alpha_mode>(am);
        });
    }
};

class surface_configuration {
    std::vector<WGPUTextureFormat> wgpu_formats;

    constexpr auto get_wgpu_formats() -> std::vector<WGPUTextureFormat> {
        std::transform(view_formats.begin(), view_formats.end(), std::back_inserter(wgpu_formats), [](auto f) {
            return static_cast<WGPUTextureFormat>(f);
        });

        return wgpu_formats;
    }

public:
    const chained_struct* next;
    device device;
    texture_format format;
    texture_usage usage;
    std::vector<texture_format> view_formats;
    composite_alpha_mode alpha_mode;
    std::uint32_t width;
    std::uint32_t height;
    present_mode present_mode;

    constexpr surface_configuration(const WGPUSurfaceConfiguration& c) :
        next(c.nextInChain),
        device(c.device),
        format(static_cast<texture_format>(c.format)),
        usage(static_cast<texture_usage>(c.usage)),
        alpha_mode(static_cast<composite_alpha_mode>(c.alphaMode)),
        width(c.width),
        height(c.height),
        present_mode(static_cast<echidna::webgpu::present_mode>(c.presentMode)) {

        std::transform(c.viewFormats, c.viewFormats + c.viewFormatCount, std::back_inserter(view_formats), [](auto vf) {
            return static_cast<texture_format>(vf);
        });
    }

    constexpr operator WGPUSurfaceConfiguration() {
        return WGPUSurfaceConfiguration{
            .nextInChain     = next,
            .device          = device,
            .format          = static_cast<WGPUTextureFormat>(format),
            .usage           = static_cast<WGPUTextureUsage>(usage),
            .viewFormatCount = view_formats.size(),
            .viewFormats     = this->get_wgpu_formats().data(),
            .alphaMode       = static_cast<WGPUCompositeAlphaMode>(alpha_mode),
            .width           = width,
            .height          = height,
            .presentMode     = static_cast<WGPUPresentMode>(present_mode),
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr surface_descriptor(const WGPUSurfaceDescriptor& d) : next(d.nextInChain), label(d.label) {}
    constexpr operator WGPUSurfaceDescriptor() { return {.nextInChain = next, .label = label.c_str()}; }
};

struct ECHIDNA_EXPORT surface_descriptor_from_android_native_window {
    chained_struct chain;
    void* window;

    constexpr surface_descriptor_from_android_native_window(const WGPUSurfaceDescriptorFromAndroidNativeWindow& d) :
        chain(d.chain), window(d.window) {}

    constexpr operator WGPUSurfaceDescriptorFromAndroidNativeWindow() {
        return WGPUSurfaceDescriptorFromAndroidNativeWindow{
            .chain  = chain,
            .window = window,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_canvas_html_selector {
    chained_struct chain;
    std::string selector;

    constexpr surface_descriptor_from_canvas_html_selector(const WGPUSurfaceDescriptorFromCanvasHTMLSelector& d) :
        chain(d.chain), selector(d.selector) {}

    constexpr operator WGPUSurfaceDescriptorFromCanvasHTMLSelector() {
        return WGPUSurfaceDescriptorFromCanvasHTMLSelector{
            .chain    = chain,
            .selector = selector.c_str(),
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_metal_layer {
    chained_struct chain;
    void* layer;

    constexpr surface_descriptor_from_metal_layer(const WGPUSurfaceDescriptorFromMetalLayer& d) :
        chain(d.chain), layer(d.layer) {}

    constexpr operator WGPUSurfaceDescriptorFromMetalLayer() {
        return WGPUSurfaceDescriptorFromMetalLayer{
            .chain = chain,
            .layer = layer,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_wayland_surface {
    chained_struct chain;
    void* display;
    void* surface;

    constexpr surface_descriptor_from_wayland_surface(const WGPUSurfaceDescriptorFromWaylandSurface& d) :
        chain(d.chain), display(d.display), surface(d.surface) {}

    constexpr operator WGPUSurfaceDescriptorFromWaylandSurface() {
        return WGPUSurfaceDescriptorFromWaylandSurface{
            .chain   = chain,
            .display = display,
            .surface = surface,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_windows_hwnd {
    chained_struct chain;
    void* instance;
    void* hwnd;

    constexpr surface_descriptor_from_windows_hwnd(const WGPUSurfaceDescriptorFromWindowsHWND& d) :
        chain(d.chain), instance(d.hinstance), hwnd(d.hwnd) {}

    constexpr operator WGPUSurfaceDescriptorFromWindowsHWND() {
        return WGPUSurfaceDescriptorFromWindowsHWND{
            .chain     = chain,
            .hinstance = instance,
            .hwnd      = hwnd,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_xcb_window {
    chained_struct chain;
    void* connection;
    std::uint32_t window;

    constexpr surface_descriptor_from_xcb_window(const WGPUSurfaceDescriptorFromXcbWindow& d) :
        chain(d.chain), connection(d.connection), window(d.window) {}

    constexpr operator WGPUSurfaceDescriptorFromXcbWindow() {
        return WGPUSurfaceDescriptorFromXcbWindow{
            .chain      = chain,
            .connection = connection,
            .window     = window,
        };
    }
};

struct ECHIDNA_EXPORT surface_descriptor_from_xlib_window {
    chained_struct chain;
    void* display;
    std::uint64_t window;

    constexpr surface_descriptor_from_xlib_window(const WGPUSurfaceDescriptorFromXlibWindow& d) :
        chain(d.chain), display(d.display), window(d.window) {}

    constexpr operator WGPUSurfaceDescriptorFromXlibWindow() {
        return WGPUSurfaceDescriptorFromXlibWindow{
            .chain   = chain,
            .display = display,
            .window  = window,
        };
    }
};

struct ECHIDNA_EXPORT texture_binding_layout {
    const chained_struct* next;
    texture_sample_type sample_type;
    texture_view_dimension view_dimension;
    bool multisampled;

    constexpr texture_binding_layout(const WGPUTextureBindingLayout& l) :
        next(l.nextInChain),
        sample_type(static_cast<texture_sample_type>(l.sampleType)),
        view_dimension(static_cast<texture_view_dimension>(l.viewDimension)),
        multisampled(static_cast<bool>(l.multisampled)) {}

    constexpr operator WGPUTextureBindingLayout() const {
        return WGPUTextureBindingLayout{
            .nextInChain   = next,
            .sampleType    = static_cast<WGPUTextureSampleType>(sample_type),
            .viewDimension = static_cast<WGPUTextureViewDimension>(view_dimension),
            .multisampled  = static_cast<WGPUBool>(multisampled),
        };
    }
};

struct ECHIDNA_EXPORT texture_data_layout {
    const chained_struct* next;
    std::uint64_t offset;
    std::uint32_t bytes_per_row;
    std::uint32_t rows_per_image;

    constexpr texture_data_layout(const WGPUTextureDataLayout& l) :
        next(l.nextInChain), offset(l.offset), bytes_per_row(l.bytesPerRow), rows_per_image(l.rowsPerImage) {}
    constexpr operator WGPUTextureDataLayout() {
        return WGPUTextureDataLayout{
            .nextInChain  = next,
            .offset       = offset,
            .bytesPerRow  = bytes_per_row,
            .rowsPerImage = rows_per_image,
        };
    }
};

struct ECHIDNA_EXPORT texture_view_descriptor {
    const chained_struct* next;
    std::string label;
    texture_format format;
    texture_view_dimension dimension;
    std::uint32_t base_mip_level;
    std::uint32_t mip_level_count;
    std::uint32_t base_array_layer;
    std::uint32_t array_layer_count;
    texture_aspect aspect;

    constexpr texture_view_descriptor(const WGPUTextureViewDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        format(static_cast<texture_format>(d.format)),
        dimension(static_cast<texture_view_dimension>(d.dimension)),
        base_mip_level(d.baseMipLevel),
        mip_level_count(d.mipLevelCount),
        base_array_layer(d.baseArrayLayer),
        array_layer_count(d.arrayLayerCount),
        aspect(static_cast<texture_aspect>(d.aspect)) {}

    constexpr operator WGPUTextureViewDescriptor() {
        return WGPUTextureViewDescriptor{
            .nextInChain     = next,
            .label           = label.c_str(),
            .format          = static_cast<WGPUTextureFormat>(format),
            .dimension       = static_cast<WGPUTextureViewDimension>(dimension),
            .baseMipLevel    = base_mip_level,
            .mipLevelCount   = mip_level_count,
            .baseArrayLayer  = base_array_layer,
            .arrayLayerCount = array_layer_count,
            .aspect          = static_cast<WGPUTextureAspect>(aspect),
        };
    }
};

struct ECHIDNA_EXPORT vertex_attribute {
    vertex_format format;
    std::uint64_t offset;
    std::uint32_t shader_location;

    constexpr vertex_attribute(const WGPUVertexAttribute& a) :
        format(static_cast<vertex_format>(a.format)), offset(a.offset), shader_location(a.shaderLocation) {}

    constexpr operator WGPUVertexAttribute() {
        return WGPUVertexAttribute{
            .format         = static_cast<WGPUVertexFormat>(format),
            .offset         = offset,
            .shaderLocation = shader_location,
        };
    }
};

class bind_group_descriptor {
    std::vector<WGPUBindGroupEntry> wgpu_entries;

    constexpr auto get_wgpu_entries() {
        wgpu_entries = std::vector<WGPUBindGroupEntry>(entries.begin(), entries.end());
        return wgpu_entries;
    }

public:
    const chained_struct* next;
    std::string label;
    bind_group_layout layout;
    std::vector<bind_group_entry> entries;

    constexpr bind_group_descriptor(const WGPUBindGroupDescriptor& d) :
        next(d.nextInChain), label(d.label), entries(d.entries, d.entries + d.entryCount) {}

    constexpr operator WGPUBindGroupDescriptor() {
        return WGPUBindGroupDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .entryCount  = entries.size(),
            .entries     = this->get_wgpu_entries().data(),
        };
    }
};

struct ECHIDNA_EXPORT bind_group_layout_entry {
    const chained_struct* next;
    std::uint32_t binding;
    shader_stage visibility;
    buffer_binding_layout buffer;
    sampler_binding_layout sampler;
    texture_binding_layout texture;
    storage_texture_binding_layout storage_texture;

    constexpr bind_group_layout_entry(const WGPUBindGroupLayoutEntry& e) :
        next(e.nextInChain),
        binding(e.binding),
        visibility(static_cast<shader_stage>(e.visibility)),
        buffer(e.buffer),
        sampler(e.sampler),
        texture(e.texture),
        storage_texture(e.storageTexture) {}

    constexpr operator WGPUBindGroupLayoutEntry() {
        return WGPUBindGroupLayoutEntry{
            .nextInChain    = next,
            .binding        = binding,
            .visibility     = static_cast<WGPUShaderStage>(visibility),
            .buffer         = buffer,
            .sampler        = sampler,
            .texture        = texture,
            .storageTexture = storage_texture,
        };
    }
};

struct ECHIDNA_EXPORT blend_state {
    blend_component color;
    blend_component alpha;

    constexpr blend_state(const WGPUBlendState& s) : color(s.color), alpha(s.alpha) {}
    constexpr operator WGPUBlendState() { return {.color = color, .alpha = alpha}; }
};

class compilation_info {
    std::vector<WGPUCompilationMessage> wgpu_messages;

    constexpr auto get_wgpu_messages() {
        wgpu_messages = std::vector<WGPUCompilationMessage>(messages.begin(), messages.end());
        return wgpu_messages;
    }

public:
    const chained_struct* next;
    std::vector<compilation_message> messages;

    constexpr compilation_info(const WGPUCompilationInfo& i) :
        next(i.nextInChain), messages(i.messages, i.messages + i.messageCount) {}
};

// TODO: If timestamp_writes changes wgpu_tsw will be outdated
class compute_pass_descriptor {
    WGPUComputePassTimestampWrites wgpu_tsw;

    constexpr auto get_wgpu_tsw() {
        wgpu_tsw = timestamp_writes;
        return &wgpu_tsw;
    }

public:
    const chained_struct* next;
    std::string label;
    compute_pass_timestamp_writes timestamp_writes;

    constexpr compute_pass_descriptor(const WGPUComputePassDescriptor& d) :
        next(d.nextInChain), label(d.label), wgpu_tsw(*d.timestampWrites), timestamp_writes(*d.timestampWrites) {}

    operator WGPUComputePassDescriptor() {
        return WGPUComputePassDescriptor{
            .nextInChain     = next,
            .label           = label.c_str(),
            .timestampWrites = this->get_wgpu_tsw(),
        };
    }
};

struct ECHIDNA_EXPORT depth_stencil_state {
    const chained_struct* next;
    texture_format format;
    bool depth_write_enabled;
    compare_function depth_compare;
    stencil_face_state stencil_front;
    stencil_face_state stencil_back;
    std::uint32_t stencil_read_mask;
    std::uint32_t stencil_write_mask;
    std::int32_t depth_bias;
    float depth_bias_slope_scale;
    float depth_bias_clamp;

    constexpr depth_stencil_state(const WGPUDepthStencilState& s) :
        next(s.nextInChain),
        format(static_cast<texture_format>(s.format)),
        depth_write_enabled(static_cast<bool>(s.depthWriteEnabled)),
        depth_compare(static_cast<compare_function>(s.depthCompare)),
        stencil_front(s.stencilFront),
        stencil_back(s.stencilBack),
        stencil_read_mask(s.stencilReadMask),
        stencil_write_mask(s.stencilWriteMask),
        depth_bias(s.depthBias),
        depth_bias_slope_scale(s.depthBiasSlopeScale),
        depth_bias_clamp(s.depthBiasClamp) {}

    constexpr operator WGPUDepthStencilState() {
        return WGPUDepthStencilState{
            .nextInChain         = next,
            .depthWriteEnabled   = static_cast<WGPUBool>(depth_write_enabled),
            .depthCompare        = static_cast<WGPUCompareFunction>(depth_compare),
            .stencilFront        = stencil_front,
            .stencilBack         = stencil_back,
            .stencilReadMask     = stencil_read_mask,
            .stencilWriteMask    = stencil_write_mask,
            .depthBias           = depth_bias,
            .depthBiasSlopeScale = depth_bias_slope_scale,
            .depthBiasClamp      = depth_bias_clamp,
        };
    }
};

struct ECHIDNA_EXPORT image_copy_buffer {
    const chained_struct* next;
    texture_data_layout layout;
    buffer buffer;

    constexpr image_copy_buffer(const WGPUImageCopyBuffer& b) :
        next(b.nextInChain), layout(b.layout), buffer(b.buffer) {}

    constexpr operator WGPUImageCopyBuffer() {
        return WGPUImageCopyBuffer{
            .nextInChain = next,
            .layout      = layout,
            .buffer      = buffer,
        };
    }
};

struct ECHIDNA_EXPORT image_copy_texture {
    const chained_struct* next;
    texture texture;
    std::uint32_t mip_level;
    origin3d origin;
    texture_aspect aspect;

    constexpr image_copy_texture(const WGPUImageCopyTexture& b) :
        next(b.nextInChain),
        texture(b.texture),
        mip_level(b.mipLevel),
        origin(b.origin),
        aspect(static_cast<texture_aspect>(b.aspect)) {}

    constexpr operator WGPUImageCopyTexture() {
        return WGPUImageCopyTexture{
            .nextInChain = next,
            .texture     = texture,
            .mipLevel    = mip_level,
            .origin      = origin,
            .aspect      = static_cast<WGPUTextureAspect>(aspect),
        };
    }
};

class programmable_stage_descriptor {
    std::vector<WGPUConstantEntry> wgpu_constants;

    constexpr auto get_wgpu_entries() {
        wgpu_constants = std::vector<WGPUConstantEntry>(constants.begin(), constants.end());
        return wgpu_constants;
    }

public:
    const chained_struct* next;
    shader_module module;
    std::string entry_point;
    std::vector<constant_entry> constants;

    constexpr programmable_stage_descriptor(const WGPUProgrammableStageDescriptor& d) :
        next(d.nextInChain),
        module(d.module),
        entry_point(d.entryPoint),
        constants(d.constants, d.constants + d.constantCount) {}

    constexpr operator WGPUProgrammableStageDescriptor() {
        return WGPUProgrammableStageDescriptor{
            .nextInChain   = next,
            .module        = module,
            .entryPoint    = entry_point.c_str(),
            .constantCount = constants.size(),
            .constants     = this->get_wgpu_entries().data(),
        };
    }
};

struct ECHIDNA_EXPORT render_pass_color_attachment {
    const chained_struct* next;
    texture_view view;
    texture_view resolve_target;
    load_op load_op;
    store_op store_op;
    color clear_value;

    constexpr render_pass_color_attachment(const WGPURenderPassColorAttachment& a) :
        next(a.nextInChain),
        view(a.view),
        resolve_target(a.resolveTarget),
        load_op(static_cast<echidna::webgpu::load_op>(a.loadOp)),
        store_op(static_cast<echidna::webgpu::store_op>(a.storeOp)),
        clear_value(a.clearValue) {}

    constexpr operator WGPURenderPassColorAttachment() {
        return WGPURenderPassColorAttachment{
            .nextInChain   = next,
            .view          = view,
            .resolveTarget = resolve_target,
            .loadOp        = static_cast<WGPULoadOp>(load_op),
            .storeOp       = static_cast<WGPUStoreOp>(store_op),
            .clearValue    = clear_value,
        };
    }
};

struct ECHIDNA_EXPORT required_limits {
    const chained_struct* next;
    limits limits;

    constexpr required_limits(const WGPURequiredLimits& l) : next(l.nextInChain), limits(l.limits) {}
    constexpr operator WGPURequiredLimits() { return {.nextInChain = next, .limits = limits}; }
};

class shader_module_descriptor {
    std::vector<WGPUShaderModuleCompilationHint> wgpu_hints;

    constexpr auto get_wgpu_hints() {
        wgpu_hints = std::vector<WGPUShaderModuleCompilationHint>(hints.begin(), hints.end());
        return wgpu_hints;
    }

public:
    const chained_struct* next;
    std::string label;
    std::vector<shader_module_compilation_hint> hints;

    constexpr shader_module_descriptor(const WGPUShaderModuleDescriptor& d) :
        next(d.nextInChain), label(d.label), hints(d.hints, d.hints + d.hintCount) {}

    constexpr operator WGPUShaderModuleDescriptor() {
        return WGPUShaderModuleDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .hintCount   = hints.size(),
            .hints       = this->get_wgpu_hints().data(),
        };
    }
};

struct ECHIDNA_EXPORT supported_limits {
    chained_struct_out* next;
    limits limits;

    constexpr supported_limits(const WGPUSupportedLimits& l) : next(l.nextInChain), limits(l.limits) {}
    constexpr operator WGPUSupportedLimits() { return {.nextInChain = next, .limits = limits}; }
};

class texture_descriptor {
    std::vector<WGPUTextureFormat> wgpu_formats;

    constexpr auto get_wgpu_formats() {
        std::transform(view_formats.begin(), view_formats.end(), std::back_inserter(wgpu_formats), [](auto f) {
            return static_cast<WGPUTextureFormat>(f);
        });
        return wgpu_formats;
    }

public:
    const chained_struct* next;
    std::string label;
    texture_usage usage;
    texture_dimension dimension;
    extent3d size;
    texture_format format;
    std::uint32_t mip_level_count;
    std::vector<texture_format> view_formats;

    constexpr texture_descriptor(const WGPUTextureDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        usage(static_cast<texture_usage>(d.usage)),
        dimension(static_cast<texture_dimension>(d.dimension)),
        size(d.size),
        format(static_cast<texture_format>(d.format)),
        mip_level_count(d.mipLevelCount) {
        std::transform(d.viewFormats, d.viewFormats + d.viewFormatCount, std::back_inserter(view_formats), [](auto f) {
            return static_cast<texture_format>(f);
        });
    }

    constexpr operator WGPUTextureDescriptor() {
        return WGPUTextureDescriptor{
            .nextInChain     = next,
            .label           = label.c_str(),
            .usage           = static_cast<WGPUTextureUsage>(usage),
            .dimension       = static_cast<WGPUTextureDimension>(dimension),
            .size            = size,
            .format          = static_cast<WGPUTextureFormat>(format),
            .mipLevelCount   = mip_level_count,
            .viewFormatCount = view_formats.size(),
            .viewFormats     = this->wgpu_formats.data(),
        };
    }
};

class vertex_buffer_layout {
    std::vector<WGPUVertexAttribute> wgpu_attributes;

    constexpr auto get_wgpu_attributes() {
        wgpu_attributes = std::vector<WGPUVertexAttribute>(attributes.begin(), attributes.end());
        return wgpu_attributes;
    }

public:
    std::uint64_t array_stride;
    vertex_step_mode step_mode;
    std::vector<vertex_attribute> attributes;

    constexpr vertex_buffer_layout(const WGPUVertexBufferLayout& l) :
        array_stride(l.arrayStride),
        step_mode(static_cast<vertex_step_mode>(l.stepMode)),
        attributes(l.attributes, l.attributes + l.attributeCount) {}

    constexpr operator WGPUVertexBufferLayout() {
        return WGPUVertexBufferLayout{
            .arrayStride    = array_stride,
            .stepMode       = static_cast<WGPUVertexStepMode>(step_mode),
            .attributeCount = attributes.size(),
            .attributes     = this->get_wgpu_attributes().data(),
        };
    }
};

class bind_group_layout_descriptor {
    std::vector<WGPUBindGroupLayoutEntry> wgpu_entries;

    constexpr auto get_wgpu_entries() {
        wgpu_entries = std::vector<WGPUBindGroupLayoutEntry>(entries.begin(), entries.end());
        return wgpu_entries;
    }

public:
    const chained_struct* next;
    std::string label;
    std::vector<bind_group_layout_entry> entries;

    constexpr bind_group_layout_descriptor(const WGPUBindGroupLayoutDescriptor& d) :
        next(d.nextInChain), label(d.label), entries(d.entries, d.entries + d.entryCount) {}

    constexpr operator WGPUBindGroupLayoutDescriptor() {
        return WGPUBindGroupLayoutDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .entryCount  = entries.size(),
            .entries     = this->get_wgpu_entries().data(),
        };
    }
};

// TODO: If blend changes, wgpu_blend will be outdated
class color_target_state {
    WGPUBlendState wgpu_blend;

    constexpr auto get_wgpu_blend() {
        wgpu_blend = blend;
        return &wgpu_blend;
    }

public:
    const chained_struct* next;
    texture_format format;
    blend_state blend;
    color_write_mask write_mask;

    constexpr color_target_state(const WGPUColorTargetState& s) :
        next(s.nextInChain),
        format(static_cast<texture_format>(format)),
        blend(*s.blend),
        write_mask(static_cast<color_write_mask>(s.writeMask)),
        wgpu_blend(*s.blend) {}

    constexpr operator WGPUColorTargetState() {
        return WGPUColorTargetState{
            .nextInChain = next,
            .format      = static_cast<WGPUTextureFormat>(format),
            .blend       = this->get_wgpu_blend(),
            .writeMask   = static_cast<WGPUColorWriteMask>(write_mask),
        };
    }
};

struct ECHIDNA_EXPORT compute_pipeline_descriptor {
    const chained_struct* next;
    std::string label;
    pipeline_layout layout;
    programmable_stage_descriptor compute;

    constexpr compute_pipeline_descriptor(const WGPUComputePipelineDescriptor& d) :
        next(d.nextInChain), label(d.label), layout(d.layout), compute(d.compute) {}

    constexpr operator WGPUComputePipelineDescriptor() {
        return WGPUComputePipelineDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .layout      = layout,
            .compute     = compute,
        };
    }
};

class device_descriptor {
    WGPURequiredLimits wgpu_limits;
    std::vector<WGPUFeatureName> wgpu_features;

    constexpr auto get_wgpu_limits() {
        wgpu_limits = required_limits;
        return &wgpu_limits;
    }

    constexpr auto get_wgpu_features() {
        std::transform(
            required_features.begin(),
            required_features.end(),
            std::back_inserter(wgpu_features),
            [](auto f) { return static_cast<WGPUFeatureName>(f); }
        );

        return wgpu_features;
    }

public:
    const chained_struct* next;
    std::string label;
    std::vector<feature_name> required_features;
    required_limits required_limits;
    queue_descriptor default_queue;
    device_lost_callback device_lost_callback;
    void* device_lost_user_data;

    constexpr device_descriptor(const WGPUDeviceDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        required_limits(*d.requiredLimits),
        default_queue(d.defaultQueue),
        device_lost_callback(d.deviceLostCallback),
        device_lost_user_data(d.deviceLostUserdata) {

        std::transform(
            d.requiredFeatures,
            d.requiredFeatures + d.requiredFeatureCount,
            std::back_inserter(required_features),
            [](auto f) { return static_cast<feature_name>(f); }
        );
    }

    constexpr operator WGPUDeviceDescriptor() {
        return WGPUDeviceDescriptor{
            .nextInChain          = next,
            .label                = label.c_str(),
            .requiredFeatureCount = required_features.size(),
            .requiredFeatures     = this->get_wgpu_features().data(),
            .requiredLimits       = this->get_wgpu_limits(),
            .defaultQueue         = default_queue,
            .deviceLostCallback   = device_lost_callback,
            .deviceLostUserdata   = device_lost_user_data,
        };
    }
};

class render_pass_descriptor {
    WGPURenderPassDepthStencilAttachment wgpu_ds;
    WGPURenderPassTimestampWrites wgpu_tsw;
    std::vector<WGPURenderPassColorAttachment> wgpu_ca;

    constexpr auto get_wgpu_ds() {
        wgpu_ds = depth_stencil_attachment;
        return &wgpu_ds;
    }

    constexpr auto get_wgpu_tsw() {
        wgpu_tsw = timestamp_writes;
        return &wgpu_tsw;
    }

    constexpr auto get_wgpu_ca() {
        wgpu_ca = std::vector<WGPURenderPassColorAttachment>(color_attachments.begin(), color_attachments.end());
        return wgpu_ca;
    }

public:
    const chained_struct* next;
    std::string label;
    std::vector<render_pass_color_attachment> color_attachments;
    render_pass_depth_stencil_attachment depth_stencil_attachment;
    query_set occlusion_query_set;
    render_pass_timestamp_writes timestamp_writes;

    constexpr render_pass_descriptor(const WGPURenderPassDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        color_attachments(d.colorAttachments, d.colorAttachments + d.colorAttachmentCount),

        depth_stencil_attachment(*d.depthStencilAttachment),
        wgpu_ds(*d.depthStencilAttachment),
        occlusion_query_set(d.occlusionQuerySet),
        timestamp_writes(*d.timestampWrites),
        wgpu_tsw(*d.timestampWrites) {
        wgpu_ca = std::vector<WGPURenderPassColorAttachment>(color_attachments.begin(), color_attachments.end());
    }

    constexpr operator WGPURenderPassDescriptor() {
        return WGPURenderPassDescriptor{
            .nextInChain            = next,
            .label                  = label.c_str(),
            .colorAttachmentCount   = color_attachments.size(),
            .colorAttachments       = this->get_wgpu_ca().data(),
            .depthStencilAttachment = this->get_wgpu_ds(),
            .occlusionQuerySet      = occlusion_query_set,
            .timestampWrites        = this->get_wgpu_tsw(),
        };
    }
};

class vertex_state {
    std::vector<WGPUConstantEntry> wgpu_constants;
    std::vector<WGPUVertexBufferLayout> wgpu_buffers;

    constexpr auto get_wgpu_constants() {
        wgpu_constants = std::vector<WGPUConstantEntry>(constants.begin(), constants.end());
        return wgpu_constants;
    }

    constexpr auto get_wgpu_buffers() {
        wgpu_buffers = std::vector<WGPUVertexBufferLayout>(buffers.begin(), buffers.end());
        return wgpu_buffers;
    }

public:
    const chained_struct* next;
    shader_module module;
    std::string entry_point;
    std::vector<constant_entry> constants;
    std::vector<vertex_buffer_layout> buffers;

    constexpr vertex_state(const WGPUVertexState& s) :
        next(s.nextInChain),
        module(s.module),
        entry_point(s.entryPoint),
        constants(s.constants, s.constants + s.constantCount),
        buffers(s.buffers, s.buffers + s.bufferCount) {}

    constexpr operator WGPUVertexState() {
        return WGPUVertexState{
            .nextInChain   = next,
            .module        = module,
            .entryPoint    = entry_point.c_str(),
            .constantCount = constants.size(),
            .constants     = this->get_wgpu_constants().data(),
            .bufferCount   = buffers.size(),
            .buffers       = this->get_wgpu_buffers().data(),
        };
    }
};

class fragment_state {
    std::vector<WGPUConstantEntry> wgpu_constants;
    std::vector<WGPUColorTargetState> wgpu_targets;

    constexpr auto get_wgpu_constants() {
        wgpu_constants = std::vector<WGPUConstantEntry>(constants.begin(), constants.end());
        return wgpu_constants;
    }

    constexpr auto get_wgpu_targets() {
        wgpu_targets = std::vector<WGPUColorTargetState>(targets.begin(), targets.end());
        return wgpu_targets;
    }

public:
    const chained_struct* next;
    shader_module module;
    std::string entry_point;
    std::vector<constant_entry> constants;
    std::vector<color_target_state> targets;

    constexpr fragment_state(const WGPUFragmentState& s) :
        next(s.nextInChain),
        module(s.module),
        entry_point(s.entryPoint),
        constants(s.constants, s.constants + s.constantCount),
        targets(s.targets, s.targets + s.targetCount) {}

    constexpr operator WGPUFragmentState() {
        return WGPUFragmentState{
            .nextInChain   = next,
            .module        = module,
            .entryPoint    = entry_point.c_str(),
            .constantCount = constants.size(),
            .constants     = this->get_wgpu_constants().data(),
            .targetCount   = targets.size(),
            .targets       = this->get_wgpu_targets().data(),
        };
    }
};

class render_pipeline_descriptor {
    WGPUDepthStencilState wgpu_ds;
    WGPUFragmentState wgpu_fs;

    constexpr auto get_wgpu_ds() {
        wgpu_ds = depth_stencil;
        return &wgpu_ds;
    }

    constexpr auto get_wgpu_fs() {
        wgpu_fs = fragment;
        return &wgpu_fs;
    }

public:
    const chained_struct* next;
    std::string label;
    pipeline_layout layout;
    vertex_state vertex;
    primitive_state primitive;
    depth_stencil_state depth_stencil;
    multisample_state multisample;
    fragment_state fragment;

    constexpr render_pipeline_descriptor(const WGPURenderPipelineDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        layout(d.layout),
        vertex(d.vertex),
        primitive(d.primitive),
        depth_stencil(*d.depthStencil),
        wgpu_ds(*d.depthStencil),
        multisample(d.multisample),
        fragment(*d.fragment),
        wgpu_fs(*d.fragment) {}

    constexpr operator WGPURenderPipelineDescriptor() {
        return WGPURenderPipelineDescriptor{
            .nextInChain  = next,
            .label        = label.c_str(),
            .layout       = layout,
            .vertex       = vertex,
            .primitive    = primitive,
            .depthStencil = this->get_wgpu_ds(),
            .multisample  = multisample,
            .fragment     = this->get_wgpu_fs(),
        };
    }
};

} // namespace echidna::webgpu