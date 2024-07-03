#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <cstdint>
#include <echidna/webgpu.hpp>

namespace ew = echidna::webgpu;

inline auto get_surface_descriptor_from_window(SDL_Window* win) -> ew::surface_descriptor {

    SDL_SysWMinfo windowWMInfo;
    SDL_VERSION(&windowWMInfo.version);
    SDL_GetWindowWMInfo(win, &windowWMInfo);

#if defined(SDL_VIDEO_DRIVER_WAYLAND)
    struct wl_display* wayland_display = windowWMInfo.info.wl.display;
    struct wl_surface* wayland_surface = windowWMInfo.info.wl.surface;

    auto plat_desc = ew::surface_descriptor_from_wayland_surface(wayland_display, wayland_surface);
    auto desc      = ew::surface_descriptor(plat_desc, "wayland test surface");
    return desc;
#elif defined(SDL_VIDEO_DRIVER_X11)
    void* display        = windowWMInfo.info.x11.display;
    std::uint64_t window = windowWMInfo.info.x11.window;

    auto plat_desc = ew::surface_descriptor_from_xlib_window(display, window);
    auto desc      = ew::surface_descriptor(plat_desc, "x11 test window");

    return desc;
#elif defined(SDL_VIDEO_DRIVER_WINDOWS)
    void* inst = windowWMInfo.info.win.hinstance;
    void* hwnd = windowWMInfo.info.win.hwnd;

    auto plat_desc = ew::surface_descriptor_from_windows_hwnd(inst, hwnd);
    auto desc      = ew::surface_descriptor(plat_desc, "win32 test window");

    return desc;
#endif
}
