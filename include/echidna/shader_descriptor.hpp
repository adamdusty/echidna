#pragma once

#include "echidna/chained.hpp"
#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include <cstdint>
#include <string>
#include <variant>
#include <vector>
#include <webgpu.h>

namespace echidna {

// struct ECHIDNA_EXPORT shader_descriptor {
//     using shader_language_descriptor = std::variant<WGPUShaderModuleWGSLDescriptor, WGPUShaderModuleSPIRVDescriptor>;
//     using shader_code                = std::variant<std::vector<std::uint32_t>, std::string>;

//     const char* label = nullptr;
//     shader_code code;
//     shader_language_descriptor descriptor;

//     static auto create(std::string_view code, const char* label = nullptr) -> shader_descriptor {
//         shader_descriptor desc;
//         desc.label = label;
//         desc.code  = std::string{code};

//         desc.descriptor = WGPUShaderModuleWGSLDescriptor{
//             .chain = chained_struct(stype::shader_module_wgsl),
//             .code  = std::get_if<std::string>(&desc.code)->c_str(),
//         };

//         return desc;
//     }

//     static auto create(std::vector<std::uint32_t>& code, const char* label = nullptr) -> shader_descriptor {
//         shader_descriptor desc;
//         desc.label = label;
//         desc.code  = std::vector{code};

//         desc.descriptor = WGPUShaderModuleSPIRVDescriptor{
//             .chain    = chained_struct(stype::shader_module_spirv),
//             .codeSize = static_cast<std::uint32_t>(std::get_if<std::vector<std::uint32_t>>(&desc.code)->size()),
//             .code     = std::get_if<std::vector<std::uint32_t>>(&desc.code)->data(),
//         };

//         return desc;
//     }

//     constexpr operator WGPUShaderModuleDescriptor() {
//         return WGPUShaderModuleDescriptor{
//             .nextInChain = &std::get_if<WGPUShaderModuleWGSLDescriptor>(&descriptor)->chain,
//             .label       = label,
//             .hintCount   = 0,
//             .hints       = nullptr
//         };
//     }
// };

// struct ECHIDNA_EXPORT wgsl_shader_descriptor {
//     WGPUChainedStruct chain = chained_struct(stype::shader_module_wgsl);
//     std::string code        = {};

//     constexpr wgsl_shader_descriptor(const char* code) : code(code) {}

//     operator WGPUShaderModuleWGSLDescriptor() { return {.chain = chain, .code = code.c_str()}; }

//     constexpr auto module_descriptor(const char* label = nullptr) -> WGPUShaderModuleDescriptor {
//         return WGPUShaderModuleDescriptor{
//             .nextInChain = &chain,
//             .label       = label,
//             .hintCount   = 0,
//             .hints       = nullptr,
//         };
//     }
// };

// constexpr auto spirv_descriptor(std::uint32_t size, const std::uint32_t* code) -> WGPUShaderModuleSPIRVDescriptor {
//     return WGPUShaderModuleSPIRVDescriptor{
//         .chain    = chained_struct(stype::shader_module_spirv),
//         .codeSize = size,
//         .code     = code,
//     };
// }

// constexpr auto wgsl_descriptor(const char* code) -> WGPUShaderModuleWGSLDescriptor {
//     return WGPUShaderModuleWGSLDescriptor{
//         .chain = chained_struct(stype::shader_module_wgsl),
//         .code  = code,
//     };
// }
} // namespace echidna