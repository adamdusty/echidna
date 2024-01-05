#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <admat/mat.hpp>
#include <array>
#include <chrono>
#include <cstdint>
#include <echidna/echidna.hpp>
#include <format>
#include <iostream>
#include <vector>

using namespace echidna;

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
        out.frag_pos = (u_mvp.model * vec4f(in.position, 1.0)).xyz;
        // out.position = u_mvp.proj * u_mvp.view * u_mvp.model *  vec4f(in.position, 1.0);
        out.position = vec4f(in.position, 1.0) * u_mvp.model * u_mvp.view * u_mvp.proj;
        out.normal = (u_mvp.model_it * vec4f(in.normal, 0.0)).xyz;
        return out;
    }

    @fragment
    fn fs_main(in: vertex_output) -> @location(0) vec4f {
        var ambient_strength = 0.1;
        var ambient = ambient_strength * u_light.color;

        var norm = normalize(in.normal);
        var light_direction = normalize(u_light.pos - in.frag_pos);
        var diff = max(dot(norm, light_direction), 0.0);
        var diffuse = diff * u_light.color;

        var specular_strength = 0.5;
        var view_direction = normalize(u_light.view - in.frag_pos);
        var reflect_direction = reflect(-light_direction, norm);
        var spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32.0);
        var specular = specular_strength * spec * u_light.color;

        var combined = (ambient + diffuse + specular) * vec3f(1.0, 1.0, 1.0);
        // return vec4f(combined, 1.0);
        return vec4f(1.0, 1.0, 1.0, 1.0);
    }
)";

// clang-format off
static constexpr auto vertices = std::array<float, 144>{
    // Front
    -0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f,

    // Back
    +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

    // Top
    -0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 0.0f,

    // Bottom
    -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

    // Left
    -0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f,

    // Right
    +0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f,
    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
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
    auto* window =
        SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);

    auto inst_desc = instance_descriptor();
    auto inst      = instance{inst_desc};

    auto windows_surface_descriptor =
        surface_descriptor_from_windows_hwnd(info.info.win.hinstance, info.info.win.window);
    auto surf_desc = surface_descriptor(*reinterpret_cast<WGPUChainedStruct*>(&windows_surface_descriptor), "test");
    auto surf      = inst.create_surface(surf_desc);

    auto opt   = adapter_options(surf, backend_type::d3d12);
    auto adapt = inst.request_adapter(opt);

    auto dev_desc = device_descriptor();
    auto dev      = adapt.request_device(dev_desc);

    auto queue = dev.get_queue();

    auto surf_conf = surface_configuration(dev, surf.preferred_format(adapt), 1920, 1080);
    surf.configure(surf_conf);
    auto format = surf.preferred_format(adapt);

    // Initialize rendering buffers
    auto vertex_buffer =
        dev.create_buffer(buffer_usage::vertex | buffer_usage::copy_dst, sizeof(float) * vertices.size());
    auto index_buffer =
        dev.create_buffer(buffer_usage::index | buffer_usage::copy_dst, sizeof(std::uint32_t) * indices.size());
    auto mvp_buffer   = dev.create_buffer(buffer_usage::uniform | buffer_usage::copy_dst, sizeof(admat::mat4) * 4);
    auto light_buffer = dev.create_buffer(buffer_usage::uniform | buffer_usage::copy_dst, sizeof(admat::vec3) * 3);

    // Write static buffer data
    queue.write_buffer(vertex_buffer, 0, vertices.data(), sizeof(float) * vertices.size());
    queue.write_buffer(index_buffer, 0, indices.data(), sizeof(float) * indices.size());

    // Bind group layout
    auto mvp_bge_lay = WGPUBindGroupLayoutEntry{
        .nextInChain = nullptr,
        .binding     = 0,
        .visibility  = static_cast<WGPUShaderStageFlags>(shader_stage::vertex | shader_stage::fragment),
        .buffer =
            {
                .nextInChain      = nullptr,
                .type             = static_cast<WGPUBufferBindingType>(buffer_binding_type::uniform),
                .hasDynamicOffset = false,
                .minBindingSize   = mvp_buffer.size(),
            },
        .sampler =
            {
                .nextInChain = nullptr,
                .type        = static_cast<WGPUSamplerBindingType>(sampler_binding_type::undefined),
            },
        .texture =
            {
                .nextInChain   = nullptr,
                .sampleType    = static_cast<WGPUTextureSampleType>(texture_sample_type::undefined),
                .viewDimension = static_cast<WGPUTextureViewDimension>(textureview_dimension::undefined),
                .multisampled  = false,
            },
        .storageTexture =
            {
                .nextInChain   = nullptr,
                .access        = static_cast<WGPUStorageTextureAccess>(storage_texture_access::undefined),
                .format        = static_cast<WGPUTextureFormat>(texture_format::undefined),
                .viewDimension = static_cast<WGPUTextureViewDimension>(textureview_dimension::undefined),
            }
    };

    auto bind_group_layout_desc = WGPUBindGroupLayoutDescriptor{
        .nextInChain = nullptr,
        .label       = nullptr,
        .entryCount  = 1,
        .entries     = &mvp_bge_lay,
    };

    auto bind_group_layout = dev.create_bind_group_layout(bind_group_layout_desc);

    // Bind group entries
    auto mvp_bge = WGPUBindGroupEntry{
        .nextInChain = nullptr,
        .binding     = 0,
        .buffer      = mvp_buffer,
        .offset      = 0,
        .size        = mvp_buffer.size(),
        .sampler     = nullptr,
        .textureView = nullptr,
    };

    auto bind_group_entries = std::vector<WGPUBindGroupEntry>();
    bind_group_entries.emplace_back(mvp_bge);

    // Bind group
    auto bind_group = dev.create_bind_group(WGPUBindGroupDescriptor{
        .nextInChain = nullptr,
        .label       = nullptr,
        .layout      = bind_group_layout,
        .entryCount  = 1,
        .entries     = bind_group_entries.data(),
    });

    auto clear_color = WGPUColor{0.05, 0.05, 0.05, 1.0};

    auto shader_module = dev.shader_moudle_from_wgsl(shader_code);

    auto blend_state = WGPUBlendState{
        .color =
            {
                .operation = WGPUBlendOperation_Add,
                .srcFactor = WGPUBlendFactor_SrcAlpha,
                .dstFactor = WGPUBlendFactor_OneMinusSrcAlpha,
            },
        .alpha =
            {
                .operation = WGPUBlendOperation_Add,
                .srcFactor = WGPUBlendFactor_Zero,
                .dstFactor = WGPUBlendFactor_One,
            },
    };

    auto color_state = WGPUColorTargetState{
        .nextInChain = nullptr,
        .format      = static_cast<WGPUTextureFormat>(format),
        .blend       = &blend_state,
        .writeMask   = static_cast<WGPUColorWriteMaskFlags>(color_write_mask::all),
    };

    auto vertex_info = echidna::vertex_buffer_layout(vertex_format::float32x3, vertex_format::float32x3);

    auto vertex_state = WGPUVertexState{
        .nextInChain   = nullptr,
        .module        = shader_module,
        .entryPoint    = "vs_main",
        .constantCount = 0,
        .constants     = nullptr,
        .bufferCount   = 1,
        .buffers       = &vertex_info.layout,
    };

    auto fragment_state = WGPUFragmentState{
        .nextInChain   = nullptr,
        .module        = shader_module,
        .entryPoint    = "fs_main",
        .constantCount = 0,
        .constants     = nullptr,
        .targetCount   = 1,
        .targets       = &color_state,
    };

    auto primitive_state = echidna::primitive_state(
        primitive_topology::triangle_list,
        index_format::undefined,
        front_face::ccw,
        cull_mode::none
    );

    auto multi_sample_state = WGPUMultisampleState{
        .nextInChain            = nullptr,
        .count                  = 1,
        .mask                   = ~0U,
        .alphaToCoverageEnabled = false,
    };

    auto depth_state = WGPUDepthStencilState{
        .nextInChain       = nullptr,
        .format            = WGPUTextureFormat_Depth24Plus,
        .depthWriteEnabled = true,
        .depthCompare      = WGPUCompareFunction_Less,
        .stencilFront =
            {
                .compare     = WGPUCompareFunction_Always,
                .failOp      = WGPUStencilOperation_Keep,
                .depthFailOp = WGPUStencilOperation_Keep,
                .passOp      = WGPUStencilOperation_Keep,
            },
        .stencilBack =
            {
                .compare     = WGPUCompareFunction_Always,
                .failOp      = WGPUStencilOperation_Keep,
                .depthFailOp = WGPUStencilOperation_Keep,
                .passOp      = WGPUStencilOperation_Keep,
            },
        .stencilReadMask     = 0, // 0xFFFFFFFF,
        .stencilWriteMask    = 0, // 0XFFFFFFFF,
        .depthBias           = 0,
        .depthBiasSlopeScale = 0,
        .depthBiasClamp      = 0,
    };
    auto depth_formats = std::vector<texture_format>();
    depth_formats.emplace_back(static_cast<texture_format>(depth_state.format));
    auto depth_texture_desc = echidna::texture_descriptor(
        "depth tex",
        texture_usage::render_attachment,
        texture_dimension::dim2,
        {1920, 1080, 1},
        static_cast<texture_format>(depth_state.format),
        1,
        1,
        1,
        depth_formats
    );
    auto depth_texture = dev.create_texture(depth_texture_desc);

    auto depth_attachment = WGPURenderPassDepthStencilAttachment{
        .view              = depth_texture.create_texture_view(depth_texture.texture_view_descriptor()),
        .depthLoadOp       = WGPULoadOp_Clear,
        .depthStoreOp      = WGPUStoreOp_Store,
        .depthClearValue   = 1.0f,
        .depthReadOnly     = false,
        .stencilLoadOp     = WGPULoadOp_Clear,
        .stencilStoreOp    = WGPUStoreOp_Store,
        .stencilClearValue = 0,
        .stencilReadOnly   = true,
    };

    auto color_attach     = renderpass_color_attachment(load_op::clear, store_op::store, clear_color);
    auto render_pass_desc = WGPURenderPassDescriptor{
        .nextInChain            = nullptr,
        .label                  = "render pass",
        .colorAttachmentCount   = 1,
        .colorAttachments       = &color_attach,
        .depthStencilAttachment = &depth_attachment,
        .occlusionQuerySet      = nullptr,
        .timestampWrites        = nullptr,
    };

    auto pipeline_layout_descriptor = WGPUPipelineLayoutDescriptor{
        .nextInChain          = nullptr,
        .label                = nullptr,
        .bindGroupLayoutCount = 1,
        .bindGroupLayouts     = bind_group_layout.addr(),
    };

    auto pipeline_layout = dev.create_pipeline_layout(pipeline_layout_descriptor);

    auto pipeline_desc = WGPURenderPipelineDescriptor{
        .nextInChain  = nullptr,
        .label        = nullptr,
        .layout       = pipeline_layout,
        .vertex       = vertex_state,
        .primitive    = primitive_state,
        .depthStencil = &depth_state,
        .multisample  = multi_sample_state,
        .fragment     = &fragment_state,
    };
    auto pipeline = dev.create_render_pipeline(pipeline_desc);

    auto model_it = admat::mat4::identity();
    auto model    = admat::transpose(admat::translate(admat::mat4::identity(), {1.0f, 0, 0}));
    auto view     = admat::look_at({0, 0, -10}, {0, 0, 0}, {0, 1, 0});
    auto proj     = admat::perspective(0.785398f, 1920.0f / 1080.0f, 0.001f, 100.0f);

    queue.write_buffer(mvp_buffer, 0 * sizeof(admat::mat4), proj.get().data(), sizeof(admat::mat4));
    queue.write_buffer(mvp_buffer, 1 * sizeof(admat::mat4), view.get().data(), sizeof(admat::mat4));
    queue.write_buffer(mvp_buffer, 2 * sizeof(admat::mat4), model.get().data(), sizeof(admat::mat4));
    queue.write_buffer(mvp_buffer, 3 * sizeof(admat::mat4), model_it.get().data(), sizeof(admat::mat4));

    auto cmds = std::vector<command_buffer>{};

    auto quit     = false;
    auto event    = SDL_Event{};
    auto now      = std::chrono::steady_clock::now();
    auto previous = now;
    float delta   = (previous - now).count();
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

        model = admat::transpose(admat::translate(admat::mat4::identity(), {std::sin(SDL_GetTicks() / 1000.0f), 0, 0}));
        queue.write_buffer(mvp_buffer, 2 * sizeof(admat::mat4), model.get().data(), sizeof(admat::mat4));

        const auto& tex       = surf.current_texture();
        const auto tex_view   = tex.create_texture_view(tex.texture_view_descriptor());
        const auto depth_view = depth_texture.create_texture_view(depth_texture.texture_view_descriptor());

        color_attach.view     = tex_view;
        depth_attachment.view = depth_view;

        auto cmd_enc = dev.create_command_encoder("traingle encoder");
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

    SDL_DestroyWindow(window);
}