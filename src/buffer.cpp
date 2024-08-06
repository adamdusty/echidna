#include "echidna/webgpu/buffer.hpp"

namespace echidna::webgpu {

auto buffer::get_mapped_range(size_t offset, size_t size) const -> void* {
    return wgpuBufferGetMappedRange(_handle.get(), offset, size);
}

auto buffer::get_const_mapped_range(size_t offset, size_t size) const -> const void* {
    return wgpuBufferGetConstMappedRange(_handle.get(), offset, size);
}

auto buffer::get_map_state() const -> buffer_map_state {
    return wgpuBufferGetMapState(_handle.get());
}

auto buffer::size() const -> std::uint64_t {
    return wgpuBufferGetSize(_handle.get());
}

auto buffer::unmap() const -> void {
    wgpuBufferUnmap(_handle.get());
}

auto buffer::map_async(
    map_mode mode,
    size_t offset,
    size_t size,
    WGPUBufferMapCallback callback,
    void* user_data
) const -> void {
    wgpuBufferMapAsync(_handle.get(), mode, offset, size, callback, user_data);
}

} // namespace echidna::webgpu