#pragma once

#include "echidna/chained.hpp"
#include "echidna/enums.hpp"
#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <cstdint>
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT shader_module {
    HANDLE_IMPL(shader_module, WGPUShaderModule)
    ~shader_module() {
        if(_handle != nullptr) {
            wgpuShaderModuleRelease(_handle);
        }
    }

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