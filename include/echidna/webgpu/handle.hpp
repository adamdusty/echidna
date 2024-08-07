#pragma once

#include <webgpu.h>

#include <memory>
#include <utility>

namespace echidna::webgpu {

struct deleter {
    auto operator()(WGPUAdapterImpl* impl) { wgpuAdapterRelease(impl); }
    auto operator()(WGPUBindGroupImpl* impl) { wgpuBindGroupRelease(impl); }
    auto operator()(WGPUBindGroupLayoutImpl* impl) { wgpuBindGroupLayoutRelease(impl); }
    auto operator()(WGPUBufferImpl* impl) { wgpuBufferRelease(impl); }
    auto operator()(WGPUCommandBufferImpl* impl) { wgpuCommandBufferRelease(impl); }
    auto operator()(WGPUCommandEncoderImpl* impl) { wgpuCommandEncoderRelease(impl); }
    auto operator()(WGPUComputePassEncoderImpl* impl) { wgpuComputePassEncoderRelease(impl); }
    auto operator()(WGPUComputePipelineImpl* impl) { wgpuComputePipelineRelease(impl); }
    auto operator()(WGPUDeviceImpl* impl) { wgpuDeviceRelease(impl); }
    auto operator()(WGPUInstanceImpl* impl) { wgpuInstanceRelease(impl); }
    auto operator()(WGPUPipelineLayoutImpl* impl) { wgpuPipelineLayoutRelease(impl); }
    auto operator()(WGPUQuerySetImpl* impl) { wgpuQuerySetRelease(impl); }
    auto operator()(WGPUQueueImpl* impl) { wgpuQueueRelease(impl); }
    auto operator()(WGPURenderBundleImpl* impl) { wgpuRenderBundleRelease(impl); }
    auto operator()(WGPURenderBundleEncoderImpl* impl) { wgpuRenderBundleEncoderRelease(impl); }
    auto operator()(WGPURenderPassEncoderImpl* impl) { wgpuRenderPassEncoderRelease(impl); }
    auto operator()(WGPURenderPipelineImpl* impl) { wgpuRenderPipelineRelease(impl); }
    auto operator()(WGPUSamplerImpl* impl) { wgpuSamplerRelease(impl); }
    auto operator()(WGPUShaderModuleImpl* impl) { wgpuShaderModuleRelease(impl); }
    auto operator()(WGPUSurfaceImpl* impl) { wgpuSurfaceRelease(impl); }
    auto operator()(WGPUTextureImpl* impl) { wgpuTextureRelease(impl); }
    auto operator()(WGPUTextureViewImpl* impl) { wgpuTextureViewRelease(impl); }
};

struct referencer {
    auto operator()(WGPUAdapterImpl* impl) { wgpuAdapterReference(impl); }
    auto operator()(WGPUBindGroupImpl* impl) { wgpuBindGroupReference(impl); }
    auto operator()(WGPUBindGroupLayoutImpl* impl) { wgpuBindGroupLayoutReference(impl); }
    auto operator()(WGPUBufferImpl* impl) { wgpuBufferReference(impl); }
    auto operator()(WGPUCommandBufferImpl* impl) { wgpuCommandBufferReference(impl); }
    auto operator()(WGPUCommandEncoderImpl* impl) { wgpuCommandEncoderReference(impl); }
    auto operator()(WGPUComputePassEncoderImpl* impl) { wgpuComputePassEncoderReference(impl); }
    auto operator()(WGPUComputePipelineImpl* impl) { wgpuComputePipelineReference(impl); }
    auto operator()(WGPUDeviceImpl* impl) { wgpuDeviceReference(impl); }
    auto operator()(WGPUInstanceImpl* impl) { wgpuInstanceReference(impl); }
    auto operator()(WGPUPipelineLayoutImpl* impl) { wgpuPipelineLayoutReference(impl); }
    auto operator()(WGPUQuerySetImpl* impl) { wgpuQuerySetReference(impl); }
    auto operator()(WGPUQueueImpl* impl) { wgpuQueueReference(impl); }
    auto operator()(WGPURenderBundleImpl* impl) { wgpuRenderBundleReference(impl); }
    auto operator()(WGPURenderBundleEncoderImpl* impl) { wgpuRenderBundleEncoderReference(impl); }
    auto operator()(WGPURenderPassEncoderImpl* impl) { wgpuRenderPassEncoderReference(impl); }
    auto operator()(WGPURenderPipelineImpl* impl) { wgpuRenderPipelineReference(impl); }
    auto operator()(WGPUSamplerImpl* impl) { wgpuSamplerReference(impl); }
    auto operator()(WGPUShaderModuleImpl* impl) { wgpuShaderModuleReference(impl); }
    auto operator()(WGPUSurfaceImpl* impl) { wgpuSurfaceReference(impl); }
    auto operator()(WGPUTextureImpl* impl) { wgpuTextureReference(impl); }
    auto operator()(WGPUTextureViewImpl* impl) { wgpuTextureViewReference(impl); }
};

template<typename E, typename W>
class handle_base {
protected:
    using handle_type   = std::unique_ptr<W, deleter>;
    handle_type _handle = nullptr;

public:
    handle_base() = default;

    // Convert from WGPU opaque ptr
    constexpr handle_base(W* handle) : _handle(handle_type(handle, deleter{})) {}

    // Move constructor
    handle_base(handle_base&& other) noexcept : _handle(std::move(other._handle)) {}

    // Copy constructor
    handle_base(const handle_base& other) : _handle(handle_type(other._handle.get(), deleter{})) {
        if(_handle != nullptr) {
            referencer{}(_handle.get());
        }
    }

    // Move assign
    auto operator=(handle_base&& other) noexcept -> E& { // NOLINT
        _handle = std::move(other._handle);
        return static_cast<E&>(*this);
    }

    // Copy assign
    auto operator=(const handle_base& other) -> E& { // NOLINT
        if(this == &other) {
            return static_cast<E&>(*this);
        }

        _handle = handle_type(other._handle.get(), deleter{});
        referencer{}(_handle.get());
        return static_cast<E&>(*this);
    }

    ~handle_base() = default;

    constexpr explicit operator bool() { return _handle != nullptr; }
    constexpr operator W*() const { return _handle.get(); }
};

} // namespace echidna::webgpu
