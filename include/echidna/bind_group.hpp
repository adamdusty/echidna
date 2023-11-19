#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT bind_group {
    HANDLE_IMPL(bind_group, WGPUBindGroup)
    ~bind_group() {
        if(_handle != nullptr) {
            wgpuBindGroupRelease(_handle);
        }
    }
};

} // namespace echidna