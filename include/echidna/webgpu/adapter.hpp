#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/device.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include <webgpu.h>

namespace echidna::webgpu {

struct ECHIDNA_EXPORT adapter : public handle_base<adapter, WGPUAdapterImpl> {
    using handle_base::handle_base;
    using handle_base::operator=;

    auto limits() const -> WGPUSupportedLimits;
    auto properties() const -> WGPUAdapterProperties;
    auto features() const -> std::vector<feature_name>;
    auto has_feature(feature_name feature) const -> bool;
    auto request_device(const WGPUDeviceDescriptor& desc) const -> device;
};

} // namespace echidna::webgpu