#include <echidna/echidna.hpp>
#include <snitch/snitch.hpp>

#include "utils.hpp"

using namespace echidna;
using namespace echidna::webgpu;

TEST_CASE("Constructors", "[instance]") {
    SECTION("Default descriptor") {
        auto inst_desc = instance_descriptor();
        auto inst      = instance(inst_desc);
        CHECK(inst != nullptr);
    }
}

TEST_CASE("Create surface") {
    auto inst_desc = instance_descriptor();
    auto inst      = instance(inst_desc);
    CHECK(inst != nullptr);

    auto* window = SDL_CreateWindow("test", 0, 0, 1920, 1080, SDL_WINDOW_HIDDEN);
    auto desc    = get_surface_descriptor_from_window(window);
    auto surf    = inst.create_surface(desc);

    std::cerr << desc.label << '\n';
    CHECK(surf != nullptr);
}

TEST_CASE("Request adapter") {
    auto inst_desc = instance_descriptor();
    auto inst      = instance(inst_desc);
    REQUIRE(inst != nullptr);

    // auto opt   = request_adapter_options{};
    // auto adapt = inst.request_adapter()
}
