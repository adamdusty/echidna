#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT shader_module : public handle_base<shader_module, WGPUShaderModuleImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;

    auto compilation_info(WGPUCompilationInfoCallback callback, void* user_data) const -> void;
};

} // namespace echidna::webgpu