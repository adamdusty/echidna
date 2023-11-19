#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT bind_group_layout {
    HANDLE_IMPL(bind_group_layout, WGPUBindGroupLayout)

    ~bind_group_layout() {
        if(_handle != nullptr) {
            wgpuBindGroupLayoutRelease(_handle);
        }
    }
};

} // namespace echidna