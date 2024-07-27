#pragma once

#include "echidna/export.hpp"

#include <type_traits>
#include <webgpu.h>

// TODO: Implement equality operators between echidna enums and wgpu-native enums
// TODO: Add static asserts for underlying types

template<typename T, typename U>
constexpr bool same_underlying =
    std::is_same_v<std::underlying_type_t<T>, std::underlying_type_t<U>>;

namespace echidna::webgpu {

template<typename E, typename W>
class wgpuenum {
    W raw;

public:
    constexpr wgpuenum(W w) : raw(w) {}
    constexpr auto operator=(const W& w) -> E& { // NOLINT
        raw = w;
        return static_cast<E&>(*this);
    }

    constexpr operator W() const { return raw; }

    constexpr auto operator==(const W& other) const -> bool { return other == raw; }
    constexpr auto operator==(const E& other) const -> bool { return other.raw == raw; }
    constexpr auto operator|(const W& other) const -> W { return raw | other; }
    constexpr auto operator&(const W& other) const -> W { return raw & other; }
};

struct ECHIDNA_EXPORT adapter_type : public wgpuenum<adapter_type, WGPUAdapterType> {
    static constexpr WGPUAdapterType discrete   = WGPUAdapterType_DiscreteGPU;
    static constexpr WGPUAdapterType integrated = WGPUAdapterType_IntegratedGPU;
    static constexpr WGPUAdapterType cpu        = WGPUAdapterType_CPU;
    static constexpr WGPUAdapterType unknown    = WGPUAdapterType_Unknown;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr adapter_type() : wgpuenum(adapter_type::unknown) {}
};

struct ECHIDNA_EXPORT address_mode : public wgpuenum<address_mode, WGPUAddressMode> {
    static constexpr WGPUAddressMode repeat        = WGPUAddressMode_Repeat;
    static constexpr WGPUAddressMode mirror_repeat = WGPUAddressMode_MirrorRepeat;
    static constexpr WGPUAddressMode clamp_to_edge = WGPUAddressMode_ClampToEdge;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr address_mode() : wgpuenum(address_mode::repeat) {}
};

struct ECHIDNA_EXPORT backend_type : public wgpuenum<backend_type, WGPUBackendType> {
    static constexpr WGPUBackendType undefined = WGPUBackendType_Undefined;
    static constexpr WGPUBackendType null      = WGPUBackendType_Null;
    static constexpr WGPUBackendType webgpu    = WGPUBackendType_WebGPU;
    static constexpr WGPUBackendType d3d11     = WGPUBackendType_D3D11;
    static constexpr WGPUBackendType d3d12     = WGPUBackendType_D3D12;
    static constexpr WGPUBackendType metal     = WGPUBackendType_Metal;
    static constexpr WGPUBackendType vulkan    = WGPUBackendType_Vulkan;
    static constexpr WGPUBackendType opengl    = WGPUBackendType_OpenGL;
    static constexpr WGPUBackendType opengles  = WGPUBackendType_OpenGLES;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr backend_type() : wgpuenum(backend_type::undefined) {}
};

struct ECHIDNA_EXPORT blend_factor : public wgpuenum<blend_factor, WGPUBlendFactor> {
    static constexpr WGPUBlendFactor zero                = WGPUBlendFactor_Zero;
    static constexpr WGPUBlendFactor one                 = WGPUBlendFactor_One;
    static constexpr WGPUBlendFactor src                 = WGPUBlendFactor_Src;
    static constexpr WGPUBlendFactor one_minus_src       = WGPUBlendFactor_OneMinusSrc;
    static constexpr WGPUBlendFactor src_alpha           = WGPUBlendFactor_SrcAlpha;
    static constexpr WGPUBlendFactor one_minus_src_alpha = WGPUBlendFactor_OneMinusSrcAlpha;
    static constexpr WGPUBlendFactor dst                 = WGPUBlendFactor_Dst;
    static constexpr WGPUBlendFactor one_minus_dst       = WGPUBlendFactor_OneMinusDst;
    static constexpr WGPUBlendFactor dst_alpha           = WGPUBlendFactor_DstAlpha;
    static constexpr WGPUBlendFactor one_minus_dst_alpha = WGPUBlendFactor_OneMinusDstAlpha;
    static constexpr WGPUBlendFactor src_alpha_saturated = WGPUBlendFactor_SrcAlphaSaturated;
    static constexpr WGPUBlendFactor constant            = WGPUBlendFactor_Constant;
    static constexpr WGPUBlendFactor one_minus_constant  = WGPUBlendFactor_OneMinusConstant;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT blend_op : public wgpuenum<blend_op, WGPUBlendOperation> {
    static constexpr WGPUBlendOperation add              = WGPUBlendOperation_Add;
    static constexpr WGPUBlendOperation subtract         = WGPUBlendOperation_Subtract;
    static constexpr WGPUBlendOperation reverse_subtract = WGPUBlendOperation_ReverseSubtract;
    static constexpr WGPUBlendOperation min              = WGPUBlendOperation_Min;
    static constexpr WGPUBlendOperation max              = WGPUBlendOperation_Max;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT buffer_binding_type
    : public wgpuenum<buffer_binding_type, WGPUBufferBindingType> {
    static constexpr WGPUBufferBindingType undefined = WGPUBufferBindingType_Undefined;
    static constexpr WGPUBufferBindingType uniform   = WGPUBufferBindingType_Uniform;
    static constexpr WGPUBufferBindingType storage   = WGPUBufferBindingType_Storage;
    static constexpr WGPUBufferBindingType read_only_storage =
        WGPUBufferBindingType_ReadOnlyStorage;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr buffer_binding_type() : wgpuenum(buffer_binding_type::undefined) {}
};

struct ECHIDNA_EXPORT buffer_map_async_status
    : public wgpuenum<buffer_map_async_status, WGPUBufferMapAsyncStatus> {
    static constexpr WGPUBufferMapAsyncStatus success = WGPUBufferMapAsyncStatus_Success;
    static constexpr WGPUBufferMapAsyncStatus validation_error =
        WGPUBufferMapAsyncStatus_ValidationError;
    static constexpr WGPUBufferMapAsyncStatus unknown     = WGPUBufferMapAsyncStatus_Unknown;
    static constexpr WGPUBufferMapAsyncStatus device_lost = WGPUBufferMapAsyncStatus_DeviceLost;
    static constexpr WGPUBufferMapAsyncStatus destroyed_before_callback =
        WGPUBufferMapAsyncStatus_DestroyedBeforeCallback;
    static constexpr WGPUBufferMapAsyncStatus unmapped_before_callback =
        WGPUBufferMapAsyncStatus_UnmappedBeforeCallback;
    static constexpr WGPUBufferMapAsyncStatus mapping_already_pending =
        WGPUBufferMapAsyncStatus_MappingAlreadyPending;
    static constexpr WGPUBufferMapAsyncStatus offset_out_of_range =
        WGPUBufferMapAsyncStatus_OffsetOutOfRange;
    static constexpr WGPUBufferMapAsyncStatus size_out_of_range =
        WGPUBufferMapAsyncStatus_SizeOutOfRange;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr buffer_map_async_status() : wgpuenum(buffer_map_async_status::unknown) {}
};

struct ECHIDNA_EXPORT buffer_map_state : public wgpuenum<buffer_map_state, WGPUBufferMapState> {
    static constexpr WGPUBufferMapState unmapped = WGPUBufferMapState_Unmapped;
    static constexpr WGPUBufferMapState pending  = WGPUBufferMapState_Pending;
    static constexpr WGPUBufferMapState mapped   = WGPUBufferMapState_Mapped;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT compare_function : public wgpuenum<compare_function, WGPUCompareFunction> {
    static constexpr WGPUCompareFunction undefined     = WGPUCompareFunction_Undefined;
    static constexpr WGPUCompareFunction never         = WGPUCompareFunction_Never;
    static constexpr WGPUCompareFunction less          = WGPUCompareFunction_Less;
    static constexpr WGPUCompareFunction less_equal    = WGPUCompareFunction_LessEqual;
    static constexpr WGPUCompareFunction greater       = WGPUCompareFunction_Greater;
    static constexpr WGPUCompareFunction greater_equal = WGPUCompareFunction_GreaterEqual;
    static constexpr WGPUCompareFunction equal         = WGPUCompareFunction_Equal;
    static constexpr WGPUCompareFunction not_equal     = WGPUCompareFunction_NotEqual;
    static constexpr WGPUCompareFunction always        = WGPUCompareFunction_Always;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr compare_function() : wgpuenum(compare_function::undefined) {}
};

struct ECHIDNA_EXPORT compilation_info_request_status
    : public wgpuenum<compilation_info_request_status, WGPUCompilationInfoRequestStatus> {
    static constexpr WGPUCompilationInfoRequestStatus success =
        WGPUCompilationInfoRequestStatus_Success;
    static constexpr WGPUCompilationInfoRequestStatus error =
        WGPUCompilationInfoRequestStatus_Error;
    static constexpr WGPUCompilationInfoRequestStatus device_lost =
        WGPUCompilationInfoRequestStatus_DeviceLost;
    static constexpr WGPUCompilationInfoRequestStatus unknown =
        WGPUCompilationInfoRequestStatus_Unknown;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr compilation_info_request_status() :
        wgpuenum(compilation_info_request_status::unknown) {}
};

struct ECHIDNA_EXPORT compilation_message_type
    : public wgpuenum<compilation_message_type, WGPUCompilationMessageType> {
    static constexpr WGPUCompilationMessageType error   = WGPUCompilationMessageType_Error;
    static constexpr WGPUCompilationMessageType warning = WGPUCompilationMessageType_Warning;
    static constexpr WGPUCompilationMessageType info    = WGPUCompilationMessageType_Info;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT composite_alpha_mode
    : public wgpuenum<composite_alpha_mode, WGPUCompositeAlphaMode> {
    static constexpr WGPUCompositeAlphaMode automatic     = WGPUCompositeAlphaMode_Auto;
    static constexpr WGPUCompositeAlphaMode opaque        = WGPUCompositeAlphaMode_Opaque;
    static constexpr WGPUCompositeAlphaMode premultiplied = WGPUCompositeAlphaMode_Premultiplied;
    static constexpr WGPUCompositeAlphaMode unpremultiplied =
        WGPUCompositeAlphaMode_Unpremultiplied;
    static constexpr WGPUCompositeAlphaMode inherit = WGPUCompositeAlphaMode_Inherit;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr composite_alpha_mode() : wgpuenum(composite_alpha_mode::automatic) {}
};

struct ECHIDNA_EXPORT create_pipeline_async_status
    : public wgpuenum<create_pipeline_async_status, WGPUCreatePipelineAsyncStatus> {
    static constexpr WGPUCreatePipelineAsyncStatus success = WGPUCreatePipelineAsyncStatus_Success;
    static constexpr WGPUCreatePipelineAsyncStatus validation_error =
        WGPUCreatePipelineAsyncStatus_ValidationError;
    static constexpr WGPUCreatePipelineAsyncStatus internal_error =
        WGPUCreatePipelineAsyncStatus_InternalError;
    static constexpr WGPUCreatePipelineAsyncStatus device_lost =
        WGPUCreatePipelineAsyncStatus_DeviceLost;
    static constexpr WGPUCreatePipelineAsyncStatus device_destroyed =
        WGPUCreatePipelineAsyncStatus_DeviceDestroyed;
    static constexpr WGPUCreatePipelineAsyncStatus unknown = WGPUCreatePipelineAsyncStatus_Unknown;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr create_pipeline_async_status() : wgpuenum(create_pipeline_async_status::unknown) {}
};

struct ECHIDNA_EXPORT cull_mode : public wgpuenum<cull_mode, WGPUCullMode> {
    static constexpr WGPUCullMode none  = WGPUCullMode_None;
    static constexpr WGPUCullMode front = WGPUCullMode_Front;
    static constexpr WGPUCullMode back  = WGPUCullMode_Back;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT device_lost_reason
    : public wgpuenum<device_lost_reason, WGPUDeviceLostReason> {
    static constexpr WGPUDeviceLostReason undefined = WGPUDeviceLostReason_Undefined;
    static constexpr WGPUDeviceLostReason destroyed = WGPUDeviceLostReason_Destroyed;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT error_filter : public wgpuenum<error_filter, WGPUErrorFilter> {
    static constexpr WGPUErrorFilter validation    = WGPUErrorFilter_Validation;
    static constexpr WGPUErrorFilter out_of_memory = WGPUErrorFilter_OutOfMemory;
    static constexpr WGPUErrorFilter internal      = WGPUErrorFilter_Internal;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT error_type : public wgpuenum<error_type, WGPUErrorType> {
    static constexpr WGPUErrorType no_error      = WGPUErrorType_NoError;
    static constexpr WGPUErrorType validation    = WGPUErrorType_Validation;
    static constexpr WGPUErrorType out_of_memory = WGPUErrorType_OutOfMemory;
    static constexpr WGPUErrorType internal      = WGPUErrorType_Internal;
    static constexpr WGPUErrorType unknown       = WGPUErrorType_Unknown;
    static constexpr WGPUErrorType device_lost   = WGPUErrorType_DeviceLost;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT feature_name : public wgpuenum<feature_name, WGPUFeatureName> {
    static constexpr WGPUFeatureName undefined              = WGPUFeatureName_Undefined;
    static constexpr WGPUFeatureName depth_clip_control     = WGPUFeatureName_DepthClipControl;
    static constexpr WGPUFeatureName depth32_float_stencil8 = WGPUFeatureName_Depth32FloatStencil8;
    static constexpr WGPUFeatureName timestamp_query        = WGPUFeatureName_TimestampQuery;
    static constexpr WGPUFeatureName texture_compression_bc = WGPUFeatureName_TextureCompressionBC;
    static constexpr WGPUFeatureName texture_compression_etc2 =
        WGPUFeatureName_TextureCompressionETC2;
    static constexpr WGPUFeatureName texture_compression_astc =
        WGPUFeatureName_TextureCompressionASTC;
    static constexpr WGPUFeatureName indirect_first_instance =
        WGPUFeatureName_IndirectFirstInstance;
    static constexpr WGPUFeatureName shader_f16 = WGPUFeatureName_ShaderF16;
    static constexpr WGPUFeatureName rg11_b10_ufloat_renderable =
        WGPUFeatureName_RG11B10UfloatRenderable;
    static constexpr WGPUFeatureName bgra8_unorm_storage = WGPUFeatureName_BGRA8UnormStorage;
    static constexpr WGPUFeatureName float32_filterable  = WGPUFeatureName_Float32Filterable;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT filter_mode : public wgpuenum<filter_mode, WGPUFilterMode> {
    static constexpr WGPUFilterMode nearest = WGPUFilterMode_Nearest;
    static constexpr WGPUFilterMode linear  = WGPUFilterMode_Linear;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT front_face : public wgpuenum<front_face, WGPUFrontFace> {
    static constexpr WGPUFrontFace ccw = WGPUFrontFace_CCW;
    static constexpr WGPUFrontFace cw  = WGPUFrontFace_CW;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT index_format : public wgpuenum<index_format, WGPUIndexFormat> {
    static constexpr WGPUIndexFormat undefined = WGPUIndexFormat_Undefined;
    static constexpr WGPUIndexFormat uint16    = WGPUIndexFormat_Uint16;
    static constexpr WGPUIndexFormat uint32    = WGPUIndexFormat_Uint32;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr index_format() : wgpuenum(index_format::undefined) {}
};

struct ECHIDNA_EXPORT load_op : public wgpuenum<load_op, WGPULoadOp> {
    static constexpr WGPULoadOp undefined = WGPULoadOp_Undefined;
    static constexpr WGPULoadOp clear     = WGPULoadOp_Clear;
    static constexpr WGPULoadOp load      = WGPULoadOp_Load;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr load_op() : wgpuenum(load_op::undefined) {}
};

struct ECHIDNA_EXPORT mipmap_filter_mode
    : public wgpuenum<mipmap_filter_mode, WGPUMipmapFilterMode> {
    static constexpr WGPUMipmapFilterMode nearest = WGPUMipmapFilterMode_Nearest;
    static constexpr WGPUMipmapFilterMode linear  = WGPUMipmapFilterMode_Linear;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT power_preference : public wgpuenum<power_preference, WGPUPowerPreference> {
    static constexpr WGPUPowerPreference undefined        = WGPUPowerPreference_Undefined;
    static constexpr WGPUPowerPreference low_power        = WGPUPowerPreference_LowPower;
    static constexpr WGPUPowerPreference high_performance = WGPUPowerPreference_HighPerformance;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT present_mode : public wgpuenum<present_mode, WGPUPresentMode> {
    static constexpr WGPUPresentMode fifo         = WGPUPresentMode_Fifo;
    static constexpr WGPUPresentMode fifo_relaxed = WGPUPresentMode_FifoRelaxed;
    static constexpr WGPUPresentMode immediate    = WGPUPresentMode_Immediate;
    static constexpr WGPUPresentMode mailbox      = WGPUPresentMode_Mailbox;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT primitive_topology
    : public wgpuenum<primitive_topology, WGPUPrimitiveTopology> {
    static constexpr WGPUPrimitiveTopology point_list     = WGPUPrimitiveTopology_PointList;
    static constexpr WGPUPrimitiveTopology line_list      = WGPUPrimitiveTopology_LineList;
    static constexpr WGPUPrimitiveTopology line_string    = WGPUPrimitiveTopology_LineStrip;
    static constexpr WGPUPrimitiveTopology triangle_list  = WGPUPrimitiveTopology_TriangleList;
    static constexpr WGPUPrimitiveTopology triangle_strip = WGPUPrimitiveTopology_TriangleStrip;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT query_type : public wgpuenum<query_type, WGPUQueryType> {
    static constexpr WGPUQueryType occlusion = WGPUQueryType_Occlusion;
    static constexpr WGPUQueryType timestamp = WGPUQueryType_Timestamp;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT queue_work_done_status
    : public wgpuenum<queue_work_done_status, WGPUQueueWorkDoneStatus> {
    static constexpr WGPUQueueWorkDoneStatus success     = WGPUQueueWorkDoneStatus_Success;
    static constexpr WGPUQueueWorkDoneStatus error       = WGPUQueueWorkDoneStatus_Error;
    static constexpr WGPUQueueWorkDoneStatus unknown     = WGPUQueueWorkDoneStatus_Unknown;
    static constexpr WGPUQueueWorkDoneStatus device_lost = WGPUQueueWorkDoneStatus_DeviceLost;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr queue_work_done_status() : wgpuenum(queue_work_done_status::unknown) {}
};

struct ECHIDNA_EXPORT request_adapter_status
    : public wgpuenum<request_adapter_status, WGPURequestAdapterStatus> {
    static constexpr WGPURequestAdapterStatus success     = WGPURequestAdapterStatus_Success;
    static constexpr WGPURequestAdapterStatus unavailable = WGPURequestAdapterStatus_Unavailable;
    static constexpr WGPURequestAdapterStatus error       = WGPURequestAdapterStatus_Error;
    static constexpr WGPURequestAdapterStatus unknown     = WGPURequestAdapterStatus_Unknown;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr request_adapter_status() : wgpuenum(request_adapter_status::unknown) {}
};

struct ECHIDNA_EXPORT request_device_status
    : public wgpuenum<request_device_status, WGPURequestDeviceStatus> {
    static constexpr WGPURequestDeviceStatus success = WGPURequestDeviceStatus_Success;
    static constexpr WGPURequestDeviceStatus error   = WGPURequestDeviceStatus_Error;
    static constexpr WGPURequestDeviceStatus unknown = WGPURequestDeviceStatus_Unknown;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr request_device_status() : wgpuenum(request_device_status::unknown) {}
};

struct ECHIDNA_EXPORT stype : public wgpuenum<stype, WGPUSType> {
    static constexpr WGPUSType invalid = WGPUSType_Invalid;
    static constexpr WGPUSType surface_descriptor_from_metal_layer =
        WGPUSType_SurfaceDescriptorFromMetalLayer;
    static constexpr WGPUSType surface_descriptor_from_windows_hwnd =
        WGPUSType_SurfaceDescriptorFromWindowsHWND;
    static constexpr WGPUSType surface_descriptor_from_xlib_window =
        WGPUSType_SurfaceDescriptorFromXlibWindow;
    static constexpr WGPUSType surface_descriptor_from_canvas_html_selector =
        WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
    static constexpr WGPUSType shader_module_spirv          = WGPUSType_ShaderModuleSPIRVDescriptor;
    static constexpr WGPUSType shader_module_wgsl           = WGPUSType_ShaderModuleWGSLDescriptor;
    static constexpr WGPUSType primitive_depth_clip_control = WGPUSType_PrimitiveDepthClipControl;
    static constexpr WGPUSType surface_descriptor_from_wayland_surface =
        WGPUSType_SurfaceDescriptorFromWaylandSurface;
    static constexpr WGPUSType surface_descriptor_from_android_native_window =
        WGPUSType_SurfaceDescriptorFromAndroidNativeWindow;
    static constexpr WGPUSType surface_descriptor_from_xcb_window =
        WGPUSType_SurfaceDescriptorFromXcbWindow;
    static constexpr WGPUSType renderpass_descriptor_max_draw_count =
        WGPUSType_RenderPassDescriptorMaxDrawCount;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr stype() : wgpuenum(stype::invalid) {}
};

struct ECHIDNA_EXPORT sampler_binding_type
    : public wgpuenum<sampler_binding_type, WGPUSamplerBindingType> {
    static constexpr WGPUSamplerBindingType undefined     = WGPUSamplerBindingType_Undefined;
    static constexpr WGPUSamplerBindingType filtering     = WGPUSamplerBindingType_Filtering;
    static constexpr WGPUSamplerBindingType non_filtering = WGPUSamplerBindingType_NonFiltering;
    static constexpr WGPUSamplerBindingType comparison    = WGPUSamplerBindingType_Comparison;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr sampler_binding_type() : wgpuenum(sampler_binding_type::undefined) {}
};

struct ECHIDNA_EXPORT stencil_op : public wgpuenum<stencil_op, WGPUStencilOperation> {
    static constexpr WGPUStencilOperation keep            = WGPUStencilOperation_Keep;
    static constexpr WGPUStencilOperation zero            = WGPUStencilOperation_Zero;
    static constexpr WGPUStencilOperation replace         = WGPUStencilOperation_Replace;
    static constexpr WGPUStencilOperation invert          = WGPUStencilOperation_Invert;
    static constexpr WGPUStencilOperation increment_clamp = WGPUStencilOperation_IncrementClamp;
    static constexpr WGPUStencilOperation decrement_clamp = WGPUStencilOperation_DecrementClamp;
    static constexpr WGPUStencilOperation increment_wrap  = WGPUStencilOperation_IncrementWrap;
    static constexpr WGPUStencilOperation decrement_wrap  = WGPUStencilOperation_DecrementWrap;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT storage_texture_access
    : public wgpuenum<storage_texture_access, WGPUStorageTextureAccess> {
    static constexpr WGPUStorageTextureAccess undefined  = WGPUStorageTextureAccess_Undefined;
    static constexpr WGPUStorageTextureAccess write_only = WGPUStorageTextureAccess_WriteOnly;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr storage_texture_access() : wgpuenum(storage_texture_access::undefined) {}
};

struct ECHIDNA_EXPORT store_op : public wgpuenum<store_op, WGPUStoreOp> {
    static constexpr WGPUStoreOp undefined = WGPUStoreOp_Undefined;
    static constexpr WGPUStoreOp store     = WGPUStoreOp_Store;
    static constexpr WGPUStoreOp discard   = WGPUStoreOp_Discard;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    constexpr store_op() : wgpuenum(store_op::undefined) {}
};

struct ECHIDNA_EXPORT surface_get_current_texture_status
    : public wgpuenum<surface_get_current_texture_status, WGPUSurfaceGetCurrentTextureStatus> {
    static constexpr WGPUSurfaceGetCurrentTextureStatus success =
        WGPUSurfaceGetCurrentTextureStatus_Success;
    static constexpr WGPUSurfaceGetCurrentTextureStatus timeout =
        WGPUSurfaceGetCurrentTextureStatus_Timeout;
    static constexpr WGPUSurfaceGetCurrentTextureStatus outdated =
        WGPUSurfaceGetCurrentTextureStatus_Outdated;
    static constexpr WGPUSurfaceGetCurrentTextureStatus lost =
        WGPUSurfaceGetCurrentTextureStatus_Lost;
    static constexpr WGPUSurfaceGetCurrentTextureStatus out_of_memory =
        WGPUSurfaceGetCurrentTextureStatus_OutOfMemory;
    static constexpr WGPUSurfaceGetCurrentTextureStatus device_lost =
        WGPUSurfaceGetCurrentTextureStatus_DeviceLost;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT texture_aspect : wgpuenum<texture_aspect, WGPUTextureAspect> {
    static constexpr WGPUTextureAspect all          = WGPUTextureAspect_All;
    static constexpr WGPUTextureAspect stencil_only = WGPUTextureAspect_StencilOnly;
    static constexpr WGPUTextureAspect depth_only   = WGPUTextureAspect_DepthOnly;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT texture_dimension : public wgpuenum<texture_dimension, WGPUTextureDimension> {
    static constexpr WGPUTextureDimension dim1 = WGPUTextureDimension_1D;
    static constexpr WGPUTextureDimension dim2 = WGPUTextureDimension_2D;
    static constexpr WGPUTextureDimension dim3 = WGPUTextureDimension_3D;
};

struct ECHIDNA_EXPORT texture_format : wgpuenum<texture_format, WGPUTextureFormat> {
    static constexpr WGPUTextureFormat undefined        = WGPUTextureFormat_Undefined;
    static constexpr WGPUTextureFormat r8_unorm         = WGPUTextureFormat_R8Unorm;
    static constexpr WGPUTextureFormat r8_snorm         = WGPUTextureFormat_R8Snorm;
    static constexpr WGPUTextureFormat r8_uint          = WGPUTextureFormat_R8Uint;
    static constexpr WGPUTextureFormat r8_sint          = WGPUTextureFormat_R8Sint;
    static constexpr WGPUTextureFormat r16_uint         = WGPUTextureFormat_R16Uint;
    static constexpr WGPUTextureFormat r16_sint         = WGPUTextureFormat_R16Sint;
    static constexpr WGPUTextureFormat r16_float        = WGPUTextureFormat_R16Float;
    static constexpr WGPUTextureFormat rg8_unorm        = WGPUTextureFormat_RG8Unorm;
    static constexpr WGPUTextureFormat rg8_snorm        = WGPUTextureFormat_RG8Snorm;
    static constexpr WGPUTextureFormat rg8_uint         = WGPUTextureFormat_RG8Uint;
    static constexpr WGPUTextureFormat rg8_sint         = WGPUTextureFormat_RG8Sint;
    static constexpr WGPUTextureFormat r32_float        = WGPUTextureFormat_R32Float;
    static constexpr WGPUTextureFormat r32_uint         = WGPUTextureFormat_R32Uint;
    static constexpr WGPUTextureFormat r32_sint         = WGPUTextureFormat_R32Sint;
    static constexpr WGPUTextureFormat rg16_uint        = WGPUTextureFormat_RG16Uint;
    static constexpr WGPUTextureFormat rg16_sint        = WGPUTextureFormat_RG16Sint;
    static constexpr WGPUTextureFormat rg16_float       = WGPUTextureFormat_RG16Float;
    static constexpr WGPUTextureFormat rgba8_unorm      = WGPUTextureFormat_RGBA8Unorm;
    static constexpr WGPUTextureFormat rgba8_unorm_srgb = WGPUTextureFormat_RGBA8UnormSrgb;
    static constexpr WGPUTextureFormat rgba8_snorm      = WGPUTextureFormat_RGBA8Snorm;
    static constexpr WGPUTextureFormat rgba8_uint       = WGPUTextureFormat_RGBA8Uint;
    static constexpr WGPUTextureFormat rgba8_sint       = WGPUTextureFormat_RGBA8Sint;
    static constexpr WGPUTextureFormat bgra8_unorm      = WGPUTextureFormat_BGRA8Unorm;
    static constexpr WGPUTextureFormat bgra8_unorm_srgb = WGPUTextureFormat_BGRA8UnormSrgb;
    static constexpr WGPUTextureFormat rgb10_a2_unorm   = WGPUTextureFormat_RGB10A2Unorm;
    static constexpr WGPUTextureFormat rg11_b10_ufloat  = WGPUTextureFormat_RG11B10Ufloat;
    static constexpr WGPUTextureFormat rgb9_e5_ufloat   = WGPUTextureFormat_RGB9E5Ufloat;
    static constexpr WGPUTextureFormat rg32_float       = WGPUTextureFormat_RG32Float;
    static constexpr WGPUTextureFormat rg32_uint        = WGPUTextureFormat_RG32Uint;
    static constexpr WGPUTextureFormat rg32_sint        = WGPUTextureFormat_RG32Sint;
    static constexpr WGPUTextureFormat rgba16_uint      = WGPUTextureFormat_RGBA16Uint;
    static constexpr WGPUTextureFormat rgba16_sint      = WGPUTextureFormat_RGBA16Sint;
    static constexpr WGPUTextureFormat rgba16_float     = WGPUTextureFormat_RGBA16Float;
    static constexpr WGPUTextureFormat rgba32_float     = WGPUTextureFormat_RGBA32Float;
    static constexpr WGPUTextureFormat rgba32_uint      = WGPUTextureFormat_RGBA32Uint;
    static constexpr WGPUTextureFormat rgba32_sint      = WGPUTextureFormat_RGBA32Sint;
    static constexpr WGPUTextureFormat stencil8         = WGPUTextureFormat_Stencil8;
    static constexpr WGPUTextureFormat depth16_unorm    = WGPUTextureFormat_Depth16Unorm;
    static constexpr WGPUTextureFormat depth24_plus     = WGPUTextureFormat_Depth24Plus;
    static constexpr WGPUTextureFormat depth24_plus_stencil8 =
        WGPUTextureFormat_Depth24PlusStencil8;
    static constexpr WGPUTextureFormat depth32_float = WGPUTextureFormat_Depth32Float;
    static constexpr WGPUTextureFormat depth32_float_stencil8 =
        WGPUTextureFormat_Depth32FloatStencil8;
    static constexpr WGPUTextureFormat bc1_rgba_unorm       = WGPUTextureFormat_BC1RGBAUnorm;
    static constexpr WGPUTextureFormat bc1_rgba_unorm_srgb  = WGPUTextureFormat_BC1RGBAUnormSrgb;
    static constexpr WGPUTextureFormat bc2_rgba_unorm       = WGPUTextureFormat_BC2RGBAUnorm;
    static constexpr WGPUTextureFormat bc2_rgba_unorm_srgb  = WGPUTextureFormat_BC2RGBAUnormSrgb;
    static constexpr WGPUTextureFormat bc3_rgba_unorm       = WGPUTextureFormat_BC3RGBAUnorm;
    static constexpr WGPUTextureFormat bc3_rgba_unorm_srgb  = WGPUTextureFormat_BC3RGBAUnormSrgb;
    static constexpr WGPUTextureFormat bc4_r_unorm          = WGPUTextureFormat_BC4RUnorm;
    static constexpr WGPUTextureFormat bc4_r_snorm          = WGPUTextureFormat_BC4RSnorm;
    static constexpr WGPUTextureFormat bc5_rg_unorm         = WGPUTextureFormat_BC5RGUnorm;
    static constexpr WGPUTextureFormat bc5_rg_snorm         = WGPUTextureFormat_BC5RGSnorm;
    static constexpr WGPUTextureFormat bc6_hrgb_ufloat      = WGPUTextureFormat_BC6HRGBUfloat;
    static constexpr WGPUTextureFormat bc6_hrgb_float       = WGPUTextureFormat_BC6HRGBFloat;
    static constexpr WGPUTextureFormat bc7_rgba_unorm       = WGPUTextureFormat_BC7RGBAUnorm;
    static constexpr WGPUTextureFormat bc7_rgba_unorm_srgb  = WGPUTextureFormat_BC7RGBAUnormSrgb;
    static constexpr WGPUTextureFormat etc2_rgb8_unorm      = WGPUTextureFormat_ETC2RGB8Unorm;
    static constexpr WGPUTextureFormat etc2_rgb8_unorm_srgb = WGPUTextureFormat_ETC2RGB8UnormSrgb;
    static constexpr WGPUTextureFormat etc2_rgb8_a1_unorm   = WGPUTextureFormat_ETC2RGB8A1Unorm;
    static constexpr WGPUTextureFormat etc2_rgb8_a1_unorm_srgb =
        WGPUTextureFormat_ETC2RGB8A1UnormSrgb;
    static constexpr WGPUTextureFormat etc2_rgba8_unorm      = WGPUTextureFormat_ETC2RGBA8Unorm;
    static constexpr WGPUTextureFormat etc2_rgba8_unorm_srgb = WGPUTextureFormat_ETC2RGBA8UnormSrgb;
    static constexpr WGPUTextureFormat eac_r11_unorm         = WGPUTextureFormat_EACR11Unorm;
    static constexpr WGPUTextureFormat eac_r11_snorm         = WGPUTextureFormat_EACR11Snorm;
    static constexpr WGPUTextureFormat eac_rg11_unorm        = WGPUTextureFormat_EACRG11Unorm;
    static constexpr WGPUTextureFormat eac_rg11_snorm        = WGPUTextureFormat_EACRG11Snorm;
    static constexpr WGPUTextureFormat astc_4x4_unorm        = WGPUTextureFormat_ASTC4x4Unorm;
    static constexpr WGPUTextureFormat astc_4x4_unorm_srgb   = WGPUTextureFormat_ASTC4x4UnormSrgb;
    static constexpr WGPUTextureFormat astc_5x4_unorm        = WGPUTextureFormat_ASTC5x4Unorm;
    static constexpr WGPUTextureFormat astc_5x4_unorm_srgb   = WGPUTextureFormat_ASTC5x4UnormSrgb;
    static constexpr WGPUTextureFormat astc_5x5_unorm        = WGPUTextureFormat_ASTC5x5Unorm;
    static constexpr WGPUTextureFormat astc_5x5_unorm_srgb   = WGPUTextureFormat_ASTC5x5UnormSrgb;
    static constexpr WGPUTextureFormat astc_6x5_unorm        = WGPUTextureFormat_ASTC6x5Unorm;
    static constexpr WGPUTextureFormat astc_6x5_unorm_srgb   = WGPUTextureFormat_ASTC6x5UnormSrgb;
    static constexpr WGPUTextureFormat astc_6x6_unorm        = WGPUTextureFormat_ASTC6x6Unorm;
    static constexpr WGPUTextureFormat astc_6x6_unorm_srgb   = WGPUTextureFormat_ASTC6x6UnormSrgb;
    static constexpr WGPUTextureFormat astc_8x5_unorm        = WGPUTextureFormat_ASTC8x5Unorm;
    static constexpr WGPUTextureFormat astc_8x5_unorm_srgb   = WGPUTextureFormat_ASTC8x5UnormSrgb;
    static constexpr WGPUTextureFormat astc_8x6_unorm        = WGPUTextureFormat_ASTC8x6Unorm;
    static constexpr WGPUTextureFormat astc_8x6_unorm_srgb   = WGPUTextureFormat_ASTC8x6UnormSrgb;
    static constexpr WGPUTextureFormat astc_8x8_unorm        = WGPUTextureFormat_ASTC8x8Unorm;
    static constexpr WGPUTextureFormat astc_8x8_unorm_srgb   = WGPUTextureFormat_ASTC8x8UnormSrgb;
    static constexpr WGPUTextureFormat astc_10x5_unorm       = WGPUTextureFormat_ASTC10x5Unorm;
    static constexpr WGPUTextureFormat astc_10x5_unorm_srgb  = WGPUTextureFormat_ASTC10x5UnormSrgb;
    static constexpr WGPUTextureFormat astc_10x6_unorm       = WGPUTextureFormat_ASTC10x6Unorm;
    static constexpr WGPUTextureFormat astc_10x6_unorm_srgb  = WGPUTextureFormat_ASTC10x6UnormSrgb;
    static constexpr WGPUTextureFormat astc_10x8_unorm       = WGPUTextureFormat_ASTC10x8Unorm;
    static constexpr WGPUTextureFormat astc_10x8_unorm_srgb  = WGPUTextureFormat_ASTC10x8UnormSrgb;
    static constexpr WGPUTextureFormat astc_10x10_unorm      = WGPUTextureFormat_ASTC10x10Unorm;
    static constexpr WGPUTextureFormat astc_10x10_unorm_srgb = WGPUTextureFormat_ASTC10x10UnormSrgb;
    static constexpr WGPUTextureFormat astc_12x10_unorm      = WGPUTextureFormat_ASTC12x10Unorm;
    static constexpr WGPUTextureFormat astc_12x10_unorm_srgb = WGPUTextureFormat_ASTC12x10UnormSrgb;
    static constexpr WGPUTextureFormat astc_12x12_unorm      = WGPUTextureFormat_ASTC12x12Unorm;
    static constexpr WGPUTextureFormat astc_12x12_unorm_srgb = WGPUTextureFormat_ASTC12x12UnormSrgb;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT texture_sample_type
    : public wgpuenum<texture_sample_type, WGPUTextureSampleType> {
    static constexpr WGPUTextureSampleType undefined        = WGPUTextureSampleType_Undefined;
    static constexpr WGPUTextureSampleType filterable_float = WGPUTextureSampleType_Float;
    static constexpr WGPUTextureSampleType unfilterable_float =
        WGPUTextureSampleType_UnfilterableFloat;
    static constexpr WGPUTextureSampleType depth = WGPUTextureSampleType_Depth;
    static constexpr WGPUTextureSampleType sint  = WGPUTextureSampleType_Sint;
    static constexpr WGPUTextureSampleType uint  = WGPUTextureSampleType_Uint;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT texture_view_dimension
    : public wgpuenum<texture_view_dimension, WGPUTextureViewDimension> {
    static constexpr WGPUTextureViewDimension undefined  = WGPUTextureViewDimension_Undefined;
    static constexpr WGPUTextureViewDimension dim1       = WGPUTextureViewDimension_1D;
    static constexpr WGPUTextureViewDimension dim2       = WGPUTextureViewDimension_2D;
    static constexpr WGPUTextureViewDimension array2d    = WGPUTextureViewDimension_2DArray;
    static constexpr WGPUTextureViewDimension cube       = WGPUTextureViewDimension_Cube;
    static constexpr WGPUTextureViewDimension cube_array = WGPUTextureViewDimension_CubeArray;
    static constexpr WGPUTextureViewDimension dim3       = WGPUTextureViewDimension_3D;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT vertex_format : public wgpuenum<vertex_format, WGPUVertexFormat> {
    static constexpr WGPUVertexFormat undefined = WGPUVertexFormat_Undefined;
    static constexpr WGPUVertexFormat uint8x2   = WGPUVertexFormat_Uint8x2;
    static constexpr WGPUVertexFormat uint8x4   = WGPUVertexFormat_Uint8x4;
    static constexpr WGPUVertexFormat sint8x2   = WGPUVertexFormat_Sint8x2;
    static constexpr WGPUVertexFormat sint8x4   = WGPUVertexFormat_Sint8x4;
    static constexpr WGPUVertexFormat unorm8x2  = WGPUVertexFormat_Unorm8x2;
    static constexpr WGPUVertexFormat unorm8x4  = WGPUVertexFormat_Unorm8x4;
    static constexpr WGPUVertexFormat snorm8x2  = WGPUVertexFormat_Snorm8x2;
    static constexpr WGPUVertexFormat snorm8x4  = WGPUVertexFormat_Snorm8x4;
    static constexpr WGPUVertexFormat uint16x2  = WGPUVertexFormat_Uint16x2;
    static constexpr WGPUVertexFormat uint16x4  = WGPUVertexFormat_Uint16x4;
    static constexpr WGPUVertexFormat sint16x2  = WGPUVertexFormat_Sint16x2;
    static constexpr WGPUVertexFormat sint16x4  = WGPUVertexFormat_Sint16x4;
    static constexpr WGPUVertexFormat unorm16x2 = WGPUVertexFormat_Unorm16x2;
    static constexpr WGPUVertexFormat unorm16x4 = WGPUVertexFormat_Unorm16x4;
    static constexpr WGPUVertexFormat snorm16x2 = WGPUVertexFormat_Snorm16x2;
    static constexpr WGPUVertexFormat snorm16x4 = WGPUVertexFormat_Snorm16x4;
    static constexpr WGPUVertexFormat float16x2 = WGPUVertexFormat_Float16x2;
    static constexpr WGPUVertexFormat float16x4 = WGPUVertexFormat_Float16x4;
    static constexpr WGPUVertexFormat float32   = WGPUVertexFormat_Float32;
    static constexpr WGPUVertexFormat float32x2 = WGPUVertexFormat_Float32x2;
    static constexpr WGPUVertexFormat float32x3 = WGPUVertexFormat_Float32x3;
    static constexpr WGPUVertexFormat float32x4 = WGPUVertexFormat_Float32x4;
    static constexpr WGPUVertexFormat uint32    = WGPUVertexFormat_Uint32;
    static constexpr WGPUVertexFormat uint32x2  = WGPUVertexFormat_Uint32x2;
    static constexpr WGPUVertexFormat uint32x3  = WGPUVertexFormat_Uint32x3;
    static constexpr WGPUVertexFormat uint32x4  = WGPUVertexFormat_Uint32x4;
    static constexpr WGPUVertexFormat sint32    = WGPUVertexFormat_Sint32;
    static constexpr WGPUVertexFormat sint32x2  = WGPUVertexFormat_Sint32x2;
    static constexpr WGPUVertexFormat sint32x3  = WGPUVertexFormat_Sint32x3;
    static constexpr WGPUVertexFormat sint32x4  = WGPUVertexFormat_Sint32x4;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

struct ECHIDNA_EXPORT vertex_step_mode : public wgpuenum<vertex_step_mode, WGPUVertexStepMode> {
    static constexpr WGPUVertexStepMode vertex   = WGPUVertexStepMode_Vertex;
    static constexpr WGPUVertexStepMode instance = WGPUVertexStepMode_Instance;
    static constexpr WGPUVertexStepMode vertex_buffer_not_used =
        WGPUVertexStepMode_VertexBufferNotUsed;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
};

// Flags
struct ECHIDNA_EXPORT buffer_usage : public wgpuenum<buffer_usage, WGPUBufferUsageFlags> {
    static constexpr WGPUBufferUsage none          = WGPUBufferUsage_None;
    static constexpr WGPUBufferUsage map_read      = WGPUBufferUsage_MapRead;
    static constexpr WGPUBufferUsage map_write     = WGPUBufferUsage_MapWrite;
    static constexpr WGPUBufferUsage copy_src      = WGPUBufferUsage_CopySrc;
    static constexpr WGPUBufferUsage copy_dst      = WGPUBufferUsage_CopyDst;
    static constexpr WGPUBufferUsage index         = WGPUBufferUsage_Index;
    static constexpr WGPUBufferUsage vertex        = WGPUBufferUsage_Vertex;
    static constexpr WGPUBufferUsage uniform       = WGPUBufferUsage_Uniform;
    static constexpr WGPUBufferUsage storage       = WGPUBufferUsage_Storage;
    static constexpr WGPUBufferUsage indirect      = WGPUBufferUsage_Indirect;
    static constexpr WGPUBufferUsage query_resolve = WGPUBufferUsage_QueryResolve;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    using wgpuenum::operator|;
    using wgpuenum::operator&;
};

struct ECHIDNA_EXPORT color_write_mask
    : public wgpuenum<color_write_mask, WGPUColorWriteMaskFlags> {
    static constexpr WGPUColorWriteMask none  = WGPUColorWriteMask_None;
    static constexpr WGPUColorWriteMask red   = WGPUColorWriteMask_Red;
    static constexpr WGPUColorWriteMask green = WGPUColorWriteMask_Green;
    static constexpr WGPUColorWriteMask blue  = WGPUColorWriteMask_Blue;
    static constexpr WGPUColorWriteMask alpha = WGPUColorWriteMask_Alpha;
    static constexpr WGPUColorWriteMask all   = WGPUColorWriteMask_All;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    using wgpuenum::operator|;
    using wgpuenum::operator&;
};

struct ECHIDNA_EXPORT map_mode : public wgpuenum<map_mode, WGPUMapModeFlags> {
    static constexpr WGPUMapMode none  = WGPUMapMode_None;
    static constexpr WGPUMapMode read  = WGPUMapMode_Read;
    static constexpr WGPUMapMode write = WGPUMapMode_Write;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    using wgpuenum::operator|;
    using wgpuenum::operator&;
};

struct ECHIDNA_EXPORT shader_stage : public wgpuenum<shader_stage, WGPUShaderStageFlags> {
    static constexpr WGPUShaderStage none     = WGPUShaderStage_None;
    static constexpr WGPUShaderStage vertex   = WGPUShaderStage_Vertex;
    static constexpr WGPUShaderStage fragment = WGPUShaderStage_Fragment;
    static constexpr WGPUShaderStage compute  = WGPUShaderStage_Compute;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    using wgpuenum::operator|;
    using wgpuenum::operator&;
};

struct ECHIDNA_EXPORT texture_usage : public wgpuenum<texture_usage, WGPUTextureUsageFlags> {
    static constexpr WGPUTextureUsage none              = WGPUTextureUsage_None;
    static constexpr WGPUTextureUsage copy_src          = WGPUTextureUsage_CopySrc;
    static constexpr WGPUTextureUsage copy_dst          = WGPUTextureUsage_CopyDst;
    static constexpr WGPUTextureUsage texture_binding   = WGPUTextureUsage_TextureBinding;
    static constexpr WGPUTextureUsage storage_binding   = WGPUTextureUsage_StorageBinding;
    static constexpr WGPUTextureUsage render_attachment = WGPUTextureUsage_RenderAttachment;

    using wgpuenum::wgpuenum;
    using wgpuenum::operator=;
    using wgpuenum::operator==;
    using wgpuenum::operator|;
    using wgpuenum::operator&;
};

} // namespace echidna::webgpu