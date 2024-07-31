#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/bind_group_layout.hpp"
#include "echidna/webgpu/buffer.hpp"
#include "echidna/webgpu/chained_struct.hpp"
#include "echidna/webgpu/device.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/pipeline_layout.hpp"
#include "echidna/webgpu/query_set.hpp"
#include "echidna/webgpu/sampler.hpp"
#include "echidna/webgpu/shader.hpp"
#include "echidna/webgpu/surface.hpp"
#include "echidna/webgpu/texture.hpp"
#include "echidna/webgpu/texture_view.hpp"

#include <bit>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include <webgpu.h>

/* NOTES
    - Structs that hold a collection of other structs currently duplicate the WGPU structs so that
        they can be pointed to on conversion. Need to determine if there is a way to avoid this.
*/

using namespace echidna::webgpu;

namespace echidna {

using device_lost_callback = WGPUDeviceLostCallback;

struct ECHIDNA_EXPORT adapter_properties {
    chained_struct_out* next;
    std::uint32_t vendor_id;
    std::string vendor;
    std::string architecture;
    std::uint32_t device_id;
    std::string device;
    std::string description;
    backend_type backend;
    adapter_type adapter;

    adapter_properties(WGPUAdapterProperties& p) :
        next(p.nextInChain),
        vendor_id(p.vendorID),
        vendor(p.vendorName),
        architecture(p.architecture),
        device_id(p.deviceID),
        device(p.name),
        description(p.driverDescription),
        backend(p.backendType),
        adapter(p.adapterType) {}

    constexpr operator WGPUAdapterProperties() {
        return WGPUAdapterProperties{
            .nextInChain       = std::bit_cast<WGPUChainedStructOut*>(next),
            .vendorID          = vendor_id,
            .vendorName        = vendor.c_str(),
            .architecture      = architecture.c_str(),
            .deviceID          = device_id,
            .name              = device.c_str(),
            .driverDescription = description.c_str(),
            .adapterType       = adapter,
            .backendType       = backend,
        };
    }
};

struct ECHIDNA_EXPORT bind_group_entry {
    const chained_struct* next;
    std::uint32_t binding;
    std::optional<buffer> buffer_binding;
    std::uint64_t offset;
    std::uint64_t size;
    std::optional<sampler> sampler_binding;
    std::optional<texture_view> texture_view_binding;

    bind_group_entry(
        std::uint32_t binding,
        const buffer& buf,
        std::uint64_t offset,
        std::uint64_t size
    ) :
        next(nullptr), binding(binding), buffer_binding(buf), offset(offset), size(size) {}

    bind_group_entry(std::uint32_t binding, const sampler& sampler) :
        next(nullptr), binding(binding), offset(0), size(0), sampler_binding(sampler) {}

    bind_group_entry(std::uint32_t binding, const texture_view& texture_view_binding) :
        next(nullptr),
        binding(binding),
        offset(0),
        size(0),
        texture_view_binding(texture_view_binding) {}

    constexpr bind_group_entry(const WGPUBindGroupEntry& e) :
        next(e.nextInChain),
        binding(e.binding),
        buffer_binding(e.buffer),
        offset(e.offset),
        size(e.size),
        sampler_binding(e.sampler),
        texture_view_binding(e.textureView) {}

    operator WGPUBindGroupEntry() const {
        return WGPUBindGroupEntry{
            .nextInChain = next,
            .binding     = binding,
            .buffer      = buffer_binding ? buffer_binding.value() : nullptr,
            .offset      = offset,
            .size        = size,
            .sampler     = sampler_binding ? sampler_binding.value() : nullptr,
            .textureView = texture_view_binding ? texture_view_binding.value() : nullptr,
        };
    }
};

struct ECHIDNA_EXPORT blend_component {
    blend_op op;
    blend_factor src;
    blend_factor dst;

    constexpr blend_component(blend_op op, blend_factor src, blend_factor dst) :
        op(op), src(src), dst(dst) {}

    constexpr blend_component(const WGPUBlendComponent& bc) :
        op(bc.operation), src(bc.srcFactor), dst(bc.dstFactor) {}

    constexpr operator WGPUBlendComponent() const {
        return WGPUBlendComponent{
            .operation = op,
            .srcFactor = src,
            .dstFactor = dst,
        };
    }
};

struct ECHIDNA_EXPORT buffer_binding_layout {
    const chained_struct* next;
    buffer_binding_type type;
    bool dynamic_offset;
    std::uint64_t min_binding_size;

    constexpr buffer_binding_layout() :
        next(nullptr),
        type(buffer_binding_type::undefined),
        dynamic_offset(false),
        min_binding_size(0) {}

    constexpr buffer_binding_layout(
        buffer_binding_type type,
        bool has_dynamic_offset,
        std::uint64_t min_binding_size
    ) :
        next(nullptr),
        type(type),
        dynamic_offset(has_dynamic_offset),
        min_binding_size(min_binding_size) {}

    constexpr buffer_binding_layout(const WGPUBufferBindingLayout& b) :
        next(b.nextInChain),
        type(b.type),
        dynamic_offset(b.hasDynamicOffset != 0u),
        min_binding_size(b.minBindingSize) {}

    constexpr operator WGPUBufferBindingLayout() const {
        return WGPUBufferBindingLayout{
            .nextInChain      = next,
            .type             = type,
            .hasDynamicOffset = static_cast<WGPUBool>(dynamic_offset),
            .minBindingSize   = min_binding_size,
        };
    }
};

struct ECHIDNA_EXPORT buffer_descriptor {
    const chained_struct* next;
    std::string label;
    buffer_usage usage;
    std::uint64_t size;
    bool mapped_at_creation;

    constexpr buffer_descriptor(
        const char* label,
        buffer_usage usage,
        std::uint64_t size,
        bool mapped_at_creation
    ) :
        next(nullptr),
        label(label),
        usage(usage),
        size(size),
        mapped_at_creation(mapped_at_creation) {}

    constexpr buffer_descriptor(buffer_usage usage, std::uint64_t size) :
        buffer_descriptor(nullptr, usage, size, false) {}

    constexpr buffer_descriptor(const WGPUBufferDescriptor& bd) :
        next(bd.nextInChain),
        label(bd.label),
        usage(bd.usage),
        size(bd.size),
        mapped_at_creation(bd.mappedAtCreation != 0u) {}

    constexpr operator WGPUBufferDescriptor() const {
        return WGPUBufferDescriptor{
            .nextInChain      = next,
            .label            = label.c_str(),
            .usage            = usage,
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

    constexpr color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {}
    constexpr color(const WGPUColor& c) : red(c.r), green(c.g), blue(c.b), alpha(c.a) {}
    constexpr operator WGPUColor() const {
        return WGPUColor{.r = red, .g = green, .b = blue, .a = alpha};
    }
};

struct ECHIDNA_EXPORT command_buffer_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr command_buffer_descriptor(const char* label) : next(nullptr), label(label) {}

    constexpr command_buffer_descriptor(const WGPUCommandBufferDescriptor& cbd) :
        next(cbd.nextInChain), label(cbd.label) {}

    constexpr operator WGPUCommandBufferDescriptor() const {
        return WGPUCommandBufferDescriptor{.nextInChain = next, .label = label.c_str()};
    }
};

struct ECHIDNA_EXPORT command_encoder_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr command_encoder_descriptor(const char* label) : next(nullptr), label(label) {}

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
        type(cm.type),
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
            .message      = message.c_str(),
            .type         = type,
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

    compute_pass_timestamp_writes(const query_set& set, std::uint32_t begin, std::uint32_t end) :
        set(set), beginning_index(begin), end_index(end) {}

    constexpr compute_pass_timestamp_writes(const WGPUComputePassTimestampWrites& ctw) :
        set(ctw.querySet),
        beginning_index(ctw.beginningOfPassWriteIndex),
        end_index(ctw.endOfPassWriteIndex) {}

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

    constexpr constant_entry(const std::string& key, double val) :
        next(nullptr), key(key), value(val) {}

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

    constexpr extent3d(std::uint32_t width, std::uint32_t height, std::uint32_t depth) :
        width(width), height(height), depth(depth) {}

    constexpr extent3d(const WGPUExtent3D& e) :
        width(e.width), height(e.height), depth(e.depthOrArrayLayers) {}

    constexpr operator WGPUExtent3D() const {
        return WGPUExtent3D{.width = width, .height = height, .depthOrArrayLayers = depth};
    }
};

struct ECHIDNA_EXPORT instance_descriptor {
    const chained_struct* next;

    explicit constexpr instance_descriptor(const chained_struct* n = nullptr) : next(n) {}
    constexpr instance_descriptor(const WGPUInstanceDescriptor& i) : next((i.nextInChain)) {}

    constexpr operator WGPUInstanceDescriptor() const {
        return WGPUInstanceDescriptor{.nextInChain = next};
    }
};

// TODO: Figure out constructor for this
struct ECHIDNA_EXPORT limits {
    std::uint32_t max_texture_dimension_1d                        = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_texture_dimension_2d                        = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_texture_dimension_3d                        = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_texture_array_layers                        = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_bind_groups                                 = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_bind_groups_plus_vertex_buffers             = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_bindings_per_group                          = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_dynamic_uniform_buffers_per_pipeline_layout = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_dynamic_storage_buffers_per_pipeline_layout = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_sampled_textures_per_shader_stage           = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_samplers_per_shader_stage                   = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_storage_buffers_per_shader_stage            = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_storage_textures_per_shader_stage           = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_uniform_buffers_per_shader_stage            = WGPU_LIMIT_U32_UNDEFINED;
    std::uint64_t max_uniform_buffer_binding_size                 = WGPU_LIMIT_U64_UNDEFINED;
    std::uint64_t max_storage_buffer_binding_size                 = WGPU_LIMIT_U64_UNDEFINED;
    std::uint32_t min_uniform_buffer_offset_alignment             = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t min_storage_buffer_offset_alignment             = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_vertex_buffers                              = WGPU_LIMIT_U32_UNDEFINED;
    std::uint64_t max_buffer_size                                 = WGPU_LIMIT_U64_UNDEFINED;
    std::uint32_t max_vertex_attributes                           = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_vertex_buffer_array_stride                  = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_inter_stage_shader_components               = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_inter_stage_shader_variables                = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_color_attachments                           = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_color_attachment_bytes_per_sample           = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_compute_workgroup_storage_size              = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_compute_invocations_per_workgroup           = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_compute_workgroup_size_X                    = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_compute_workgroup_size_Y                    = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_compute_workgroup_size_Z                    = WGPU_LIMIT_U32_UNDEFINED;
    std::uint32_t max_compute_workgroups_per_dimension            = WGPU_LIMIT_U32_UNDEFINED;

    constexpr limits() {}

    constexpr limits(const WGPULimits& lim) :
        max_texture_dimension_1d(lim.maxTextureDimension1D),
        max_texture_dimension_2d(lim.maxTextureDimension2D),
        max_texture_dimension_3d(lim.maxTextureDimension3D),
        max_texture_array_layers(lim.maxTextureArrayLayers),
        max_bind_groups(lim.maxBindGroups),
        max_bind_groups_plus_vertex_buffers(lim.maxBindGroupsPlusVertexBuffers),
        max_bindings_per_group(lim.maxBindingsPerBindGroup),
        max_dynamic_uniform_buffers_per_pipeline_layout(
            lim.maxDynamicUniformBuffersPerPipelineLayout
        ),
        max_dynamic_storage_buffers_per_pipeline_layout(
            lim.maxDynamicStorageBuffersPerPipelineLayout
        ),
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
            .maxTextureDimension1D          = max_texture_dimension_1d,
            .maxTextureDimension2D          = max_texture_dimension_2d,
            .maxTextureDimension3D          = max_texture_dimension_3d,
            .maxTextureArrayLayers          = max_texture_array_layers,
            .maxBindGroups                  = max_bind_groups,
            .maxBindGroupsPlusVertexBuffers = max_bind_groups_plus_vertex_buffers,
            .maxBindingsPerBindGroup        = max_bindings_per_group,
            .maxDynamicUniformBuffersPerPipelineLayout =
                max_dynamic_uniform_buffers_per_pipeline_layout,
            .maxDynamicStorageBuffersPerPipelineLayout =
                max_dynamic_storage_buffers_per_pipeline_layout,
            .maxSampledTexturesPerShaderStage  = max_sampled_textures_per_shader_stage,
            .maxSamplersPerShaderStage         = max_samplers_per_shader_stage,
            .maxStorageBuffersPerShaderStage   = max_storage_buffers_per_shader_stage,
            .maxStorageTexturesPerShaderStage  = max_storage_textures_per_shader_stage,
            .maxUniformBuffersPerShaderStage   = max_uniform_buffers_per_shader_stage,
            .maxUniformBufferBindingSize       = max_uniform_buffer_binding_size,
            .maxStorageBufferBindingSize       = max_storage_buffer_binding_size,
            .minUniformBufferOffsetAlignment   = min_uniform_buffer_offset_alignment,
            .minStorageBufferOffsetAlignment   = min_storage_buffer_offset_alignment,
            .maxVertexBuffers                  = max_vertex_buffers,
            .maxBufferSize                     = max_buffer_size,
            .maxVertexAttributes               = max_vertex_attributes,
            .maxVertexBufferArrayStride        = max_vertex_buffer_array_stride,
            .maxInterStageShaderComponents     = max_inter_stage_shader_components,
            .maxInterStageShaderVariables      = max_inter_stage_shader_variables,
            .maxColorAttachments               = max_color_attachments,
            .maxColorAttachmentBytesPerSample  = max_color_attachment_bytes_per_sample,
            .maxComputeWorkgroupStorageSize    = max_compute_workgroup_storage_size,
            .maxComputeInvocationsPerWorkgroup = max_compute_invocations_per_workgroup,
            .maxComputeWorkgroupSizeX          = max_compute_workgroup_size_X,
            .maxComputeWorkgroupSizeY          = max_compute_workgroup_size_Y,
            .maxComputeWorkgroupSizeZ          = max_compute_workgroup_size_Z,
            .maxComputeWorkgroupsPerDimension  = max_compute_workgroups_per_dimension,
        };
    }
};

struct ECHIDNA_EXPORT multisample_state {
    const chained_struct* next;
    std::uint32_t count;
    std::uint32_t mask;
    bool alpha_to_coverage_enabled;

    constexpr multisample_state(std::uint32_t count, std::uint32_t mask, bool alpha) :
        next(nullptr), count(count), mask(mask), alpha_to_coverage_enabled(alpha) {}

    constexpr multisample_state(const WGPUMultisampleState& s) :
        next(s.nextInChain),
        count(s.count),
        mask(s.mask),
        alpha_to_coverage_enabled(s.alphaToCoverageEnabled != 0u) {}

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

    constexpr origin3d(std::uint32_t x, std::uint32_t y, std::uint32_t z) : x(x), y(y), z(z) {}
    constexpr origin3d(const WGPUOrigin3D& o) : x(o.x), y(o.y), z(o.z) {}
    constexpr operator WGPUOrigin3D() const { return WGPUOrigin3D{.x = x, .y = y, .z = z}; }
};

class pipeline_layout_descriptor {
    std::vector<WGPUBindGroupLayout> wgpu_layouts;

public:
    const chained_struct* next;
    std::string label;
    std::vector<bind_group_layout> layouts;

    constexpr pipeline_layout_descriptor(
        const std::string& label,
        const std::vector<bind_group_layout>& layouts
    ) :
        wgpu_layouts(layouts.begin(), layouts.end()),
        next(nullptr),
        label(label),
        layouts(layouts) {}

    constexpr pipeline_layout_descriptor(const WGPUPipelineLayoutDescriptor& pld) :
        next(pld.nextInChain),
        label(pld.label),
        layouts(pld.bindGroupLayouts, pld.bindGroupLayouts + pld.bindGroupLayoutCount) {}

    constexpr operator WGPUPipelineLayoutDescriptor() {
        wgpu_layouts = std::vector<WGPUBindGroupLayout>(layouts.begin(), layouts.end());

        return WGPUPipelineLayoutDescriptor{
            .nextInChain          = next,
            .label                = label.c_str(),
            .bindGroupLayoutCount = layouts.size(),
            .bindGroupLayouts     = wgpu_layouts.data(),
        };
    }
};

struct ECHIDNA_EXPORT primitive_depth_clip_control {
    chained_struct chain;
    bool unclipped_depth;

    constexpr primitive_depth_clip_control(chained_struct chain, bool unclipped) :
        chain(chain), unclipped_depth(unclipped) {}

    constexpr primitive_depth_clip_control(WGPUPrimitiveDepthClipControl& pdc) :
        chain(pdc.chain), unclipped_depth(pdc.unclippedDepth != 0u) {}

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
    front_face front_face_winding;
    cull_mode cull_mode_direction;

    constexpr primitive_state(
        primitive_topology topology,
        index_format format,
        front_face front,
        cull_mode cull_direction
    ) :
        next(nullptr),
        topology(topology),
        strip_index_format(format),
        front_face_winding(front),
        cull_mode_direction(cull_direction) {}

    constexpr primitive_state(const WGPUPrimitiveState& p) :
        next((p.nextInChain)),
        topology(p.topology),
        strip_index_format(p.stripIndexFormat),
        front_face_winding(p.frontFace),
        cull_mode_direction(p.cullMode) {}

    constexpr operator WGPUPrimitiveState() const {
        return WGPUPrimitiveState{
            .nextInChain      = next,
            .topology         = topology,
            .stripIndexFormat = strip_index_format,
            .frontFace        = front_face_winding,
            .cullMode         = cull_mode_direction,
        };
    }
};

struct ECHIDNA_EXPORT query_set_descriptor {
    const chained_struct* next;
    std::string label;
    query_type type;
    std::uint32_t count;

    constexpr query_set_descriptor(const std::string& label, query_type type, std::uint32_t count) :
        next(nullptr), label(label), type(type), count(count) {}

    constexpr query_set_descriptor(const WGPUQuerySetDescriptor& q) :
        next(q.nextInChain), label(q.label), type(q.type), count(q.count) {}

    constexpr operator WGPUQuerySetDescriptor() const {
        return WGPUQuerySetDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .type        = type,
            .count       = count,
        };
    }
};

struct ECHIDNA_EXPORT queue_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr queue_descriptor() : next(nullptr) {}
    constexpr queue_descriptor(const std::string& label) : next(nullptr), label(label) {}
    constexpr queue_descriptor(const WGPUQueueDescriptor& q) :
        next(q.nextInChain), label(q.label) {}
    constexpr operator WGPUQueueDescriptor() {
        return {.nextInChain = next, .label = label.c_str()};
    }
};

struct ECHIDNA_EXPORT render_bundle_descriptor {
    const chained_struct* next;
    std::string label;

    constexpr render_bundle_descriptor(const std::string& label) : next(nullptr), label(label) {}
    constexpr render_bundle_descriptor(const WGPURenderBundleDescriptor& q) :
        next(q.nextInChain), label(q.label) {}
    constexpr operator WGPURenderBundleDescriptor() const {
        return {.nextInChain = next, .label = label.c_str()};
    }
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

    render_pass_depth_stencil_attachment(
        const texture_view& view,
        load_op depth_load,
        store_op depth_store,
        float depth_clear_val,
        bool depth_read_only,
        load_op stencil_load,
        store_op stencil_store,
        std::uint32_t stencil_clear_val,
        bool stencil_read_only
    ) :
        view(view),
        depth_load_op(depth_load),
        depth_store_op(depth_store),
        depth_clear_value(depth_clear_val),
        depth_read_only(depth_read_only),
        stencil_load_op(stencil_load),
        stencil_store_op(stencil_store),
        stencil_clear_value(stencil_clear_val),
        stencil_read_only(stencil_read_only) {}

    constexpr render_pass_depth_stencil_attachment(const WGPURenderPassDepthStencilAttachment& a) :
        view(a.view),
        depth_load_op(a.depthLoadOp),
        depth_store_op(a.depthStoreOp),
        depth_clear_value(a.depthClearValue),
        depth_read_only(a.depthReadOnly != 0u),
        stencil_load_op(a.stencilLoadOp),
        stencil_store_op(a.stencilStoreOp),
        stencil_clear_value(a.stencilClearValue),
        stencil_read_only(a.stencilReadOnly != 0u) {}

    constexpr operator WGPURenderPassDepthStencilAttachment() const {
        return WGPURenderPassDepthStencilAttachment{
            .view              = view,
            .depthLoadOp       = depth_load_op,
            .depthStoreOp      = depth_store_op,
            .depthClearValue   = depth_clear_value,
            .depthReadOnly     = static_cast<WGPUBool>(depth_read_only),
            .stencilLoadOp     = stencil_load_op,
            .stencilStoreOp    = stencil_store_op,
            .stencilClearValue = stencil_clear_value,
            .stencilReadOnly   = static_cast<WGPUBool>(stencil_read_only),
        };
    }
};

struct ECHIDNA_EXPORT render_pass_descriptor_max_draw_count {
    chained_struct chain;
    std::uint64_t max_draw_count;

    constexpr render_pass_descriptor_max_draw_count(chained_struct chain, std::uint64_t count) :
        chain(chain), max_draw_count(count) {}

    constexpr render_pass_descriptor_max_draw_count(std::uint64_t count) :
        chain(), max_draw_count(count) {}

    constexpr render_pass_descriptor_max_draw_count(const WGPURenderPassDescriptorMaxDrawCount& mdc
    ) :
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

    render_pass_timestamp_writes() : set(nullptr), beginning_index(), end_index() {}

    render_pass_timestamp_writes(const query_set& set, std::uint32_t begin, std::uint32_t end) :
        set(set), beginning_index(begin), end_index(end) {}

    constexpr render_pass_timestamp_writes(const WGPURenderPassTimestampWrites& w) :
        set(w.querySet),
        beginning_index(w.beginningOfPassWriteIndex),
        end_index(w.endOfPassWriteIndex) {}

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
    power_preference power_pref;
    backend_type backend;
    bool force_fallback;

    request_adapter_options(
        const chained_struct* n,
        const surface& surf,
        power_preference pref,
        backend_type backend,
        bool fallback
    ) :
        next(n),
        compatible_surface(surf),
        power_pref(pref),
        backend(backend),
        force_fallback(fallback) {}

    request_adapter_options(
        surface& surf,
        power_preference pref,
        backend_type backend,
        bool fallback
    ) :
        request_adapter_options(nullptr, surf, pref, backend, fallback) {}

    request_adapter_options(surface& surf) :
        request_adapter_options(
            surf,
            power_preference::high_performance,
            backend_type::undefined,
            false
        ) {}

    constexpr request_adapter_options(const WGPURequestAdapterOptions& o) :
        next(o.nextInChain),
        compatible_surface(o.compatibleSurface),
        power_pref(o.powerPreference),
        backend(o.backendType),
        force_fallback(o.forceFallbackAdapter != 0u) {}

    constexpr operator WGPURequestAdapterOptions() const {
        return WGPURequestAdapterOptions{
            .nextInChain          = next,
            .compatibleSurface    = compatible_surface,
            .powerPreference      = power_pref,
            .backendType          = backend,
            .forceFallbackAdapter = static_cast<WGPUBool>(force_fallback),
        };
    }
};

struct ECHIDNA_EXPORT sampler_binding_layout {
    const chained_struct* next;
    sampler_binding_type type;

    constexpr sampler_binding_layout() : next(nullptr), type(sampler_binding_type::undefined) {}

    constexpr sampler_binding_layout(sampler_binding_type type) : next(nullptr), type(type) {}

    constexpr sampler_binding_layout(const WGPUSamplerBindingLayout& l) :
        next(l.nextInChain), type(l.type) {}

    constexpr operator WGPUSamplerBindingLayout() const {
        return WGPUSamplerBindingLayout{
            .nextInChain = next,
            .type        = type,
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

    constexpr sampler_descriptor(
        const std::string& label,
        address_mode u,
        address_mode v,
        address_mode w,
        filter_mode mag,
        filter_mode min,
        mipmap_filter_mode mipmap,
        float lod_min,
        float lod_max,
        compare_function comp,
        std::uint16_t anisotropy
    ) :
        next(nullptr),
        label(label),
        address_mode_u(u),
        address_mode_v(v),
        address_mode_w(w),
        mag_filter(mag),
        min_filter(min),
        mip_map_filter(mipmap),
        lod_min_clamp(lod_min),
        lod_max_clamp(lod_max),
        compare(comp),
        max_anisotropy(anisotropy) {}

    constexpr sampler_descriptor(const WGPUSamplerDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        address_mode_u(d.addressModeU),
        address_mode_v(d.addressModeV),
        address_mode_w(d.addressModeW),
        mag_filter(d.magFilter),
        min_filter(d.minFilter),
        mip_map_filter(d.mipmapFilter),
        lod_min_clamp(d.lodMinClamp),
        lod_max_clamp(d.lodMaxClamp),
        compare(d.compare),
        max_anisotropy(d.maxAnisotropy) {}

    constexpr operator WGPUSamplerDescriptor() const {
        return WGPUSamplerDescriptor{
            .nextInChain   = next,
            .label         = label.c_str(),
            .addressModeU  = address_mode_u,
            .addressModeV  = address_mode_v,
            .addressModeW  = address_mode_w,
            .magFilter     = mag_filter,
            .minFilter     = min_filter,
            .mipmapFilter  = mip_map_filter,
            .lodMinClamp   = lod_min_clamp,
            .lodMaxClamp   = lod_max_clamp,
            .compare       = compare,
            .maxAnisotropy = max_anisotropy,
        };
    }
};

struct ECHIDNA_EXPORT shader_module_compilation_hint {
    const chained_struct* next;
    std::string entry_point;
    pipeline_layout layout;

    shader_module_compilation_hint(const std::string& entry, const pipeline_layout& layout) :
        next(nullptr), entry_point(entry), layout(layout) {}

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

    constexpr shader_module_spirv_descriptor(std::uint32_t size, const std::uint32_t* code) :
        chain(make_chained(stype::shader_module_spirv)), size(size), code(code) {}

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

    constexpr shader_module_wgsl_descriptor(const std::string& code) :
        chain(make_chained(stype::shader_module_wgsl)), code(code) {}

    constexpr shader_module_wgsl_descriptor(const WGPUShaderModuleWGSLDescriptor& d) :
        chain(d.chain), code(d.code) {}

    constexpr operator WGPUShaderModuleWGSLDescriptor() const {
        return {.chain = chain, .code = code.c_str()};
    }
};

struct ECHIDNA_EXPORT stencil_face_state {
    compare_function compare;
    stencil_op fail;
    stencil_op depth_fail;
    stencil_op pass;

    constexpr stencil_face_state(
        compare_function comp,
        stencil_op fail,
        stencil_op depth_fail,
        stencil_op pass
    ) :
        compare(comp), fail(fail), depth_fail(depth_fail), pass(pass) {}

    constexpr stencil_face_state(const WGPUStencilFaceState& s) :
        compare(s.compare), fail(s.failOp), depth_fail(s.depthFailOp), pass(s.passOp) {}

    constexpr operator WGPUStencilFaceState() const {
        return WGPUStencilFaceState{
            .compare     = compare,
            .failOp      = fail,
            .depthFailOp = depth_fail,
            .passOp      = pass,
        };
    }
};

struct ECHIDNA_EXPORT storage_texture_binding_layout {
    const chained_struct* next;
    storage_texture_access access;
    texture_format format;
    texture_view_dimension view_dimension;

    constexpr storage_texture_binding_layout() :
        next(nullptr),
        access(storage_texture_access::undefined),
        format(texture_format::undefined),
        view_dimension(texture_view_dimension::undefined) {}

    constexpr storage_texture_binding_layout(
        storage_texture_access access,
        texture_format format,
        texture_view_dimension dim
    ) :
        next(nullptr), access(access), format(format), view_dimension(dim) {}

    constexpr storage_texture_binding_layout(const WGPUStorageTextureBindingLayout& l) :
        next(l.nextInChain), access(l.access), format(l.format), view_dimension(l.viewDimension) {}

    constexpr operator WGPUStorageTextureBindingLayout() const {
        return WGPUStorageTextureBindingLayout{
            .nextInChain   = next,
            .access        = access,
            .format        = format,
            .viewDimension = view_dimension,
        };
    }
};

class surface_capabilities {
    std::vector<WGPUTextureFormat> wgpu_fmts;
    std::vector<WGPUPresentMode> wgpu_pm;
    std::vector<WGPUCompositeAlphaMode> wgpu_cam;

public:
    std::vector<texture_format> formats;
    std::vector<present_mode> present_modes;
    std::vector<composite_alpha_mode> alpha_modes;

    surface_capabilities(
        const std::vector<texture_format>& formats,
        const std::vector<present_mode>& present_modes,
        std::vector<composite_alpha_mode>& alpha_modes
    ) :
        wgpu_fmts(formats.begin(), formats.end()),
        wgpu_pm(present_modes.begin(), present_modes.end()),
        wgpu_cam(alpha_modes.begin(), alpha_modes.end()),
        formats(formats),
        present_modes(present_modes),
        alpha_modes(alpha_modes) {}

    constexpr surface_capabilities(const WGPUSurfaceCapabilities& c) :
        formats(c.formats, c.formats + c.formatCount),
        present_modes(c.presentModes, c.presentModes + c.presentModeCount),
        alpha_modes(c.alphaModes, c.alphaModes + c.alphaModeCount) {}

    constexpr operator WGPUSurfaceCapabilities() {
        wgpu_fmts = std::vector<WGPUTextureFormat>(formats.begin(), formats.end());
        wgpu_pm   = std::vector<WGPUPresentMode>(present_modes.begin(), present_modes.end());
        wgpu_cam  = std::vector<WGPUCompositeAlphaMode>(alpha_modes.begin(), alpha_modes.end());
        return WGPUSurfaceCapabilities{
            .nextInChain      = nullptr,
            .formatCount      = formats.size(),
            .formats          = wgpu_fmts.data(),
            .presentModeCount = present_modes.size(),
            .presentModes     = wgpu_pm.data(),
            .alphaModeCount   = alpha_modes.size(),
            .alphaModes       = wgpu_cam.data(),
        };
    }
};

class surface_configuration {
    std::vector<WGPUTextureFormat> wgpu_formats;

public:
    const chained_struct* next;
    device device_handle;
    texture_format format;
    texture_usage usage;
    std::vector<texture_format> view_formats;
    composite_alpha_mode alpha_mode;
    std::uint32_t width;
    std::uint32_t height;
    present_mode present;

    surface_configuration(
        const device& device,
        texture_format format,
        texture_usage usage,
        const std::vector<texture_format>& view_formats,
        composite_alpha_mode alpha,
        std::uint32_t width,
        std::uint32_t height,
        present_mode present
    ) :
        next(nullptr),
        device_handle(device),
        format(format),
        usage(usage),
        view_formats(view_formats),
        alpha_mode(alpha),
        width(width),
        height(height),
        present(present) {}

    surface_configuration(
        const device& dev,
        texture_format format,
        std::uint32_t width,
        std::uint32_t height
    ) :
        next(nullptr),
        device_handle(dev),
        format(format),
        usage(texture_usage::render_attachment),
        alpha_mode(composite_alpha_mode::automatic),
        width(width),
        height(height),
        present(present_mode::fifo) {}

    constexpr surface_configuration(const WGPUSurfaceConfiguration& c) :
        next(c.nextInChain),
        device_handle(c.device),
        format(c.format),
        usage(c.usage),
        view_formats(c.viewFormats, c.viewFormats + c.viewFormatCount),
        alpha_mode(c.alphaMode),
        width(c.width),
        height(c.height),
        present(c.presentMode) {}

    constexpr operator WGPUSurfaceConfiguration() {
        wgpu_formats = std::vector<WGPUTextureFormat>(view_formats.begin(), view_formats.end());
        return WGPUSurfaceConfiguration{
            .nextInChain     = next,
            .device          = device_handle,
            .format          = format,
            .usage           = usage,
            .viewFormatCount = view_formats.size(),
            .viewFormats     = wgpu_formats.data(),
            .alphaMode       = alpha_mode,
            .width           = width,
            .height          = height,
            .presentMode     = present,
        };
    }
};

struct ECHIDNA_EXPORT texture_binding_layout {
    const chained_struct* next;
    texture_sample_type sample_type;
    texture_view_dimension view_dimension;
    bool multisampled;

    constexpr texture_binding_layout() :
        next(nullptr),
        sample_type(texture_sample_type::undefined),
        view_dimension(texture_view_dimension::undefined),
        multisampled(false) {}

    constexpr texture_binding_layout(
        texture_sample_type sample_type,
        texture_view_dimension dim,
        bool multisampled
    ) :
        next(nullptr), sample_type(sample_type), view_dimension(dim), multisampled(multisampled) {}

    constexpr texture_binding_layout(const WGPUTextureBindingLayout& l) :
        next(l.nextInChain),
        sample_type(l.sampleType),
        view_dimension(l.viewDimension),
        multisampled(l.multisampled != 0u) {}

    constexpr operator WGPUTextureBindingLayout() const {
        return WGPUTextureBindingLayout{
            .nextInChain   = next,
            .sampleType    = sample_type,
            .viewDimension = view_dimension,
            .multisampled  = static_cast<WGPUBool>(multisampled),
        };
    }
};

struct ECHIDNA_EXPORT texture_data_layout {
    const chained_struct* next;
    std::uint64_t offset;
    std::uint32_t bytes_per_row;
    std::uint32_t rows_per_image;

    constexpr texture_data_layout(
        std::uint64_t offset,
        std::uint32_t bytes_per_row,
        std::uint32_t rows
    ) :
        next(nullptr), offset(offset), bytes_per_row(bytes_per_row), rows_per_image(rows) {}

    constexpr texture_data_layout(const WGPUTextureDataLayout& l) :
        next(l.nextInChain),
        offset(l.offset),
        bytes_per_row(l.bytesPerRow),
        rows_per_image(l.rowsPerImage) {}
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

    constexpr texture_view_descriptor(
        const std::string& label,
        texture_format format,
        texture_view_dimension dim,
        std::uint32_t base_mip,
        std::uint32_t mip_count,
        std::uint32_t base_array,
        std::uint32_t array_count,
        texture_aspect aspect
    ) :
        next(nullptr),
        label(label),
        format(format),
        dimension(dim),
        base_mip_level(base_mip),
        mip_level_count(mip_count),
        base_array_layer(base_array),
        array_layer_count(array_count),
        aspect(aspect) {}

    constexpr texture_view_descriptor(const WGPUTextureViewDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        format(d.format),
        dimension(d.dimension),
        base_mip_level(d.baseMipLevel),
        mip_level_count(d.mipLevelCount),
        base_array_layer(d.baseArrayLayer),
        array_layer_count(d.arrayLayerCount),
        aspect(d.aspect) {}

    constexpr operator WGPUTextureViewDescriptor() {
        return WGPUTextureViewDescriptor{
            .nextInChain     = next,
            .label           = label.c_str(),
            .format          = format,
            .dimension       = dimension,
            .baseMipLevel    = base_mip_level,
            .mipLevelCount   = mip_level_count,
            .baseArrayLayer  = base_array_layer,
            .arrayLayerCount = array_layer_count,
            .aspect          = aspect,
        };
    }
};

struct ECHIDNA_EXPORT vertex_attribute {
    vertex_format format;
    std::uint64_t offset;
    std::uint32_t shader_location;

    constexpr vertex_attribute(
        vertex_format format,
        std::uint64_t offset,
        std::uint32_t shader_loc
    ) :
        format(format), offset(offset), shader_location(shader_loc) {}

    constexpr vertex_attribute(const WGPUVertexAttribute& a) :
        format(a.format), offset(a.offset), shader_location(a.shaderLocation) {}

    constexpr operator WGPUVertexAttribute() {
        return WGPUVertexAttribute{
            .format         = format,
            .offset         = offset,
            .shaderLocation = shader_location,
        };
    }
};

class bind_group_descriptor {
    std::vector<WGPUBindGroupEntry> wgpu_entries;

public:
    const chained_struct* next;
    std::string label;
    bind_group_layout layout;
    std::vector<bind_group_entry> entries;

    bind_group_descriptor(
        const char* label,
        bind_group_layout& bgl,
        const std::vector<bind_group_entry>& entries
    ) :
        next(nullptr), label(label), layout(bgl), entries(entries) {}

    bind_group_descriptor(
        const bind_group_layout& layout,
        const std::vector<bind_group_entry>& entries
    ) :
        next(nullptr), layout(layout), entries(entries) {}

    constexpr bind_group_descriptor(const WGPUBindGroupDescriptor& d) :
        wgpu_entries(d.entries, d.entries + d.entryCount),
        next(d.nextInChain),
        label(d.label),
        entries(d.entries, d.entries + d.entryCount) {}

    constexpr operator WGPUBindGroupDescriptor() {
        wgpu_entries = std::vector<WGPUBindGroupEntry>(entries.begin(), entries.end());

        return WGPUBindGroupDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .layout      = layout,
            .entryCount  = entries.size(),
            .entries     = wgpu_entries.data(),
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

    bind_group_layout_entry(std::uint32_t binding, shader_stage vis, buffer_binding_layout layout) :
        next(nullptr), binding(binding), visibility(vis), buffer(layout) {}

    bind_group_layout_entry(
        std::uint32_t binding,
        shader_stage vis,
        sampler_binding_layout layout
    ) :
        next(nullptr), binding(binding), visibility(vis), sampler(layout) {}

    bind_group_layout_entry(
        std::uint32_t binding,
        shader_stage vis,
        texture_binding_layout layout
    ) :
        next(nullptr), binding(binding), visibility(vis), texture(layout) {}

    bind_group_layout_entry(
        std::uint32_t binding,
        shader_stage vis,
        storage_texture_binding_layout layout
    ) :
        next(nullptr), binding(binding), visibility(vis), storage_texture(layout) {}

    constexpr bind_group_layout_entry(const WGPUBindGroupLayoutEntry& e) :
        next(e.nextInChain),
        binding(e.binding),
        visibility(e.visibility),
        buffer(e.buffer),
        sampler(e.sampler),
        texture(e.texture),
        storage_texture(e.storageTexture) {}

    constexpr operator WGPUBindGroupLayoutEntry() {
        return WGPUBindGroupLayoutEntry{
            .nextInChain    = next,
            .binding        = binding,
            .visibility     = visibility,
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

    constexpr blend_state(blend_component color, blend_component alpha) :
        color(color), alpha(alpha) {}
    constexpr blend_state(const WGPUBlendState& s) : color(s.color), alpha(s.alpha) {}
    constexpr operator WGPUBlendState() { return {.color = color, .alpha = alpha}; }
};

class compilation_info {
    std::vector<WGPUCompilationMessage> wgpu_messages;

public:
    const chained_struct* next;
    std::vector<compilation_message> messages;

    compilation_info(const std::vector<compilation_message>& msg) :
        wgpu_messages(msg.begin(), msg.end()), next(nullptr), messages(msg) {}

    constexpr compilation_info(const WGPUCompilationInfo& i) :
        next(i.nextInChain), messages(i.messages, i.messages + i.messageCount) {}

    constexpr operator WGPUCompilationInfo() {
        wgpu_messages = std::vector<WGPUCompilationMessage>(messages.begin(), messages.end());
        return WGPUCompilationInfo{
            .nextInChain  = next,
            .messageCount = messages.size(),
            .messages     = wgpu_messages.data(),
        };
    }
};

class compute_pass_descriptor {
    std::optional<WGPUComputePassTimestampWrites> wgpu_tsw;

public:
    const chained_struct* next;
    std::string label;
    compute_pass_timestamp_writes timestamp_writes;

    compute_pass_descriptor(const std::string& label, const compute_pass_timestamp_writes& tsw) :
        wgpu_tsw(tsw), next(nullptr), label(label), timestamp_writes(tsw) {}

    constexpr compute_pass_descriptor(const WGPUComputePassDescriptor& d) :
        wgpu_tsw(*d.timestampWrites),
        next(d.nextInChain),
        label(d.label),
        timestamp_writes(*d.timestampWrites) {}

    operator WGPUComputePassDescriptor() {
        wgpu_tsw = timestamp_writes;
        return WGPUComputePassDescriptor{
            .nextInChain     = next,
            .label           = label.c_str(),
            .timestampWrites = wgpu_tsw ? std::to_address(wgpu_tsw) : nullptr,
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

    constexpr depth_stencil_state(
        texture_format format,
        bool depth_write_enabled,
        compare_function depth_compare,
        const stencil_face_state& front,
        const stencil_face_state& back,
        std::uint32_t stencil_read_mask,
        std::uint32_t stencil_write_mask,
        std::int32_t depth_bias,
        float slope_scale,
        float clamp
    ) :
        next(nullptr),
        format(format),
        depth_write_enabled(depth_write_enabled),
        depth_compare(depth_compare),
        stencil_front(front),
        stencil_back(back),
        stencil_read_mask(stencil_read_mask),
        stencil_write_mask(stencil_write_mask),
        depth_bias(depth_bias),
        depth_bias_slope_scale(slope_scale),
        depth_bias_clamp(clamp) {}

    constexpr depth_stencil_state(const WGPUDepthStencilState& s) :
        next(s.nextInChain),
        format(s.format),
        depth_write_enabled(s.depthWriteEnabled != 0u),
        depth_compare(s.depthCompare),
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
            .format              = format,
            .depthWriteEnabled   = static_cast<WGPUBool>(depth_write_enabled),
            .depthCompare        = depth_compare,
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
    buffer buffer_dst;

    image_copy_buffer(texture_data_layout layout, const buffer& dest) :
        next(nullptr), layout(layout), buffer_dst(dest) {}

    constexpr image_copy_buffer(const WGPUImageCopyBuffer& b) :
        next(b.nextInChain), layout(b.layout), buffer_dst(b.buffer) {}

    constexpr operator WGPUImageCopyBuffer() {
        return WGPUImageCopyBuffer{
            .nextInChain = next,
            .layout      = layout,
            .buffer      = buffer_dst,
        };
    }
};

struct ECHIDNA_EXPORT image_copy_texture {
    const chained_struct* next;
    texture texture_dst;
    std::uint32_t mip_level;
    origin3d origin;
    texture_aspect aspect;

    constexpr image_copy_texture(const WGPUImageCopyTexture& b) :
        next(b.nextInChain),
        texture_dst(b.texture),
        mip_level(b.mipLevel),
        origin(b.origin),
        aspect(b.aspect) {}

    constexpr operator WGPUImageCopyTexture() {
        return WGPUImageCopyTexture{
            .nextInChain = next,
            .texture     = texture_dst,
            .mipLevel    = mip_level,
            .origin      = origin,
            .aspect      = aspect,
        };
    }
};

class programmable_stage_descriptor {
    std::vector<WGPUConstantEntry> wgpu_constants;

public:
    const chained_struct* next;
    shader_module module;
    std::string entry_point;
    std::vector<constant_entry> constants;

    programmable_stage_descriptor(const shader_module& module, const std::string& entry) :
        next(nullptr), module(module), entry_point(entry) {}

    constexpr programmable_stage_descriptor(const WGPUProgrammableStageDescriptor& d) :
        next(d.nextInChain),
        module(d.module),
        entry_point(d.entryPoint),
        constants(d.constants, d.constants + d.constantCount) {}

    constexpr operator WGPUProgrammableStageDescriptor() {
        wgpu_constants = std::vector<WGPUConstantEntry>(constants.begin(), constants.end());

        return WGPUProgrammableStageDescriptor{
            .nextInChain   = next,
            .module        = module,
            .entryPoint    = entry_point.c_str(),
            .constantCount = constants.size(),
            .constants     = wgpu_constants.data(),
        };
    }
};

struct ECHIDNA_EXPORT render_pass_color_attachment {
    const chained_struct* next;
    texture_view view;
    texture_view resolve_target;
    load_op load_operation;
    store_op store_operation;
    color clear_value;

    render_pass_color_attachment(load_op load, store_op store, color clear) :
        next(nullptr),
        view(nullptr),
        resolve_target(nullptr),
        load_operation(load),
        store_operation(store),
        clear_value(clear) {}

    render_pass_color_attachment(
        const texture_view& view,
        const texture_view& resolve,
        load_op load,
        store_op store,
        color clear
    ) :
        next(nullptr),
        view(view),
        resolve_target(resolve),
        load_operation(load),
        store_operation(store),
        clear_value(clear) {}

    constexpr render_pass_color_attachment(const WGPURenderPassColorAttachment& a) :
        next(a.nextInChain),
        view(a.view),
        resolve_target(a.resolveTarget),
        load_operation(a.loadOp),
        store_operation(a.storeOp),
        clear_value(a.clearValue) {}

    constexpr operator WGPURenderPassColorAttachment() {
        return WGPURenderPassColorAttachment{
            .nextInChain   = next,
            .view          = view,
            .resolveTarget = resolve_target,
            .loadOp        = load_operation,
            .storeOp       = store_operation,
            .clearValue    = clear_value,
        };
    }
};

struct ECHIDNA_EXPORT required_limits {
    const chained_struct* next;
    limits required_lims;

    constexpr required_limits() : next(nullptr) {}
    constexpr required_limits(limits limits) : next(nullptr), required_lims(limits) {}
    constexpr required_limits(const WGPURequiredLimits& l) :
        next(l.nextInChain), required_lims(l.limits) {}
    constexpr operator WGPURequiredLimits() {
        return {.nextInChain = next, .limits = required_lims};
    }
};

class shader_module_descriptor {
    std::vector<WGPUShaderModuleCompilationHint> wgpu_hints;

public:
    const chained_struct* next;
    std::string label;
    std::vector<shader_module_compilation_hint> hints;

    shader_module_descriptor(const shader_module_wgsl_descriptor& chain) : next(&chain.chain) {}

    constexpr shader_module_descriptor(
        const std::string& label,
        const std::vector<shader_module_compilation_hint>& hints
    ) :
        next(nullptr), label(label), hints(hints) {}

    constexpr shader_module_descriptor(const WGPUShaderModuleDescriptor& d) :
        next(d.nextInChain), label(d.label), hints(d.hints, d.hints + d.hintCount) {}

    constexpr operator WGPUShaderModuleDescriptor() {
        wgpu_hints = std::vector<WGPUShaderModuleCompilationHint>(hints.begin(), hints.end());
        return WGPUShaderModuleDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .hintCount   = hints.size(),
            .hints       = wgpu_hints.data(),
        };
    }
};

struct ECHIDNA_EXPORT supported_limits {
    chained_struct_out* next;
    limits supported_lims;

    constexpr supported_limits(limits limits) : next(nullptr), supported_lims(limits) {}
    constexpr supported_limits(const WGPUSupportedLimits& l) :
        next(l.nextInChain), supported_lims(l.limits) {}
    constexpr operator WGPUSupportedLimits() {
        return {.nextInChain = next, .limits = supported_lims};
    }
};

class texture_descriptor {
    std::vector<WGPUTextureFormat> wgpu_formats;

public:
    const chained_struct* next;
    std::string label;
    texture_usage usage;
    texture_dimension dimension;
    extent3d size;
    texture_format format;
    std::uint32_t mip_level_count;
    std::uint32_t sample_count;
    std::vector<texture_format> view_formats;

    texture_descriptor(
        const std::string& label,
        texture_usage usage,
        texture_dimension dim,
        extent3d size,
        texture_format format,
        std::uint32_t mip_level_count,
        std::uint32_t sample_count,
        const std::vector<texture_format>& view_formats
    ) :
        next(nullptr),
        label(label),
        usage(usage),
        dimension(dim),
        size(size),
        format(format),
        mip_level_count(mip_level_count),
        sample_count(sample_count),
        view_formats(view_formats) {}

    constexpr texture_descriptor(const WGPUTextureDescriptor& d) :
        next(d.nextInChain),
        label(d.label),
        usage(d.usage),
        dimension(d.dimension),
        size(d.size),
        format(d.format),
        mip_level_count(d.mipLevelCount),
        sample_count(d.sampleCount),
        view_formats(d.viewFormats, d.viewFormats + d.viewFormatCount) {}

    constexpr operator WGPUTextureDescriptor() {
        wgpu_formats = std::vector<WGPUTextureFormat>(view_formats.begin(), view_formats.end());

        return WGPUTextureDescriptor{
            .nextInChain     = next,
            .label           = label.c_str(),
            .usage           = usage,
            .dimension       = dimension,
            .size            = size,
            .format          = format,
            .mipLevelCount   = mip_level_count,
            .sampleCount     = sample_count,
            .viewFormatCount = view_formats.size(),
            .viewFormats     = wgpu_formats.data(),
        };
    }
};

class vertex_buffer_layout {
    std::vector<WGPUVertexAttribute> wgpu_attributes;

public:
    std::uint64_t array_stride;
    vertex_step_mode step_mode;
    std::vector<vertex_attribute> attributes;

    vertex_buffer_layout(
        std::uint64_t stride,
        vertex_step_mode step_mode,
        const std::vector<vertex_attribute>& attributes
    ) :
        array_stride(stride), step_mode(step_mode), attributes(attributes) {}

    constexpr vertex_buffer_layout(const WGPUVertexBufferLayout& l) :
        array_stride(l.arrayStride),
        step_mode(l.stepMode),
        attributes(l.attributes, l.attributes + l.attributeCount) {}

    constexpr operator WGPUVertexBufferLayout() {
        wgpu_attributes = std::vector<WGPUVertexAttribute>(attributes.begin(), attributes.end());

        return WGPUVertexBufferLayout{
            .arrayStride    = array_stride,
            .stepMode       = step_mode,
            .attributeCount = attributes.size(),
            .attributes     = wgpu_attributes.data(),
        };
    }
};

class bind_group_layout_descriptor {
    std::vector<WGPUBindGroupLayoutEntry> wgpu_entries;

public:
    const chained_struct* next;
    std::string label;
    std::vector<bind_group_layout_entry> entries;

    bind_group_layout_descriptor(
        const std::string& label,
        const std::vector<bind_group_layout_entry>& entries
    ) :
        next(nullptr), label(label), entries(entries) {}

    constexpr bind_group_layout_descriptor(const WGPUBindGroupLayoutDescriptor& d) :
        next(d.nextInChain), label(d.label), entries(d.entries, d.entries + d.entryCount) {}

    bind_group_layout_descriptor(const char* label, std::vector<bind_group_layout_entry>& entries) :
        next(nullptr), label(label), entries(entries) {}

    constexpr operator WGPUBindGroupLayoutDescriptor() {
        wgpu_entries = std::vector<WGPUBindGroupLayoutEntry>(entries.begin(), entries.end());

        return WGPUBindGroupLayoutDescriptor{
            .nextInChain = next,
            .label       = label.c_str(),
            .entryCount  = entries.size(),
            .entries     = wgpu_entries.data(),
        };
    }
};

class color_target_state {
    std::optional<WGPUBlendState> wgpu_blend;

public:
    const chained_struct* next;
    texture_format format;
    blend_state blend;
    color_write_mask write_mask;

    constexpr color_target_state(
        texture_format format,
        const blend_state& blend,
        const color_write_mask& mask
    ) :
        next(nullptr), format(format), blend(blend), write_mask(mask) {}

    constexpr color_target_state(const WGPUColorTargetState& s) :
        wgpu_blend(*s.blend),
        next(s.nextInChain),
        format(s.format),
        blend(*s.blend),
        write_mask(s.writeMask) {}

    constexpr operator WGPUColorTargetState() {
        wgpu_blend = blend;
        return WGPUColorTargetState{
            .nextInChain = next,
            .format      = format,
            .blend       = wgpu_blend ? std::to_address(wgpu_blend) : nullptr,
            .writeMask   = write_mask,
        };
    }
};

struct ECHIDNA_EXPORT compute_pipeline_descriptor {
    const chained_struct* next;
    std::string label;
    pipeline_layout layout;
    programmable_stage_descriptor compute;

    compute_pipeline_descriptor(
        const std::string& label,
        const pipeline_layout& layout,
        const programmable_stage_descriptor& compute
    ) :
        next(nullptr), label(label), layout(layout), compute(compute) {}

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
    std::optional<WGPURequiredLimits> wgpu_limits;
    std::vector<WGPUFeatureName> wgpu_features;

    static constexpr auto device_lost = [](WGPUDeviceLostReason reason, const char* msg, void*) {
        std::cerr << "Device lost: " << reason;
        if(msg != nullptr) {
            std::cerr << "(message: " << msg << ")";
        }
    };

public:
    const chained_struct* next;
    std::string label;
    std::vector<feature_name> required_features;
    required_limits required_lims;
    queue_descriptor default_queue;
    device_lost_callback dev_lost_callback;
    void* device_lost_user_data;

    device_descriptor(
        const std::string& label,
        const std::vector<feature_name>& features,
        const required_limits& limits,
        const queue_descriptor& default_queue,
        const device_lost_callback& device_lost_callback,
        void* device_lost_user_data
    ) :
        next(nullptr),
        label(label),
        required_features(features),
        required_lims(limits),
        default_queue(default_queue),
        dev_lost_callback(device_lost_callback),
        device_lost_user_data(device_lost_user_data) {}

    device_descriptor() :
        next(nullptr),
        dev_lost_callback(device_descriptor::device_lost),
        device_lost_user_data(nullptr) {}

    constexpr device_descriptor(const WGPUDeviceDescriptor& d) :
        wgpu_limits(*d.requiredLimits),
        next(d.nextInChain),
        label(d.label),
        required_features(d.requiredFeatures, d.requiredFeatures + d.requiredFeatureCount),
        required_lims(*d.requiredLimits),
        default_queue(d.defaultQueue),
        dev_lost_callback(d.deviceLostCallback),
        device_lost_user_data(d.deviceLostUserdata) {}

    constexpr operator WGPUDeviceDescriptor() {
        wgpu_limits = required_lims;
        wgpu_features =
            std::vector<WGPUFeatureName>(required_features.begin(), required_features.end());

        return WGPUDeviceDescriptor{
            .nextInChain          = next,
            .label                = label.c_str(),
            .requiredFeatureCount = required_features.size(),
            .requiredFeatures     = wgpu_features.data(),
            .requiredLimits       = wgpu_limits ? std::to_address(wgpu_limits) : nullptr,
            .defaultQueue         = default_queue,
            .deviceLostCallback   = dev_lost_callback,
            .deviceLostUserdata   = device_lost_user_data,
        };
    }
};

class render_pass_descriptor {
    std::optional<WGPURenderPassDepthStencilAttachment> wgpu_ds;
    std::optional<WGPURenderPassTimestampWrites> wgpu_tsw;
    std::vector<WGPURenderPassColorAttachment> wgpu_ca;

public:
    const chained_struct* next;
    std::string label;
    std::vector<render_pass_color_attachment> color_attachments;
    render_pass_depth_stencil_attachment depth_stencil_attachment;
    std::optional<query_set> occlusion_query_set;
    std::optional<render_pass_timestamp_writes> timestamp_writes;

    render_pass_descriptor(
        const std::vector<render_pass_color_attachment>& color_attachments,
        const render_pass_depth_stencil_attachment& depth_stencil_attachment
    ) :
        next(nullptr),
        color_attachments(color_attachments),
        depth_stencil_attachment(depth_stencil_attachment) {}

    render_pass_descriptor(
        const std::string& label,
        const std::vector<render_pass_color_attachment>& color_attachments,
        const render_pass_depth_stencil_attachment& depth_stencil_attachment
    ) :
        next(nullptr),
        label(label),
        color_attachments(color_attachments),
        depth_stencil_attachment(depth_stencil_attachment) {}

    render_pass_descriptor(
        const std::string& label,
        const std::vector<render_pass_color_attachment>& color_attachments,
        const render_pass_depth_stencil_attachment& depth_stencil_attachment,
        const query_set& occlusion_query,
        const render_pass_timestamp_writes& tsw
    ) :
        next(nullptr),
        label(label),
        color_attachments(color_attachments),
        depth_stencil_attachment(depth_stencil_attachment),
        occlusion_query_set(occlusion_query),
        timestamp_writes(tsw) {}

    constexpr render_pass_descriptor(const WGPURenderPassDescriptor& d) :
        wgpu_ds(*d.depthStencilAttachment),
        wgpu_tsw(*d.timestampWrites),
        next(d.nextInChain),
        label(d.label),
        color_attachments(d.colorAttachments, d.colorAttachments + d.colorAttachmentCount),
        depth_stencil_attachment(*d.depthStencilAttachment),
        occlusion_query_set(d.occlusionQuerySet),
        timestamp_writes(*d.timestampWrites) {
        wgpu_ca = std::vector<WGPURenderPassColorAttachment>(
            color_attachments.begin(),
            color_attachments.end()
        );
    }

    operator WGPURenderPassDescriptor() {
        wgpu_ds  = depth_stencil_attachment;
        wgpu_tsw = timestamp_writes;
        wgpu_ca  = std::vector<WGPURenderPassColorAttachment>(
            color_attachments.begin(),
            color_attachments.end()
        );

        return WGPURenderPassDescriptor{
            .nextInChain            = next,
            .label                  = label.c_str(),
            .colorAttachmentCount   = color_attachments.size(),
            .colorAttachments       = wgpu_ca.data(),
            .depthStencilAttachment = wgpu_ds ? std::to_address(wgpu_ds) : nullptr,
            .occlusionQuerySet      = occlusion_query_set ? occlusion_query_set.value() : nullptr,
            .timestampWrites        = wgpu_tsw ? std::to_address(wgpu_tsw) : nullptr,
        };
    }
};

class vertex_state {
    std::vector<WGPUConstantEntry> wgpu_constants;
    std::vector<WGPUVertexBufferLayout> wgpu_buffers;

public:
    const chained_struct* next;
    shader_module module;
    std::string entry_point;
    std::vector<constant_entry> constants;
    std::vector<vertex_buffer_layout> buffers;

    vertex_state(
        const shader_module& module,
        const std::string& entry,
        const std::vector<constant_entry>& constants,
        const std::vector<vertex_buffer_layout>& buffers
    ) :
        next(nullptr), module(module), entry_point(entry), constants(constants), buffers(buffers) {}

    constexpr vertex_state(const WGPUVertexState& s) :
        next(s.nextInChain),
        module(s.module),
        entry_point(s.entryPoint),
        constants(s.constants, s.constants + s.constantCount),
        buffers(s.buffers, s.buffers + s.bufferCount) {}

    constexpr operator WGPUVertexState() {
        wgpu_constants = std::vector<WGPUConstantEntry>(constants.begin(), constants.end());
        wgpu_buffers   = std::vector<WGPUVertexBufferLayout>(buffers.begin(), buffers.end());

        return WGPUVertexState{
            .nextInChain   = next,
            .module        = module,
            .entryPoint    = entry_point.c_str(),
            .constantCount = constants.size(),
            .constants     = wgpu_constants.data(),
            .bufferCount   = buffers.size(),
            .buffers       = wgpu_buffers.data(),
        };
    }
};

class fragment_state {
    std::vector<WGPUConstantEntry> wgpu_constants;
    std::vector<WGPUColorTargetState> wgpu_targets;

public:
    const chained_struct* next;
    shader_module module;
    std::string entry_point;
    std::vector<constant_entry> constants;
    std::vector<color_target_state> targets;

    fragment_state(
        const shader_module& module,
        const std::string& entry,
        const std::vector<constant_entry>& constants,
        const std::vector<color_target_state>& targets
    ) :
        next(nullptr), module(module), entry_point(entry), constants(constants), targets(targets) {}

    constexpr fragment_state(const WGPUFragmentState& s) :
        next(s.nextInChain),
        module(s.module),
        entry_point(s.entryPoint),
        constants(s.constants, s.constants + s.constantCount),
        targets(s.targets, s.targets + s.targetCount) {}

    constexpr operator WGPUFragmentState() {
        wgpu_constants = std::vector<WGPUConstantEntry>(constants.begin(), constants.end());
        wgpu_targets   = std::vector<WGPUColorTargetState>(targets.begin(), targets.end());

        return WGPUFragmentState{
            .nextInChain   = next,
            .module        = module,
            .entryPoint    = entry_point.c_str(),
            .constantCount = constants.size(),
            .constants     = wgpu_constants.data(),
            .targetCount   = targets.size(),
            .targets       = wgpu_targets.data(),
        };
    }
};

class render_pipeline_descriptor {
    std::optional<WGPUDepthStencilState> wgpu_ds;
    std::optional<WGPUFragmentState> wgpu_fs;

public:
    const chained_struct* next;
    std::string label;
    pipeline_layout layout;
    vertex_state vertex;
    primitive_state primitive;
    depth_stencil_state depth_stencil;
    multisample_state multisample;
    fragment_state fragment;

    render_pipeline_descriptor(
        const std::string& label,
        const pipeline_layout& layout,
        const vertex_state& vertex,
        const primitive_state& primitive,
        const depth_stencil_state& depth_stencil,
        const multisample_state& multisample,
        const fragment_state& fragment
    ) :
        next(nullptr),
        label(label),
        layout(layout),
        vertex(vertex),
        primitive(primitive),
        depth_stencil(depth_stencil),
        multisample(multisample),
        fragment(fragment) {}

    constexpr render_pipeline_descriptor(const WGPURenderPipelineDescriptor& d) :
        wgpu_ds(*d.depthStencil),
        wgpu_fs(*d.fragment),
        next(d.nextInChain),
        label(d.label),
        layout(d.layout),
        vertex(d.vertex),
        primitive(d.primitive),
        depth_stencil(*d.depthStencil),
        multisample(d.multisample),
        fragment(*d.fragment) {}

    constexpr operator WGPURenderPipelineDescriptor() {
        wgpu_ds = depth_stencil;
        wgpu_fs = fragment;

        return WGPURenderPipelineDescriptor{
            .nextInChain  = next,
            .label        = label.c_str(),
            .layout       = layout,
            .vertex       = vertex,
            .primitive    = primitive,
            .depthStencil = wgpu_ds ? std::to_address(wgpu_ds) : nullptr,
            .multisample  = multisample,
            .fragment     = wgpu_fs ? std::to_address(wgpu_fs) : nullptr,
        };
    }
};

} // namespace echidna