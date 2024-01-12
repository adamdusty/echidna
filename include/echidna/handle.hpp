#pragma once

#include <utility>

namespace echidna {

template<typename E, typename W>
class handle_base {
protected:
    W _handle;

public:
    handle_base()                      = default;
    handle_base(const handle_base&)    = delete;
    auto operator=(const handle_base&) = delete;
    handle_base(W handle) : _handle(handle) {}
    handle_base(handle_base&& other) noexcept : _handle(std::exchange(other._handle, nullptr)) {}
    ~handle_base() {
        if(_handle) {
            E::release(_handle);
        }
    }

    auto operator=(handle_base&& other) noexcept -> E& { // NOLINT
        _handle = std::exchange(other._handle, nullptr);
        return static_cast<E&>(*this);
    }

    constexpr explicit operator bool() { return _handle != nullptr; }
    constexpr operator W() const { return _handle; }
    constexpr auto get() -> W { return _handle; }
    constexpr auto addr() -> const W* { return &_handle; }
};

} // namespace echidna
