#pragma once

#include "echidna/handle.hpp"
#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna {

enum class adapter_type : std::uint32_t {
    discrete   = WGPUAdapterType_DiscreteGPU,
    integrated = WGPUAdapterType_IntegratedGPU,
    cpu        = WGPUAdapterType_CPU,
    unknown    = WGPUAdapterType_Unknown,
};

enum class address_mode : std::uint32_t {
    repeat        = WGPUAddressMode_Repeat,
    mirror_repeat = WGPUAddressMode_MirrorRepeat,
    clamp_to_edge = WGPUAddressMode_ClampToEdge,
};

enum class backend_type : std::uint32_t {
    undefined = WGPUBackendType_Undefined,
    null      = WGPUBackendType_Null,
    webgpu    = WGPUBackendType_WebGPU,
    d3d11     = WGPUBackendType_D3D11,
    d3d12     = WGPUBackendType_D3D12,
    metal     = WGPUBackendType_Metal,
    vulkan    = WGPUBackendType_Vulkan,
    opengl    = WGPUBackendType_OpenGL,
    opengles  = WGPUBackendType_OpenGLES,
};

enum class blend_factor : std::uint32_t {
    zero                = WGPUBlendFactor_Zero,
    one                 = WGPUBlendFactor_One,
    src                 = WGPUBlendFactor_Src,
    one_minus_src       = WGPUBlendFactor_OneMinusSrc,
    src_alpha           = WGPUBlendFactor_SrcAlpha,
    one_minus_src_alpha = WGPUBlendFactor_OneMinusSrcAlpha,
    dst                 = WGPUBlendFactor_Dst,
    one_minus_dst       = WGPUBlendFactor_OneMinusDst,
    dst_alpha           = WGPUBlendFactor_DstAlpha,
    one_minus_dst_alpha = WGPUBlendFactor_OneMinusDstAlpha,
    src_alpha_saturated = WGPUBlendFactor_SrcAlphaSaturated,
    constant            = WGPUBlendFactor_Constant,
    one_minus_constant  = WGPUBlendFactor_OneMinusConstant,
};

enum class blend_op : std::uint32_t {
    add              = WGPUBlendOperation_Add,
    subtract         = WGPUBlendOperation_Subtract,
    reverse_subtract = WGPUBlendOperation_ReverseSubtract,
    min              = WGPUBlendOperation_Min,
    max              = WGPUBlendOperation_Max,
};

enum class buffer_binding_type : std::uint32_t {
    undefined         = WGPUBufferBindingType_Undefined,
    uniform           = WGPUBufferBindingType_Uniform,
    storage           = WGPUBufferBindingType_Storage,
    read_only_storage = WGPUBufferBindingType_ReadOnlyStorage,
};

enum class buffer_map_async_status : std::uint32_t {
    success                   = WGPUBufferMapAsyncStatus_Success,
    validation_error          = WGPUBufferMapAsyncStatus_ValidationError,
    unknown                   = WGPUBufferMapAsyncStatus_Unknown,
    device_lost               = WGPUBufferMapAsyncStatus_DeviceLost,
    destroyed_before_callback = WGPUBufferMapAsyncStatus_DestroyedBeforeCallback,
    unmapped_before_callback  = WGPUBufferMapAsyncStatus_UnmappedBeforeCallback,
    mapping_already_pending   = WGPUBufferMapAsyncStatus_MappingAlreadyPending,
    offset_out_of_range       = WGPUBufferMapAsyncStatus_OffsetOutOfRange,
    size_out_of_range         = WGPUBufferMapAsyncStatus_SizeOutOfRange,
};

enum class buffer_map_state : std::uint32_t {
    unmapped = WGPUBufferMapState_Unmapped,
    pending  = WGPUBufferMapState_Pending,
    mapped   = WGPUBufferMapState_Mapped,
};

enum class compare_function : std::uint32_t {
    undefined     = WGPUCompareFunction_Undefined,
    never         = WGPUCompareFunction_Never,
    less          = WGPUCompareFunction_Less,
    less_equal    = WGPUCompareFunction_LessEqual,
    greater       = WGPUCompareFunction_Greater,
    greater_equal = WGPUCompareFunction_GreaterEqual,
    equal         = WGPUCompareFunction_Equal,
    not_equal     = WGPUCompareFunction_NotEqual,
    always        = WGPUCompareFunction_Always,
};

enum class compilation_info_request_status : std::uint32_t {
    success     = WGPUCompilationInfoRequestStatus_Success,
    error       = WGPUCompilationInfoRequestStatus_Error,
    device_lost = WGPUCompilationInfoRequestStatus_DeviceLost,
    unknown     = WGPUCompilationInfoRequestStatus_Unknown,
};

enum class compilation_message_type : std::uint32_t {
    error   = WGPUCompilationMessageType_Error,
    warning = WGPUCompilationMessageType_Warning,
    info    = WGPUCompilationMessageType_Info,
};

enum class composite_alpha_mode : std::uint32_t {
    automatic       = WGPUCompositeAlphaMode_Auto,
    opaque          = WGPUCompositeAlphaMode_Opaque,
    premultiplied   = WGPUCompositeAlphaMode_Premultiplied,
    unpremultiplied = WGPUCompositeAlphaMode_Unpremultiplied,
    inherit         = WGPUCompositeAlphaMode_Inherit,
};

enum class create_pipeline_async_status : std::uint32_t {
    success          = WGPUCreatePipelineAsyncStatus_Success,
    validation_error = WGPUCreatePipelineAsyncStatus_ValidationError,
    internal_error   = WGPUCreatePipelineAsyncStatus_InternalError,
    device_lost      = WGPUCreatePipelineAsyncStatus_DeviceLost,
    device_destroyed = WGPUCreatePipelineAsyncStatus_DeviceDestroyed,
    unknown          = WGPUCreatePipelineAsyncStatus_Unknown,
};

enum class cull_mode : std::uint32_t {
    none  = WGPUCullMode_None,
    front = WGPUCullMode_Front,
    back  = WGPUCullMode_Back,
};

enum class device_lost_reason : std::uint32_t {
    undefined = WGPUDeviceLostReason_Undefined,
    destroyed = WGPUDeviceLostReason_Destroyed,
};

enum class error_filter : std::uint32_t {
    validation    = WGPUErrorFilter_Validation,
    out_of_memory = WGPUErrorFilter_OutOfMemory,
    internal      = WGPUErrorFilter_Internal,
};

enum class error_type : std::uint32_t {
    no_error      = WGPUErrorType_NoError,
    validation    = WGPUErrorType_Validation,
    out_of_memory = WGPUErrorType_OutOfMemory,
    internal      = WGPUErrorType_Internal,
    unknown       = WGPUErrorType_Unknown,
    device_lost   = WGPUErrorType_DeviceLost,
};

enum class feature_name : std::uint32_t {
    undefined                  = WGPUFeatureName_Undefined,
    depth_clip_control         = WGPUFeatureName_DepthClipControl,
    depth32_float_stencil8     = WGPUFeatureName_Depth32FloatStencil8,
    timestamp_query            = WGPUFeatureName_TimestampQuery,
    texture_compression_bc     = WGPUFeatureName_TextureCompressionBC,
    texture_compression_etc2   = WGPUFeatureName_TextureCompressionETC2,
    texture_compression_astc   = WGPUFeatureName_TextureCompressionASTC,
    indirect_first_instance    = WGPUFeatureName_IndirectFirstInstance,
    shader_f16                 = WGPUFeatureName_ShaderF16,
    rg11_b10_ufloat_renderable = WGPUFeatureName_RG11B10UfloatRenderable,
    bgra8_unorm_storage        = WGPUFeatureName_BGRA8UnormStorage,
    float32_filterable         = WGPUFeatureName_Float32Filterable,
};

enum class filter_mode : std::uint32_t {
    nearest = WGPUFilterMode_Nearest,
    linear  = WGPUFilterMode_Linear,
};

enum class front_face : std::uint32_t {

    ccw = WGPUFrontFace_CCW,
    cw  = WGPUFrontFace_CW,
};

enum class index_format : std::uint32_t {
    undefined = WGPUIndexFormat_Undefined,
    uint16    = WGPUIndexFormat_Uint16,
    uint32    = WGPUIndexFormat_Uint32,
};

enum class load_op : std::uint32_t {
    undefined = WGPULoadOp_Undefined,
    clear     = WGPULoadOp_Clear,
    load      = WGPULoadOp_Load,
};

enum class mipmap_filter_mode : std::uint32_t {
    nearest = WGPUMipmapFilterMode_Nearest,
    linear  = WGPUMipmapFilterMode_Linear,
};

enum class power_preference : std::uint32_t {
    undefined        = WGPUPowerPreference_Undefined,
    low_power        = WGPUPowerPreference_LowPower,
    high_performance = WGPUPowerPreference_HighPerformance,
};

enum class present_mode : std::uint32_t {
    fifo         = WGPUPresentMode_Fifo,
    fifo_relaxed = WGPUPresentMode_FifoRelaxed,
    immediate    = WGPUPresentMode_Immediate,
    mailbox      = WGPUPresentMode_Mailbox,
};

enum class primitive_topology : std::uint32_t {
    point_list     = WGPUPrimitiveTopology_PointList,
    line_list      = WGPUPrimitiveTopology_LineList,
    line_string    = WGPUPrimitiveTopology_LineStrip,
    triangle_list  = WGPUPrimitiveTopology_TriangleList,
    triangle_strip = WGPUPrimitiveTopology_TriangleStrip,
};

enum class query_type : std::uint32_t {
    occlusion = WGPUQueryType_Occlusion,
    timestamp = WGPUQueryType_Timestamp,
};

enum class queue_work_done_status : std::uint32_t {
    success     = WGPUQueueWorkDoneStatus_Success,
    error       = WGPUQueueWorkDoneStatus_Error,
    unknown     = WGPUQueueWorkDoneStatus_Unknown,
    device_lost = WGPUQueueWorkDoneStatus_DeviceLost,
};

enum class request_adapter_status : std::uint32_t {
    success     = WGPURequestAdapterStatus_Success,
    unavailable = WGPURequestAdapterStatus_Unavailable,
    error       = WGPURequestAdapterStatus_Error,
    unknown     = WGPURequestAdapterStatus_Unknown,
};

enum class requst_device_status : std::uint32_t {
    success = WGPURequestDeviceStatus_Success,
    error   = WGPURequestDeviceStatus_Error,
    unknown = WGPURequestDeviceStatus_Unknown,
};

enum class stype : std::uint32_t {
    invalid                                       = WGPUSType_Invalid,
    surface_descriptor_from_metal_layer           = WGPUSType_SurfaceDescriptorFromMetalLayer,
    surface_descriptor_from_windows_hwnd          = WGPUSType_SurfaceDescriptorFromWindowsHWND,
    surface_descriptor_from_xlib_window           = WGPUSType_SurfaceDescriptorFromXlibWindow,
    surface_descriptor_from_canvas_html_selector  = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector,
    shader_module_spirv                           = WGPUSType_ShaderModuleSPIRVDescriptor,
    shader_module_wgsl                            = WGPUSType_ShaderModuleWGSLDescriptor,
    primitive_depth_clip_control                  = WGPUSType_PrimitiveDepthClipControl,
    surface_descriptor_from_wayland_surface       = WGPUSType_SurfaceDescriptorFromWaylandSurface,
    surface_descriptor_from_android_native_window = WGPUSType_SurfaceDescriptorFromAndroidNativeWindow,
    surface_descriptor_from_xcb_window            = WGPUSType_SurfaceDescriptorFromXcbWindow,
    renderpass_descriptor_max_draw_count          = WGPUSType_RenderPassDescriptorMaxDrawCount,
};

enum class sampler_binding_type : std::uint32_t {
    undefined     = WGPUSamplerBindingType_Undefined,
    filtering     = WGPUSamplerBindingType_Filtering,
    non_filtering = WGPUSamplerBindingType_NonFiltering,
    comparison    = WGPUSamplerBindingType_Comparison,
};

enum class stencil_op : std::uint32_t {
    keep            = WGPUStencilOperation_Keep,
    zero            = WGPUStencilOperation_Zero,
    replace         = WGPUStencilOperation_Replace,
    invert          = WGPUStencilOperation_Invert,
    increment_clamp = WGPUStencilOperation_IncrementClamp,
    decrement_clamp = WGPUStencilOperation_DecrementClamp,
    increment_wrap  = WGPUStencilOperation_IncrementWrap,
    decrement_wrap  = WGPUStencilOperation_DecrementWrap,
};

enum class storage_texture_access : std::uint32_t {
    undefined  = WGPUStorageTextureAccess_Undefined,
    write_only = WGPUStorageTextureAccess_WriteOnly,
};

enum class store_op : std::uint32_t {
    undefined = WGPUStoreOp_Undefined,
    store     = WGPUStoreOp_Store,
    discard   = WGPUStoreOp_Discard,
};

enum class surface_get_current_texture_status : std::uint32_t {
    success       = WGPUSurfaceGetCurrentTextureStatus_Success,
    timeout       = WGPUSurfaceGetCurrentTextureStatus_Timeout,
    outdated      = WGPUSurfaceGetCurrentTextureStatus_Outdated,
    lost          = WGPUSurfaceGetCurrentTextureStatus_Lost,
    out_of_memory = WGPUSurfaceGetCurrentTextureStatus_OutOfMemory,
    device_lost   = WGPUSurfaceGetCurrentTextureStatus_DeviceLost,
};

enum class texture_aspect : std::uint32_t {
    all          = WGPUTextureAspect_All,
    stencil_only = WGPUTextureAspect_StencilOnly,
    depth_only   = WGPUTextureAspect_DepthOnly,
};

enum class texture_dimension : std::uint32_t {
    dim1 = WGPUTextureDimension_1D,
    dim2 = WGPUTextureDimension_2D,
    dim3 = WGPUTextureDimension_3D,
};

enum class texture_format {
    undefined               = WGPUTextureFormat_Undefined,
    r8_unorm                = WGPUTextureFormat_R8Unorm,
    r8_snorm                = WGPUTextureFormat_R8Snorm,
    r8_uint                 = WGPUTextureFormat_R8Uint,
    r8_sint                 = WGPUTextureFormat_R8Sint,
    r16_uint                = WGPUTextureFormat_R16Uint,
    r16_sint                = WGPUTextureFormat_R16Sint,
    r16_float               = WGPUTextureFormat_R16Float,
    rg8_unorm               = WGPUTextureFormat_RG8Unorm,
    rg8_snorm               = WGPUTextureFormat_RG8Snorm,
    rg8_uint                = WGPUTextureFormat_RG8Uint,
    rg8_sint                = WGPUTextureFormat_RG8Sint,
    r32_float               = WGPUTextureFormat_R32Float,
    r32_uint                = WGPUTextureFormat_R32Uint,
    r32_sint                = WGPUTextureFormat_R32Sint,
    rg16_uint               = WGPUTextureFormat_RG16Uint,
    rg16_sint               = WGPUTextureFormat_RG16Sint,
    rg16_float              = WGPUTextureFormat_RG16Float,
    rgba8_unorm             = WGPUTextureFormat_RGBA8Unorm,
    rgba8_unorm_srgb        = WGPUTextureFormat_RGBA8UnormSrgb,
    rgba8_snorm             = WGPUTextureFormat_RGBA8Snorm,
    rgba8_uint              = WGPUTextureFormat_RGBA8Uint,
    rgba8_sint              = WGPUTextureFormat_RGBA8Sint,
    bgra8_unorm             = WGPUTextureFormat_BGRA8Unorm,
    bgra8_unorm_srgb        = WGPUTextureFormat_BGRA8UnormSrgb,
    rgb10_a2_unorm          = WGPUTextureFormat_RGB10A2Unorm,
    rg11_b10_ufloat         = WGPUTextureFormat_RG11B10Ufloat,
    rgb9_e5_ufloat          = WGPUTextureFormat_RGB9E5Ufloat,
    rg32_float              = WGPUTextureFormat_RG32Float,
    rg32_uint               = WGPUTextureFormat_RG32Uint,
    rg32_sint               = WGPUTextureFormat_RG32Sint,
    rgba16_uint             = WGPUTextureFormat_RGBA16Uint,
    rgba16_sint             = WGPUTextureFormat_RGBA16Sint,
    rgba16_float            = WGPUTextureFormat_RGBA16Float,
    rgba32_float            = WGPUTextureFormat_RGBA32Float,
    rgba32_uint             = WGPUTextureFormat_RGBA32Uint,
    rgba32_sint             = WGPUTextureFormat_RGBA32Sint,
    stencil8                = WGPUTextureFormat_Stencil8,
    depth16_unorm           = WGPUTextureFormat_Depth16Unorm,
    depth24_plus            = WGPUTextureFormat_Depth24Plus,
    depth24_plus_stencil8   = WGPUTextureFormat_Depth24PlusStencil8,
    depth32_float           = WGPUTextureFormat_Depth32Float,
    depth32_float_stencil8  = WGPUTextureFormat_Depth32FloatStencil8,
    bc1_rgba_unorm          = WGPUTextureFormat_BC1RGBAUnorm,
    bc1_rgba_unorm_srgb     = WGPUTextureFormat_BC1RGBAUnormSrgb,
    bc2_rgba_unorm          = WGPUTextureFormat_BC2RGBAUnorm,
    bc2_rgba_unorm_srgb     = WGPUTextureFormat_BC2RGBAUnormSrgb,
    bc3_rgba_unorm          = WGPUTextureFormat_BC3RGBAUnorm,
    bc3_rgba_unorm_srgb     = WGPUTextureFormat_BC3RGBAUnormSrgb,
    bc4_r_unorm             = WGPUTextureFormat_BC4RUnorm,
    bc4_r_snorm             = WGPUTextureFormat_BC4RSnorm,
    bc5_rg_unorm            = WGPUTextureFormat_BC5RGUnorm,
    bc5_rg_snorm            = WGPUTextureFormat_BC5RGSnorm,
    bc6_hrgb_ufloat         = WGPUTextureFormat_BC6HRGBUfloat,
    bc6_hrgb_float          = WGPUTextureFormat_BC6HRGBFloat,
    bc7_rgba_unorm          = WGPUTextureFormat_BC7RGBAUnorm,
    bc7_rgba_unorm_srgb     = WGPUTextureFormat_BC7RGBAUnormSrgb,
    etc2_rgb8_unorm         = WGPUTextureFormat_ETC2RGB8Unorm,
    etc2_rgb8_unorm_srgb    = WGPUTextureFormat_ETC2RGB8UnormSrgb,
    etc2_rgb8_a1_unorm      = WGPUTextureFormat_ETC2RGB8A1Unorm,
    etc2_rgb8_a1_unorm_srgb = WGPUTextureFormat_ETC2RGB8A1UnormSrgb,
    etc2_rgba8_unorm        = WGPUTextureFormat_ETC2RGBA8Unorm,
    etc2_rgba8_unorm_srgb   = WGPUTextureFormat_ETC2RGBA8UnormSrgb,
    eac_r11_unorm           = WGPUTextureFormat_EACR11Unorm,
    eac_r11_snorm           = WGPUTextureFormat_EACR11Snorm,
    eac_rg11_unorm          = WGPUTextureFormat_EACRG11Unorm,
    eac_rg11_snorm          = WGPUTextureFormat_EACRG11Snorm,
    astc_4x4_unorm          = WGPUTextureFormat_ASTC4x4Unorm,
    astc_4x4_unorm_srgb     = WGPUTextureFormat_ASTC4x4UnormSrgb,
    astc_5x4_unorm          = WGPUTextureFormat_ASTC5x4Unorm,
    astc_5x4_unorm_srgb     = WGPUTextureFormat_ASTC5x4UnormSrgb,
    astc_5x5_unorm          = WGPUTextureFormat_ASTC5x5Unorm,
    astc_5x5_unorm_srgb     = WGPUTextureFormat_ASTC5x5UnormSrgb,
    astc_6x5_unorm          = WGPUTextureFormat_ASTC6x5Unorm,
    astc_6x5_unorm_srgb     = WGPUTextureFormat_ASTC6x5UnormSrgb,
    astc_6x6_unorm          = WGPUTextureFormat_ASTC6x6Unorm,
    astc_6x6_unorm_srgb     = WGPUTextureFormat_ASTC6x6UnormSrgb,
    astc_8x5_unorm          = WGPUTextureFormat_ASTC8x5Unorm,
    astc_8x5_unorm_srgb     = WGPUTextureFormat_ASTC8x5UnormSrgb,
    astc_8x6_unorm          = WGPUTextureFormat_ASTC8x6Unorm,
    astc_8x6_unorm_srgb     = WGPUTextureFormat_ASTC8x6UnormSrgb,
    astc_8x8_unorm          = WGPUTextureFormat_ASTC8x8Unorm,
    astc_8x8_unorm_srgb     = WGPUTextureFormat_ASTC8x8UnormSrgb,
    astc_10x5_unorm         = WGPUTextureFormat_ASTC10x5Unorm,
    astc_10x5_unorm_srgb    = WGPUTextureFormat_ASTC10x5UnormSrgb,
    astc_10x6_unorm         = WGPUTextureFormat_ASTC10x6Unorm,
    astc_10x6_unorm_srgb    = WGPUTextureFormat_ASTC10x6UnormSrgb,
    astc_10x8_unorm         = WGPUTextureFormat_ASTC10x8Unorm,
    astc_10x8_unorm_srgb    = WGPUTextureFormat_ASTC10x8UnormSrgb,
    astc_10x10_unorm        = WGPUTextureFormat_ASTC10x10Unorm,
    astc_10x10_unorm_srgb   = WGPUTextureFormat_ASTC10x10UnormSrgb,
    astc_12x10_unorm        = WGPUTextureFormat_ASTC12x10Unorm,
    astc_12x10_unorm_srgb   = WGPUTextureFormat_ASTC12x10UnormSrgb,
    astc_12x12_unorm        = WGPUTextureFormat_ASTC12x12Unorm,
    astc_12x12_unorm_srgb   = WGPUTextureFormat_ASTC12x12UnormSrgb,
};

enum class texture_sample_type : std::uint32_t {
    undefined          = WGPUTextureSampleType_Undefined,
    filterable_float   = WGPUTextureSampleType_Float,
    unfilterable_float = WGPUTextureSampleType_UnfilterableFloat,
    depth              = WGPUTextureSampleType_Depth,
    sint               = WGPUTextureSampleType_Sint,
    uint               = WGPUTextureSampleType_Uint,
};

enum class textureview_dimension : std::uint32_t {
    undefined  = WGPUTextureViewDimension_Undefined,
    dim1       = WGPUTextureViewDimension_1D,
    dim2       = WGPUTextureViewDimension_2D,
    array2d    = WGPUTextureViewDimension_2DArray,
    cube       = WGPUTextureViewDimension_Cube,
    cube_array = WGPUTextureViewDimension_CubeArray,
    dim3       = WGPUTextureViewDimension_3D,
};

enum class vertex_format : std::uint32_t {
    undefined = WGPUVertexFormat_Undefined,
    uint8x2   = WGPUVertexFormat_Uint8x2,
    uint8x4   = WGPUVertexFormat_Uint8x4,
    sint8x2   = WGPUVertexFormat_Sint8x2,
    sint8x4   = WGPUVertexFormat_Sint8x4,
    unorm8x2  = WGPUVertexFormat_Unorm8x2,
    unorm8x4  = WGPUVertexFormat_Unorm8x4,
    snorm8x2  = WGPUVertexFormat_Snorm8x2,
    snorm8x4  = WGPUVertexFormat_Snorm8x4,
    uint16x2  = WGPUVertexFormat_Uint16x2,
    uint16x4  = WGPUVertexFormat_Uint16x4,
    sint16x2  = WGPUVertexFormat_Sint16x2,
    sint16x4  = WGPUVertexFormat_Sint16x4,
    unorm16x2 = WGPUVertexFormat_Unorm16x2,
    unorm16x4 = WGPUVertexFormat_Unorm16x4,
    snorm16x2 = WGPUVertexFormat_Snorm16x2,
    snorm16x4 = WGPUVertexFormat_Snorm16x4,
    float16x2 = WGPUVertexFormat_Float16x2,
    float16x4 = WGPUVertexFormat_Float16x4,
    float32   = WGPUVertexFormat_Float32,
    float32x2 = WGPUVertexFormat_Float32x2,
    float32x3 = WGPUVertexFormat_Float32x3,
    float32x4 = WGPUVertexFormat_Float32x4,
    uint32    = WGPUVertexFormat_Uint32,
    uint32x2  = WGPUVertexFormat_Uint32x2,
    uint32x3  = WGPUVertexFormat_Uint32x3,
    uint32x4  = WGPUVertexFormat_Uint32x4,
    sint32    = WGPUVertexFormat_Sint32,
    sint32x2  = WGPUVertexFormat_Sint32x2,
    sint32x3  = WGPUVertexFormat_Sint32x3,
    sint32x4  = WGPUVertexFormat_Sint32x4,
};

enum class vertex_step_mode {
    vertex                 = WGPUVertexStepMode_Vertex,
    instance               = WGPUVertexStepMode_Instance,
    vertex_buffer_not_used = WGPUVertexStepMode_VertexBufferNotUsed,
};

// Flags
enum class buffer_usage : std::uint32_t {
    none          = WGPUBufferUsage_None,
    map_read      = WGPUBufferUsage_MapRead,
    map_write     = WGPUBufferUsage_MapWrite,
    copy_src      = WGPUBufferUsage_CopySrc,
    copy_dst      = WGPUBufferUsage_CopyDst,
    index         = WGPUBufferUsage_Index,
    vertex        = WGPUBufferUsage_Vertex,
    uniform       = WGPUBufferUsage_Uniform,
    storage       = WGPUBufferUsage_Storage,
    indirect      = WGPUBufferUsage_Indirect,
    query_resolve = WGPUBufferUsage_QueryResolve,
};

enum class color_write_mask : std::uint32_t {
    none  = WGPUColorWriteMask_None,
    red   = WGPUColorWriteMask_Red,
    green = WGPUColorWriteMask_Green,
    blue  = WGPUColorWriteMask_Blue,
    alpha = WGPUColorWriteMask_Alpha,
    all   = WGPUColorWriteMask_All,
};

enum class map_mode : std::uint32_t {
    none  = WGPUMapMode_None,
    read  = WGPUMapMode_Read,
    write = WGPUMapMode_Write,
};

enum class shader_stage : std::uint32_t {
    none     = WGPUShaderStage_None,
    vertex   = WGPUShaderStage_Vertex,
    fragment = WGPUShaderStage_Fragment,
    compute  = WGPUShaderStage_Compute,
};

enum class texture_usage : std::uint32_t {
    none              = WGPUTextureUsage_None,
    copy_src          = WGPUTextureUsage_CopySrc,
    copy_dst          = WGPUTextureUsage_CopyDst,
    texture_binding   = WGPUTextureUsage_TextureBinding,
    storage_binding   = WGPUTextureUsage_StorageBinding,
    render_attachment = WGPUTextureUsage_RenderAttachment,
};

constexpr auto operator==(WGPURequestAdapterStatus lhs, request_adapter_status rhs) {
    return lhs == static_cast<WGPURequestAdapterStatus>(rhs);
}

constexpr auto operator|(buffer_usage lhs, buffer_usage rhs) -> buffer_usage {
    return static_cast<buffer_usage>(
        static_cast<std::underlying_type_t<buffer_usage>>(lhs) | static_cast<std::underlying_type_t<buffer_usage>>(rhs)
    );
}

constexpr auto operator&(buffer_usage lhs, buffer_usage rhs) -> buffer_usage {
    return static_cast<buffer_usage>(
        static_cast<std::underlying_type_t<buffer_usage>>(lhs) & static_cast<std::underlying_type_t<buffer_usage>>(rhs)
    );
}

constexpr auto operator|(shader_stage lhs, shader_stage rhs) -> shader_stage {
    return static_cast<shader_stage>(
        static_cast<std::underlying_type_t<shader_stage>>(lhs) | static_cast<std::underlying_type_t<shader_stage>>(rhs)
    );
}

constexpr auto operator&(shader_stage lhs, shader_stage rhs) -> shader_stage {
    return static_cast<shader_stage>(
        static_cast<std::underlying_type_t<shader_stage>>(lhs) & static_cast<std::underlying_type_t<shader_stage>>(rhs)
    );
}

constexpr auto operator|(map_mode lhs, map_mode rhs) -> map_mode {
    return static_cast<map_mode>(
        static_cast<std::underlying_type_t<map_mode>>(lhs) | static_cast<std::underlying_type_t<map_mode>>(rhs)
    );
}

constexpr auto operator&(map_mode lhs, map_mode rhs) -> map_mode {
    return static_cast<map_mode>(
        static_cast<std::underlying_type_t<map_mode>>(lhs) & static_cast<std::underlying_type_t<map_mode>>(rhs)
    );
}

constexpr auto operator|(texture_usage lhs, texture_usage rhs) -> texture_usage {
    return static_cast<texture_usage>(
        static_cast<std::underlying_type_t<texture_usage>>(lhs) |
        static_cast<std::underlying_type_t<texture_usage>>(rhs)
    );
}

constexpr auto operator&(texture_usage lhs, texture_usage rhs) -> texture_usage {
    return static_cast<texture_usage>(
        static_cast<std::underlying_type_t<texture_usage>>(lhs) &
        static_cast<std::underlying_type_t<texture_usage>>(rhs)
    );
}

} // namespace echidna