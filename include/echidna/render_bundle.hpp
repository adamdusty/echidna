#pragma once

#include "echidna/export.hpp"
#include "echidna/macros.hpp"
#include <webgpu.h>

namespace echidna {

class ECHIDNA_EXPORT render_bundle {
    HANDLE_IMPL(render_bundle, WGPURenderBundle)
    ~render_bundle() {
        if(_handle != nullptr) {
            wgpuRenderBundleRelease(_handle);
        }
    }
};

} // namespace echidna