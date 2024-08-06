#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT texture_view : public handle_base<texture_view, WGPUTextureViewImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;
};

} // namespace echidna::webgpu