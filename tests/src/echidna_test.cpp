#include <echidna/echidna.hpp>
#include <echidna/surface_descriptor.hpp>
#include <snitch/snitch.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <bit>

using namespace echidna;

auto surface_descriptor_from_window(SDL_Window* win) -> WGPUSurfaceDescriptor {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(win, &info);
    WGPUSurfaceDescriptor desc;

#if defined(_WIN32) && _WIN32
    auto windows_surface_descriptor =
        surface_descriptor_from_windows_hwnd(info.info.win.hinstance, info.info.win.window);
    desc = surface_descriptor(*std::bit_cast<WGPUChainedStruct*>(&windows_surface_descriptor), "test");
#elif defined(__linux__) && __linux__
    if(info.subsystem == SDL_SYSWM_X11) {
        auto x11_desc = surface_descriptor_from_xlib_window(info.info.x11.display, info.info.x11.window);
        desc          = surface_descriptor(*std::bit_cast<WGPUChainedStruct*>(&x11_desc), "X11");
    } else if(info.subsystem == SDL_SYSWM_WAYLAND) {
        auto way_desc = surface_descriptor_from_wayland_surface(info.info.wl.display, info.info.wl.surface);
        desc          = surface_descriptor(*std::bit_cast<WGPUChainedStruct*>(&way_desc), "Wayland");
    }
#endif

    return desc;
}

TEST_CASE("Instance methods", "[instance]") {
    auto* window =
        SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_HIDDEN);
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);

    auto inst_desc = instance_descriptor();
    auto inst      = instance{inst_desc};
    REQUIRE(inst);

    auto desc = surface_descriptor_from_window(window);
    auto surf = inst.create_surface(desc);
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

    auto surf_conf = surface_configuration(dev, format, 1920, 1080);
    surf.configure(surf_conf);

    // const auto& tex = surf.current_texture();

    SDL_DestroyWindow(window);
}