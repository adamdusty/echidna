#pragma once

#include "echidna/export.hpp"
#include "echidna/webgpu/enums.hpp"
#include "echidna/webgpu/handle.hpp"
#include <cstddef>
#include <cstdint>
#include <webgpu.h>

namespace echidna::webgpu {

// TODO: Functions for buffer descriptor creation

class ECHIDNA_EXPORT buffer : public handle_base<buffer, WGPUBuffer> {
    friend handle_base<buffer, WGPUBuffer>;
    static auto release(WGPUBuffer handle) { wgpuBufferRelease(handle); }
    static auto reference(WGPUBuffer handle) { wgpuBufferReference(handle); }

public:
    using handle_base::handle_base;
    using handle_base::operator=;

    auto get_mapped_range(size_t offset, size_t size) const -> void*;
    auto get_const_mapped_range(size_t offset, size_t size) const -> const void*;
    auto get_map_state() const -> buffer_map_state;
    auto size() const -> std::uint64_t;
    auto unmap() const -> void;
    auto map_async(map_mode mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void* user_data) const
        -> void;
};

} // namespace echidna::webgpu