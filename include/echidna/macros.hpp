#pragma once

#include <utility>

#define HANDLE_IMPL(name, wgpu_type)                                                                                   \
    wgpu_type _handle{nullptr};                                                                                        \
                                                                                                                       \
public:                                                                                                                \
    constexpr explicit operator bool() {                                                                               \
        return _handle != nullptr;                                                                                     \
    }                                                                                                                  \
    constexpr operator wgpu_type() const {                                                                             \
        return _handle;                                                                                                \
    }                                                                                                                  \
    name(name&)           = delete;                                                                                    \
    auto operator=(name&) = delete;                                                                                    \
    name()                = default;                                                                                   \
    ~name()               = default;                                                                                   \
    explicit name(wgpu_type handle) : _handle(handle) {}                                                               \
    name(name&& other) noexcept : _handle(std::exchange(other._handle, nullptr)) {}                                    \
    auto operator=(name&& other) noexcept -> name& {                                                                   \
        _handle = std::exchange(other._handle, nullptr);                                                               \
        return *this;                                                                                                  \
    }

// For some reason the compiler is warning about backslash newline at the end of this file,
// so I'm adding this comment to shut it up.