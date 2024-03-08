#pragma once

#include "echidna/chained.hpp"
#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT shader_module : public handle_base<shader_module, WGPUShaderModule> {
    friend handle_base<shader_module, WGPUShaderModule>;
    static auto release(WGPUShaderModule handle) { wgpuShaderModuleRelease(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto compilation_info(WGPUCompilationInfoCallback callback, void* user_data) const -> void;
};

constexpr auto spirv_descriptor(std::uint32_t size, const std::uint32_t* code) -> WGPUShaderModuleSPIRVDescriptor {
    return WGPUShaderModuleSPIRVDescriptor{
        .chain    = chained_struct(stype::shader_module_spirv),
        .codeSize = size,
        .code     = code,
    };
}

constexpr auto wgsl_descriptor(const char* code) -> WGPUShaderModuleWGSLDescriptor {
    return WGPUShaderModuleWGSLDescriptor{
        .chain = chained_struct(stype::shader_module_wgsl),
        .code  = code,
    };
}

} // namespace echidna