#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

class ECHIDNA_EXPORT render_bundle : public handle_base<render_bundle, WGPURenderBundle> {
    friend handle_base<render_bundle, WGPURenderBundle>;
    static auto release(WGPURenderBundle handle) { wgpuRenderBundleRelease(handle); }
    static auto reference(WGPURenderBundle handle) { wgpuRenderBundleReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu