#include "echidna/buffer.hpp"

namespace echidna {

auto buffer::get_mapped_range(size_t offset, size_t size) const -> void* {
    return wgpuBufferGetMappedRange(_handle, offset, size);
}

auto buffer::get_const_mapped_range(size_t offset, size_t size) const -> const void* {
    return wgpuBufferGetConstMappedRange(_handle, offset, size);
}

auto buffer::get_map_state() const -> buffer_map_state {
    return static_cast<buffer_map_state>(wgpuBufferGetMapState(_handle));
}

auto buffer::size() const -> std::uint64_t {
    return wgpuBufferGetSize(_handle);
}

auto buffer::unmap() const -> void {
    wgpuBufferUnmap(_handle);
}

auto buffer::map_async(
    map_mode_flags mode, size_t offset, size_t size, WGPUBufferMapCallback callback, void* user_data) const -> void {
    wgpuBufferMapAsync(_handle, static_cast<WGPUMapModeFlags>(mode), offset, size, callback, user_data);
}

} // namespace echidna