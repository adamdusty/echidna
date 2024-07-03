#pragma once

#include "echidna/webgpu/enums.hpp"
#include <format>
#include <iostream>
#include <string>
#include <webgpu.h>

namespace echidna {

// constexpr auto device_lost_print_stderr = [](WGPUDeviceLostReason reason, char const* message, void*) {
//     auto loss_reason = reason == device_lost_reason::destroyed ? std::string{"destroyed"} : std::string{"undefined"};

//     std::cerr << std::format("Device Lost[{}]: {}", loss_reason, message);
// };

} // namespace echidna