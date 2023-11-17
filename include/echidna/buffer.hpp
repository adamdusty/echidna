#pragma once

#include "echidna/enums.hpp"
#include "echidna/macros.hpp"
#include <cstddef>
#include <cstdint>
#include <webgpu.h>

namespace echidna {

// TODO: Functions for buffer descriptor creation

class buffer {
    HANDLE_IMPL(buffer, WGPUBuffer)

    auto get_mapped_range(size_t offset, size_t size) const -> void*;
    auto get_const_mapped_range(size_t offset, size_t size) const -> const void*;
    auto get_map_state() const -> buffer_map_state;
    auto size() const -> std::uint64_t;
    auto unmap() const -> void;
    auto map_async(
        map_mode_flags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void* user_data) const -> void;
};

} // namespace echidna