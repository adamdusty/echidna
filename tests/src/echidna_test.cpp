#include <echidna/adapter.hpp>
#include <echidna/device.hpp>
#include <echidna/echidna.hpp>
#include <echidna/instance.hpp>
#include <echidna/queue.hpp>
#include <echidna/surface.hpp>
#include <echidna/surface_descriptor.hpp>
#include <snitch/snitch.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

using namespace echidna;

TEST_CASE("Instance methods", "[instance]") {
    auto* window =
        SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_HIDDEN);
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);

    auto inst_desc = instance_descriptor();
    auto inst      = instance{inst_desc};
    REQUIRE(inst);

    auto windows_surface_descriptor =
        surface_descriptor_from_windows_hwnd(info.info.win.hinstance, info.info.win.window);
    auto surf_desc = surface_descriptor(*reinterpret_cast<WGPUChainedStruct*>(&windows_surface_descriptor), "test");
    auto surf      = inst.create_surface(surf_desc);
    REQUIRE(surf);

    auto opt   = adapter_options(surf);
    auto adapt = inst.request_adapter(opt);
    REQUIRE(adapt);

    auto format = surf.preferred_format(adapt);
    CHECK(format != texture_format::undefined);

    auto dev_desc = device_descriptor();
    auto dev      = adapt.request_device(dev_desc);
    dev.set_uncaptured_error_callback(device_error_stderr);
    REQUIRE(dev);

    auto queue = dev.get_queue();
    REQUIRE(queue);

    auto surf_conf = surface_configuration(dev, 1920, 1080);
    surf.configure(surf_conf);

    // const auto& tex = surf.current_texture();

    SDL_DestroyWindow(window);
}