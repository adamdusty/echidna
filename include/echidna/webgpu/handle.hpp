#pragma once

#include <utility>

namespace echidna::webgpu {

template<typename E, typename W>
class handle_base {
protected:
    W _handle = nullptr;

public:
    handle_base() = default;

    // Convert from WGPU opaque ptr
    constexpr handle_base(W handle) : _handle(handle) {}

    // Move constructor
    handle_base(handle_base&& other) noexcept : _handle(std::exchange(other._handle, nullptr)) {}

    // Copy constructor
    handle_base(const handle_base& other) : _handle(other._handle) {
        if(_handle != nullptr) {
            E::reference(_handle);
        }
    }

    // Move assign
    auto operator=(handle_base&& other) noexcept -> E& { // NOLINT
        _handle = std::exchange(other._handle, nullptr);
        return static_cast<E&>(*this);
    }

    // Copy assign
    auto operator=(const handle_base& other) -> E& { // NOLINT
        if(this == &other) {
            return static_cast<E&>(*this);
        }

        _handle = other._handle;
        E::reference(_handle);
        return static_cast<E&>(*this);
    }

    ~handle_base() {
        if(_handle != nullptr) {
            E::release(_handle);
        }
    }

    constexpr explicit operator bool() { return _handle != nullptr; }
    constexpr operator W() const {
        // if(_handle != nullptr) {
        //     E::reference(_handle);
        // }
        return _handle;
    }

    // Return pointer to handle
    constexpr auto addr() const -> const W* { return &_handle; }
};

} // namespace echidna::webgpu
