#include "echidna/webgpu/queue.hpp"

namespace echidna::webgpu {

auto queue::submit(std::vector<command_buffer>& commands) const -> void {
    auto wgpu_commands = std::vector<WGPUCommandBuffer>(commands.begin(), commands.end());
    wgpuQueueSubmit(_handle.get(), wgpu_commands.size(), wgpu_commands.data());
}

auto queue::write_buffer(const buffer& buffer, std::uint64_t offset, const void* data, size_t size)
    const -> void {
    wgpuQueueWriteBuffer(_handle.get(), buffer, offset, data, size);
}

} // namespace echidna::webgpu