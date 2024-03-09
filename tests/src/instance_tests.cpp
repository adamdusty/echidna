#include <echidna/echidna.hpp>
#include <snitch/snitch.hpp>

using namespace echidna;

TEST_CASE("Instance request adapter", "[instance]") {
    auto inst_desc = instance_descriptor();
    auto inst      = instance{inst_desc};
    REQUIRE(inst);

    auto opt   = adapter_options(nullptr, backend_type::undefined, power_preference::high_performance, false);
    auto adapt = inst.request_adapter(opt);
    REQUIRE(adapt);
}

TEST_CASE("Instance request adapter, invalid backend", "[instance]") {
    auto inst_desc = instance_descriptor();
    auto inst      = instance{inst_desc};
    REQUIRE(inst);

    auto opt   = adapter_options(nullptr, backend_type::metal, power_preference::high_performance, false);
    auto adapt = inst.request_adapter(opt);
    CHECK(!adapt);
}