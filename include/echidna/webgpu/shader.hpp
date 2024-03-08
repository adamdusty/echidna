#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
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

} // namespace echidna