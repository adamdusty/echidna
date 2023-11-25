#include "echidna/shader.hpp"

namespace echidna {

auto shader_module::compilation_info(WGPUCompilationInfoCallback callback, void* user_data) const -> void {
    wgpuShaderModuleGetCompilationInfo(_handle, callback, user_data);
}

} // namespace echidna