#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <admat/mat.hpp>
#include <array>
#include <chrono>
#include <cstdint>
#include <echidna/webgpu.hpp>
#include <iostream>
#include <vector>

using namespace echidna::webgpu;

static constexpr auto shader_code = R"(
    struct vertex_input{
        @location(0) position: vec3f,
        @location(1) normal: vec3f,
    };

    struct vertex_output{
        @builtin(position) position: vec4f,
        @location(0) frag_pos: vec3f,
        @location(1) normal: vec3f,
    };

    struct mvp{
        proj: mat4x4f,
        view: mat4x4f,
        model: mat4x4f,
        model_it: mat4x4f,
    }

    struct light{
        pos: vec3f,
        view: vec3f,
        color: vec3f,
    }

    @group(0) @binding(0) var<uniform> u_mvp: mvp;
    @group(0) @binding(0) var<uniform> u_light: light;

    @vertex
    fn vs_main(in: vertex_input) -> vertex_output {
        var out: vertex_output;
        out.position = u_mvp.proj * u_mvp.view * u_mvp.model *  vec4f(in.position, 1.0);
        out.frag_pos = (u_mvp.model * vec4f(in.position, 1.0)).xyz;
        out.normal = (u_mvp.model * vec4f(in.normal, 0.0)).xyz;
        return out;
    }

    @fragment
    fn fs_main(in: vertex_output) -> @location(0) vec4f {
        var hcl: light;
        hcl.pos = vec3f(0.0, 0.0, -10.0);
        hcl.view = vec3f(0.0, 0.0, 10.0);
        hcl.color = vec3f(1.0, 1.0, 1.0);

        var ambient_strength = 0.1;
        var ambient = ambient_strength * hcl.color;

        var norm = normalize(in.normal);
        var light_direction = normalize(hcl.pos - in.frag_pos);
        var diff = max(dot(norm, light_direction), 0.0);
        var diffuse = diff * hcl.color;

        var specular_strength = 0.3;
        var view_direction = normalize(hcl.view - in.frag_pos);
        var reflect_direction = reflect(-light_direction, norm);
        var spec = pow(max(dot(view_direction, reflect_direction), 0.0), 256.0);
        var specular = specular_strength * spec * hcl.color;

        return vec4f((ambient + diffuse + specular) * vec3f(0.0, 1.0, 0.0), 1.0);
    }
)";

// clang-format off
static constexpr auto vertices = std::array<float, 144>{
    // Front
    -0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 1.0f,
    +0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 1.0f,
    +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 1.0f,

    // Back
    +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, +0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

    // Top
    -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f,
    +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f,

    // Bottom
    -0.5f, -0.5f, +0.5f, 0.0f, -1.0f, 0.0f,
    +0.5f, -0.5f, +0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    +0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    // Left
    -0.5f, +0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, +0.5f, +0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, +0.5f, -1.0f, 0.0f, 0.0f,

    // Right
    +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 0.0f,
    +0.5f, +0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
};

static constexpr auto indices = std::array<std::uint32_t,36>{
    0,1,2, 1,3,2,
    4,5,6, 5,7,6,
    8,9,10, 9,11,10,
    12,13,14, 13,15,14,
    16,17,18, 17,19,18,
    20,21,22, 21,23,22,
};
// clang-format on

auto main() -> int {
    // GPU Initialization
    auto* window = SDL_CreateWindow(
        "test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN
    );
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);

    // WGPUInstanceExtras instanceExtras = {};
    // instanceExtras.chain.sType        = (WGPUSType)WGPUSType_InstanceExtras;
    // instanceExtras.backends           = WGPUInstanceBackend_GL;

    // WGPUInstanceDescriptor instanceDescriptor = {};
    // instanceDescriptor.nextInChain            = &instanceExtras.chain;

    auto inst = instance(instance_descriptor());

    auto surf_desc = surface_descriptor();

    if(info.subsystem == SDL_SYSWM_X11) {
        std::cerr << "x11" << '\n';
        auto plat =
            surface_descriptor_from_xlib_window(info.info.x11.display, info.info.x11.window);
        surf_desc = surface_descriptor(plat, "xlib_window");
    } else {
        std::cerr << "wayland" << '\n';
        auto plat =
            surface_descriptor_from_wayland_surface(info.info.wl.display, info.info.wl.surface);
        surf_desc = surface_descriptor(plat, "wayland_window");
    }

    auto surf = inst.create_surface(surf_desc);

    auto opt   = request_adapter_options(surf);
    auto adapt = inst.request_adapter(opt);

    auto dev_desc = device_descriptor();
    auto dev      = adapt.request_device(dev_desc);

    auto queue = dev.get_queue();

    auto format    = surf.preferred_format(adapt);
    auto surf_conf = surface_configuration(dev, surf.preferred_format(adapt), 1920, 1080);
    surf.configure(surf_conf);

    // Initialize rendering buffers
    auto vertex_buffer = dev.create_buffer(
        buffer_usage::vertex | buffer_usage::copy_dst,
        sizeof(float) * vertices.size()
    );
    auto index_buffer = dev.create_buffer(
        buffer_usage::index | buffer_usage::copy_dst,
        sizeof(std::uint32_t) * indices.size()
    );
    auto mvp_buffer =
        dev.create_buffer(buffer_usage::uniform | buffer_usage::copy_dst, sizeof(admat::mat4) * 4);
    auto light_buffer =
        dev.create_buffer(buffer_usage::uniform | buffer_usage::copy_dst, sizeof(admat::vec3) * 3);

    // Write static buffer data
    queue.write_buffer(vertex_buffer, 0, vertices.data(), sizeof(float) * vertices.size());
    queue.write_buffer(index_buffer, 0, indices.data(), sizeof(float) * indices.size());

    // Bind group layout
    auto bind_group_layout_entries = std::vector<bind_group_layout_entry>();
    bind_group_layout_entries.emplace_back(
        0,
        shader_stage::vertex | shader_stage::fragment,
        buffer_binding_layout(buffer_binding_type::uniform, false, mvp_buffer.size())
    );

    // auto bgld = bind_group_layout_desc(bind_group_layout_entries);
    auto bgld      = bind_group_layout_descriptor("Bind group 1", bind_group_layout_entries);
    auto wgpu_bgld = static_cast<WGPUBindGroupLayoutDescriptor>(bgld);
    auto bgl       = dev.create_bind_group_layout(bgld);

    // Bind group entries
    auto mvp_bge = bind_group_entry(0, mvp_buffer, 0, mvp_buffer.size());

    auto bind_group_entries = std::vector<bind_group_entry>();
    bind_group_entries.emplace_back(mvp_bge);

    // Bind group
    auto bind_group = dev.create_bind_group(bind_group_descriptor(bgl, bind_group_entries));

    auto clear_color = WGPUColor{0.05, 0.05, 0.05, 1.0};

    auto wgsl_desc         = shader_module_wgsl_descriptor(shader_code);
    auto shader_descriptor = shader_module_descriptor(wgsl_desc);
    auto shader_module     = dev.create_shader_module(shader_descriptor);

    auto blend_state = WGPUBlendState{
        .color = blend_component(
            blend_op::add,
            blend_factor::src_alpha,
            blend_factor::one_minus_src_alpha
        ),
        .alpha = blend_component(blend_op::add, blend_factor::zero, blend_factor::one),
    };

    auto color_state = color_target_state(format, blend_state, color_write_mask::all);

    auto vertex_layout = vertex_buffer_layout(
        24,
        vertex_step_mode::vertex,
        {
            vertex_attribute(vertex_format::float32x3, 0, 0),
            vertex_attribute(vertex_format::float32x3, 12, 1),
        }
    );

    auto vertex_state =
        echidna::webgpu::vertex_state(shader_module, "vs_main", {}, {vertex_layout});

    // auto fragment_state = WGPUFragmentState{
    //     .nextInChain   = nullptr,
    //     .module        = shader_module,
    //     .entryPoint    = "fs_main",
    //     .constantCount = 0,
    //     .constants     = nullptr,
    //     .targetCount   = 1,
    //     .targets       = &color_state,
    // };

    auto fragment_state =
        echidna::webgpu::fragment_state(shader_module, "fs_main", {}, {color_state});

    auto primitive_state = echidna::webgpu::primitive_state(
        primitive_topology::triangle_list,
        index_format::undefined,
        front_face::ccw,
        cull_mode::none
    );

    auto multi_sample_state = multisample_state(1, ~0U, false);

    auto depth_state = depth_stencil_state(
        texture_format::depth32_float,
        true,
        compare_function::less_equal,
        stencil_face_state(
            compare_function::always,
            stencil_op::keep,
            stencil_op::keep,
            stencil_op::keep
        ),
        stencil_face_state(
            compare_function::always,
            stencil_op::keep,
            stencil_op::keep,
            stencil_op::keep
        ),
        0,
        0,
        0,
        0.0f,
        0.0f
    );

    auto depth_formats = std::vector<texture_format>();
    depth_formats.emplace_back(static_cast<texture_format>(depth_state.format));
    // auto depth_texture_desc = texture_descriptor(
    //     "depth tex",
    //     texture_usage::render_attachment,
    //     texture_dimension::dim2,
    //     {1920, 1080, 1},
    //     texture_format::depth32_float,
    //     1,
    //     1,
    //     depth_formats
    // );
    auto depth_texture_desc = texture_descriptor(
        "depth",
        texture_usage::render_attachment,
        texture_dimension::dim2,
        {1920, 1080, 1},
        texture_format::depth32_float,
        1,
        1,
        depth_formats
    );
    auto depth_texture = dev.create_texture(depth_texture_desc);

    auto depth_texture_view_desc = texture_view_descriptor(
        "depth",
        texture_format::depth32_float,
        texture_view_dimension::dim2,
        0,
        1,
        0,
        1,
        texture_aspect::all
    );
    auto depth_texture_view = depth_texture.create_texture_view(depth_texture_view_desc);

    auto depth_attachment = WGPURenderPassDepthStencilAttachment{
        .view              = depth_texture_view,
        .depthLoadOp       = WGPULoadOp_Clear,
        .depthStoreOp      = WGPUStoreOp_Store,
        .depthClearValue   = 1.0f,
        .depthReadOnly     = false,
        .stencilLoadOp     = WGPULoadOp_Clear,
        .stencilStoreOp    = WGPUStoreOp_Store,
        .stencilClearValue = 0,
        .stencilReadOnly   = true,
    };

    auto color_attach = render_pass_color_attachment(load_op::clear, store_op::store, clear_color);
    auto render_pass_desc = render_pass_descriptor(
        "renderpass",
        {color_attach},
        {depth_attachment},
        query_set(),
        render_pass_timestamp_writes()
    );

    auto pipeline_layout_descriptor = echidna::webgpu::pipeline_layout_descriptor("pld", {bgl});

    auto pipeline_layout = dev.create_pipeline_layout(pipeline_layout_descriptor);

    auto pipeline_desc = render_pipeline_descriptor(
        "pipeline",
        pipeline_layout,
        vertex_state,
        primitive_state,
        depth_state,
        multi_sample_state,
        fragment_state
    );

    auto pipeline = dev.create_render_pipeline(pipeline_desc);

    auto model_it = admat::mat4::identity();
    auto model    = admat::translation(0, 1, 0);
    auto view     = admat::look_at({0.0f, 0, 10}, {0, 0, 0}, {0, 1, 0});
    auto proj     = admat::perspective(0.785398f, 1920.0f / 1080.0f, 0.001f, 1000.0f);
    // auto proj = glm::perspective(0.785398f, 1920.0f / 1080.0f, 0.001f, 1000.0f);

    queue.write_buffer(mvp_buffer, 0 * sizeof(admat::mat4), &proj, sizeof(admat::mat4));
    queue.write_buffer(mvp_buffer, 1 * sizeof(admat::mat4), &view, sizeof(admat::mat4));
    queue.write_buffer(mvp_buffer, 2 * sizeof(admat::mat4), &model, sizeof(admat::mat4));
    queue.write_buffer(mvp_buffer, 3 * sizeof(admat::mat4), &model_it, sizeof(admat::mat4));

    auto cmds = std::vector<command_buffer>{};

    auto quit     = false;
    auto event    = SDL_Event{};
    auto now      = std::chrono::steady_clock::now();
    auto previous = now;
    float delta   = (previous - now).count();

    std::cout << "Before loop\n";

    while(!quit) {
        now   = std::chrono::steady_clock::now();
        delta = (now - previous).count() / 1'000'000'000.0f;
        // std::cout << std::format("Delta Time: {}\r", delta);

        previous = now;

        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
                }
                break;
            }
        }

        float x = std::sin(SDL_GetTicks64() / 1000.0f);
        float y = std::cos(SDL_GetTicks64() / 1000.0f);
        // float z        = std::cos(SDL_GetTicks64() / 1000.0f);
        float rotation = SDL_GetTicks64() / 2000.0f;
        model          = admat::translation(x * 3, y * 3, 0);
        // model          = model * admat::rotation({0, 1, 0}, rotation);
        // model_it       = admat::transpose(admat::inverse(model));
        queue.write_buffer(mvp_buffer, 2 * sizeof(admat::mat4), &model, sizeof(admat::mat4));
        queue.write_buffer(mvp_buffer, 3 * sizeof(admat::mat4), &model_it, sizeof(admat::mat4));

        auto tex            = surf.current_texture();
        const auto tex_view = tex->create_texture_view();
        // const auto depth_view = depth_texture.create_texture_view(depth_texture_view_desc);

        color_attach.view                          = tex_view;
        render_pass_desc.color_attachments[0].view = tex_view;
        // depth_attachment.view = depth_view;

        auto cmd_enc = dev.create_command_encoder("phong encoder");
        auto rp_enc  = cmd_enc.begin_render_pass(render_pass_desc);

        rp_enc.set_pipeline(pipeline);
        rp_enc.set_vertex_buffer(0, vertex_buffer, 0, vertex_buffer.size());
        rp_enc.set_index_buffer(index_buffer, index_format::uint32, 0, index_buffer.size());

        rp_enc.set_bind_group(0, bind_group, {});

        rp_enc.draw_indexed(indices.size(), 1, 0, 0, 0);

        rp_enc.end();
        cmds.emplace_back(cmd_enc.finish({}));
        queue.submit(cmds);
        surf.present();

        cmds.clear();
    }

    // Destroying the window before destructors are called causes an issue with wgpu
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    return 0;
}