#pragma once

#include <webgpu.h>

#include "echidna/enums.hpp"

namespace echidna {

constexpr auto chained_struct(const WGPUChainedStruct* next, stype _type) {
    return WGPUChainedStruct{
        .next  = next,
        .sType = static_cast<WGPUSType>(_type),
    };
}

constexpr auto chained_struct(stype type) {
    return chained_struct(nullptr, type);
}

constexpr auto chained_struct() {
    return chained_struct(nullptr, stype::invalid);
}

} // namespace echidna

// struct ChainedStruct : public WGPUChainedStruct {
// public:
//   typedef ChainedStruct S;
//   typedef WGPUChainedStruct W;
//   ChainedStruct() : W() {}
//   ChainedStruct(const W &other) : W(other) {}
//   ChainedStruct(const DefaultFlag &) : W() { setDefault(); }
//   ChainedStruct &operator=(const DefaultFlag &) {
//     setDefault();
//     return *this;
//   }
//   friend auto operator<<(std ::ostream &stream, const S &) -> std ::ostream & {
//     return stream << "<wgpu::"
//                   << "ChainedStruct"
//                   << ">";
//   }

// public: