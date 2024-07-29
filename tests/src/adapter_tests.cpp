#include <echidna/echidna.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("API") {}

// #include <vector>

// using namespace echidna;

// TEST_CASE("Apapter limits", "[adpater]") {
//     auto inst_desc = instance_descriptor();
//     auto inst      = instance{inst_desc};
//     REQUIRE(inst);

//     auto opt   = adapter_options();
//     auto adapt = inst.request_adapter(opt);
//     REQUIRE(adapt);

//     auto limits = adapt.limits();

//     // Not sure how to test that limit acquisition actually worked
//     CHECK(limits.limits.maxBindGroups > 0);
// }

// TEST_CASE("Apapter properties", "[adpater]") {
//     auto inst_desc = instance_descriptor();
//     auto inst      = instance{inst_desc};
//     REQUIRE(inst);

//     auto opt   = adapter_options();
//     auto adapt = inst.request_adapter(opt);
//     REQUIRE(adapt);

//     auto props = adapt.properties();

//     // TODO: Not going to work if theres no discrete card obviously
//     CHECK(props.adapterType == adapter_type::discrete);
// }

// TEST_CASE("Adapter features", "[adapter]") {
//     auto inst_desc = instance_descriptor();
//     auto inst      = instance{inst_desc};
//     REQUIRE(inst);

//     auto opt   = adapter_options();
//     auto adapt = inst.request_adapter(opt);
//     REQUIRE(adapt);

//     auto feats = adapt.features();

//     // TODO: Can't guarantee this is true
//     CHECK(!feats.empty());
// }

// TEST_CASE("Adapter has feature", "[adapter]") {
//     auto inst_desc = instance_descriptor();
//     auto inst      = instance{inst_desc};
//     REQUIRE(inst);

//     auto opt   = adapter_options();
//     auto adapt = inst.request_adapter(opt);
//     REQUIRE(adapt);

//     auto depth_clip = adapt.has_feature(feature_name::depth_clip_control);

//     // TODO: Can't guarantee this is true
//     CHECK(depth_clip);
// }

// TEST_CASE("Adapter request device", "[adapter]") {
//     auto inst_desc = instance_descriptor();
//     auto inst      = instance{inst_desc};
//     REQUIRE(inst);

//     auto opt   = adapter_options();
//     auto adapt = inst.request_adapter(opt);
//     REQUIRE(adapt);

//     auto required_features = std::vector<feature_name>{feature_name::depth_clip_control};
//     auto required_limits   = std::vector<WGPURequiredLimits>{};

//     auto dev_desc = device_descriptor(
//         "test_device",
//         required_features,
//         required_limits,
//         {.nextInChain = nullptr, .label = "test_queue"},
//         device_lost_print_stderr,
//         nullptr
//     );

//     auto device = adapt.request_device(dev_desc);
//     REQUIRE(device);
// }