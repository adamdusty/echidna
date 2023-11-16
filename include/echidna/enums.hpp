#pragma once

#include <cstdint>
#include <vector>
#include <webgpu.h>

namespace echidna {

enum feature_name : std::uint32_t {
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

enum class composite_alpha_mode : std::uint32_t {
    automatic       = WGPUCompositeAlphaMode_Auto,
    opaque          = WGPUCompositeAlphaMode_Opaque,
    premultiplied   = WGPUCompositeAlphaMode_Premultiplied,
    unpremultiplied = WGPUCompositeAlphaMode_Unpremultiplied,
    inherit         = WGPUCompositeAlphaMode_Inherit,
};

enum class present_mode : std::uint32_t {
    fifo         = WGPUPresentMode_Fifo,
    fifo_relaxed = WGPUPresentMode_FifoRelaxed,
    immediate    = WGPUPresentMode_Immediate,
    mailbox      = WGPUPresentMode_Mailbox,
};

enum class texture_usage {
    none              = WGPUTextureUsage_None,
    copy_src          = WGPUTextureUsage_CopySrc,
    copy_dst          = WGPUTextureUsage_CopyDst,
    texture_binding   = WGPUTextureUsage_TextureBinding,
    storage_binding   = WGPUTextureUsage_StorageBinding,
    render_attachment = WGPUTextureUsage_RenderAttachment,
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

enum class power_preference : std::uint32_t {
    undefined        = WGPUPowerPreference_Undefined,
    low_power        = WGPUPowerPreference_LowPower,
    high_performance = WGPUPowerPreference_HighPerformance,
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

enum class request_adapter_status : std::uint32_t {
    success     = WGPURequestAdapterStatus_Success,
    unavailable = WGPURequestAdapterStatus_Unavailable,
    error       = WGPURequestAdapterStatus_Error,
    unknown     = WGPURequestAdapterStatus_Unknown,
};

constexpr auto operator==(WGPURequestAdapterStatus lhs, request_adapter_status rhs) {
    return lhs == static_cast<WGPURequestAdapterStatus>(rhs);
}

} // namespace echidna