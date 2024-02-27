auto main() -> int {return 0;}

// #define SDL_MAIN_HANDLED

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_syswm.h>
// #include <array>
// #include <cstdint>
// #include <echidna/echidna.hpp>
// #include <iostream>

// using namespace echidna;

// static constexpr auto shader_code = R"(
//     struct vertex_input{
//         @location(0) position: vec3f,
//         @location(1) color: vec3f,
//     };

//     struct vertex_output{
//         @builtin(position) position: vec4f,
//         @location(0) color: vec3f,
//     };

//     @vertex
//     fn vs_main(in: vertex_input) -> vertex_output {
//         var out: vertex_output;
//         out.position = vec4f(in.position, 1.0);
//         out.color = in.color;
//         return out;
//     }

//     @fragment
//     fn fs_main(in: vertex_output) -> @location(0) vec4f {
//         return vec4f(in.color, 1.0);
//     }
// )";

// // clang-format off
// static constexpr auto vertices = std::array<float, 18>{
//     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//     +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//     +0.0f, +0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
// };

// static constexpr auto indices = std::array<std::uint32_t,3>{
//     0, 1, 2,
// };
// // clang-format on

// auto main() -> int {
//     auto* window =
//         SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
//     SDL_SysWMinfo info;
//     SDL_VERSION(&info.version);
//     SDL_GetWindowWMInfo(window, &info);

//     auto inst_desc = instance_descriptor();
//     auto inst      = instance{inst_desc};

//     auto windows_surface_descriptor =
//         surface_descriptor_from_windows_hwnd(info.info.win.hinstance, info.info.win.window);
//     auto surf_desc = surface_descriptor(*reinterpret_cast<WGPUChainedStruct*>(&windows_surface_descriptor), "test");
//     auto surf      = inst.create_surface(surf_desc);

//     auto opt    = adapter_options(surf);
//     auto adapt  = inst.request_adapter(opt);
//     auto format = surf.preferred_format(adapt);

//     auto dev_desc = device_descriptor();
//     auto dev      = adapt.request_device(dev_desc);

//     auto queue = dev.get_queue();

//     auto surf_conf = surface_configuration(dev, surf.preferred_format(adapt), 1920, 1080);
//     surf.configure(surf_conf);

//     auto vertex_buffer =
//         dev.create_buffer(buffer_usage::vertex | buffer_usage::copy_dst, sizeof(float) * vertices.size());
//     auto index_buffer =
//         dev.create_buffer(buffer_usage::index | buffer_usage::copy_dst, sizeof(std::uint32_t) * indices.size());
//     queue.write_buffer(vertex_buffer, 0, vertices.data(), sizeof(float) * vertices.size());
//     queue.write_buffer(index_buffer, 0, indices.data(), sizeof(float) * indices.size());

//     auto clear_color = WGPUColor{0.05, 0.05, 0.05, 1.0};

//     auto shader_module = dev.shader_moudle_from_wgsl(shader_code);

//     auto color_state = color_target_state(surf.preferred_format(adapt), color_write_mask::all);

//     auto vertex_info =
//         echidna::vertex_buffer_layout(echidna::vertex_format::float32x3, echidna::vertex_format::float32x3);

//     auto vertex_state = WGPUVertexState{
//         .nextInChain   = nullptr,
//         .module        = shader_module,
//         .entryPoint    = "vs_main",
//         .constantCount = 0,
//         .constants     = nullptr,
//         .bufferCount   = 1,
//         .buffers       = &vertex_info.layout,
//     };

//     auto fragment_state = WGPUFragmentState{
//         .nextInChain   = nullptr,
//         .module        = shader_module,
//         .entryPoint    = "fs_main",
//         .constantCount = 0,
//         .constants     = nullptr,
//         .targetCount   = 1,
//         .targets       = &color_state,
//     };

//     auto primitive_state = echidna::primitive_state(
//         primitive_topology::triangle_list,
//         index_format::undefined,
//         front_face::ccw,
//         cull_mode::none
//     );

//     auto multi_sample_state = WGPUMultisampleState{
//         .nextInChain            = nullptr,
//         .count                  = 1,
//         .mask                   = ~0U,
//         .alphaToCoverageEnabled = false,
//     };

//     auto color_attach     = renderpass_color_attachment(load_op::clear, store_op::store, clear_color);
//     auto render_pass_desc = WGPURenderPassDescriptor{
//         .nextInChain            = nullptr,
//         .label                  = "render pass",
//         .colorAttachmentCount   = 1,
//         .colorAttachments       = &color_attach,
//         .depthStencilAttachment = nullptr,
//         .occlusionQuerySet      = nullptr,
//         .timestampWrites        = nullptr,
//     };

//     auto pipeline_layout_descriptor = WGPUPipelineLayoutDescriptor{
//         .nextInChain          = nullptr,
//         .label                = nullptr,
//         .bindGroupLayoutCount = 0,
//         .bindGroupLayouts     = nullptr,
//     };

//     auto pipeline_layout = dev.create_pipeline_layout(pipeline_layout_descriptor);

//     auto pipeline_desc = WGPURenderPipelineDescriptor{
//         .nextInChain  = nullptr,
//         .label        = nullptr,
//         .layout       = pipeline_layout,
//         .vertex       = vertex_state,
//         .primitive    = primitive_state,
//         .depthStencil = nullptr,
//         .multisample  = multi_sample_state,
//         .fragment     = &fragment_state,
//     };
//     auto pipeline = dev.create_render_pipeline(pipeline_desc);

//     auto cmds = std::vector<command_buffer>{};

//     auto quit  = false;
//     auto event = SDL_Event{};
//     while(!quit) {
//         while(SDL_PollEvent(&event) != 0) {
//             switch(event.type) {
//             case SDL_QUIT:
//                 quit = true;
//                 break;
//             case SDL_KEYDOWN:
//                 if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//                     quit = true;
//                 }
//                 break;
//             }
//         }

//         const auto& tex     = surf.current_texture();
//         const auto tex_view = tex->create_texture_view(tex->texture_view_descriptor());

//         color_attach.view = tex_view;

//         auto cmd_enc = dev.create_command_encoder("traingle encoder");
//         auto rp_enc  = cmd_enc.begin_render_pass(render_pass_desc);

//         rp_enc.set_pipeline(pipeline);
//         rp_enc.set_vertex_buffer(0, vertex_buffer, 0, vertex_buffer.size());
//         rp_enc.set_index_buffer(index_buffer, index_format::uint32, 0, index_buffer.size());

//         rp_enc.draw_indexed(indices.size(), 1, 0, 0, 0);

//         rp_enc.end();
//         cmds.emplace_back(cmd_enc.finish({}));
//         queue.submit(cmds);
//         surf.present();

//         cmds.clear();
//     }

//     SDL_DestroyWindow(window);
// }