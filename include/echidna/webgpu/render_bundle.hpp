#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT render_bundle : public handle_base<render_bundle, WGPURenderBundleImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu