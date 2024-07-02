#include "echidna/webgpu/query_set.hpp"

namespace echidna::webgpu {

auto query_set::count() const -> std::uint32_t {
    return wgpuQuerySetGetCount(_handle);
}

auto query_set::type() const -> query_type {
    return static_cast<query_type>(wgpuQuerySetGetType(_handle));
}

} // namespace echidna::webgpu