#include "echidna/webgpu/shader.hpp"

namespace echidna::webgpu {

auto shader_module::compilation_info(WGPUCompilationInfoCallback callback, void* user_data) const
    -> void {
    wgpuShaderModuleGetCompilationInfo(_handle.get(), callback, user_data);
}

} // namespace echidna::webgpu