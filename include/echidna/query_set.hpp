#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT query_set {
    HANDLE_IMPL(query_set, WGPUQuerySet)
    ~query_set() {
        if(_handle != nullptr) {
            wgpuQuerySetDestroy(_handle);
            wgpuQuerySetRelease(_handle);
        }
    }
};

} // namespace echidna