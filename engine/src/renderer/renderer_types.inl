#pragma once

#include "containers/freelist.h"
#include "defines.h"
#include "math/math_types.h"
#include "resources/resource_types.h"

struct shader;
struct shader_uniform;
struct frame_data;
struct terrain;

typedef struct geometry_render_data {
    mat4 model;
    geometry* geometry;
	u32 unique_id;
} geometry_render_data;

typedef enum renderer_debug_view_mode {
    RENDERER_VIEW_MODE_DEFAULT = 0,
    RENDERER_VIEW_MODE_LIGHTING = 1,
    RENDERER_VIEW_MODE_NORMALS = 2
} renderer_debug_view_mode;

typedef enum render_target_attachment_type {
	RENDER_TARGET_ATTACHMENT_TYPE_COLOR = 0x1,
	RENDER_TARGET_ATTACHMENT_TYPE_DEPTH = 0x2,
	RENDER_TARGET_ATTACHMENT_TYPE_STENCIL = 0x4
} render_target_attachment_type;

typedef enum render_target_attachment_source {
    RENDER_TARGET_ATTACHMENT_SOURCE_DEFAULT = 0x1,
    RENDER_TARGET_ATTACHMENT_SOURCE_VIEW = 0x2
} render_target_attachment_source;

typedef enum render_target_attachment_load_operation {
    RENDER_TARGET_ATTACHMENT_LOAD_OPERATION_DONT_CARE = 0x0,
    RENDER_TARGET_ATTACHMENT_LOAD_OPERATION_LOAD = 0x1
} render_target_attachment_load_operation;

typedef enum render_target_attachment_store_operation {
    RENDER_TARGET_ATTACHMENT_STORE_OPERATION_DONT_CARE = 0x0,
    RENDER_TARGET_ATTACHMENT_STORE_OPERATION_STORE = 0x1
} render_target_attachment_store_operation;

typedef struct render_target_attachment_config {
    render_target_attachment_type type;
    render_target_attachment_source source;
    render_target_attachment_load_operation load_operation;
    render_target_attachment_store_operation store_operation;
    b8 present_after;
} render_target_attachment_config;

typedef struct render_target_config {
    u8 attachment_count;
    render_target_attachment_config* attachments;
} render_target_config;

typedef struct render_target_attachment {
    render_target_attachment_type type;
    render_target_attachment_source source;
    render_target_attachment_load_operation load_operation;
    render_target_attachment_store_operation store_operation;
    b8 present_after;
    struct texture* texture;
} render_target_attachment;

typedef struct render_target {
    u8 attachment_count;
    struct render_target_attachment* attachments;
    void* internal_framebuffer;
} render_target;

typedef enum renderpass_clear_flag {
    RENDERPASS_CLEAR_NONE_FLAG = 0x0,
    RENDERPASS_CLEAR_COLOR_BUFFER_FLAG = 0x1,
    RENDERPASS_CLEAR_DEPTH_BUFFER_FLAG = 0x2,
    RENDERPASS_CLEAR_STENCIL_BUFFER_FLAG = 0x4
} renderpass_clear_flag;

typedef struct renderpass_config {
    const char* name;
    f32 depth;
    u32 stencil;
    vec4 render_area;
    vec4 clear_color;

    u8 clear_flags;
	u8 render_target_count;
	render_target_config target;
} renderpass_config;

typedef struct renderpass {
    u16 id;

	char* name;
	
    vec4 render_area;
    vec4 clear_color;

    u8 clear_flags;
    u8 render_target_count;
    render_target* targets;

    void* internal_data;
} renderpass;

typedef enum renderbuffer_type {
    RENDERBUFFER_TYPE_UNKNOWN,
    RENDERBUFFER_TYPE_VERTEX,
    RENDERBUFFER_TYPE_INDEX,
    RENDERBUFFER_TYPE_UNIFORM,
    RENDERBUFFER_TYPE_STAGING,
    RENDERBUFFER_TYPE_READ,
    RENDERBUFFER_TYPE_STORAGE
} renderbuffer_type;

typedef struct renderbuffer {
	char* name;
    renderbuffer_type type;
    u64 total_size;
    u64 freelist_memory_requirement;
    freelist buffer_freelist;
    void* freelist_block;
    void* internal_data;
} renderbuffer;

typedef enum renderer_config_flag_bits {
	RENDERER_CONFIG_FLAG_VSYNC_ENABLED_BIT = 0x1,
	RENDERER_CONFIG_FLAG_POWER_SAVING_BIT = 0x2,
} renderer_config_flag_bits;

typedef u32 renderer_config_flags;

typedef struct renderer_backend_config {
    const char* application_name;
	renderer_config_flags flags;
} renderer_backend_config;

typedef struct renderer_plugin {
    u64 frame_number;
    u64 internal_context_size;
    void* internal_context;

    b8 (*initialize)(struct renderer_plugin* plugin, const renderer_backend_config* config, u8* out_window_render_target_count);

    void (*shutdown)(struct renderer_plugin* plugin);

    void (*resized)(struct renderer_plugin* plugin, u16 width, u16 height);

    b8 (*frame_begin)(struct renderer_plugin* plugin, const struct frame_data* p_frame_data);
    b8 (*frame_end)(struct renderer_plugin* plugin, const struct frame_data* p_frame_data);

	void (*viewport_set)(struct renderer_plugin* plugin, vec4 rect);
	
	void (*viewport_reset)(struct renderer_plugin* plugin);
	
	void (*scissor_set)(struct renderer_plugin* plugin, vec4 rect);
	
	void (*scissor_reset)(struct renderer_plugin* plugin);
    b8 (*renderpass_begin)(struct renderer_plugin* plugin, renderpass* pass, render_target* target);
    b8 (*renderpass_end)(struct renderer_plugin* plugin, renderpass* pass);
	
    void (*texture_create)(struct renderer_plugin* plugin, const u8* pixels, struct texture* texture);
    
    void (*texture_destroy)(struct renderer_plugin* plugin, struct texture* texture);
    void (*texture_create_writeable)(struct renderer_plugin* plugin, texture* t);
    void (*texture_resize)(struct renderer_plugin* plugin, texture* t, u32 new_width, u32 new_height);
    void (*texture_write_data)(struct renderer_plugin* plugin, texture* t, u32 offset, u32 size, const u8* pixels);

	void (*texture_read_data)(struct renderer_plugin* plugin, texture* t, u32 offset, u32 size, void** out_memory);
	
	void (*texture_read_pixel)(struct renderer_plugin* plugin, texture* t, u32 x, u32 y, u8** out_rgba);
	
    b8 (*geometry_create)(struct renderer_plugin* plugin, geometry* g);
	b8 (*geometry_upload)(struct renderer_plugin* plugin, geometry* g, u32 vertex_offset, u32 vertex_size, u32 index_offset, u32 index_size);
	void (*geometry_vertex_update)(struct renderer_plugin* plugin, geometry* g, u32 offset, u32 vertex_count, void* vertices);

    void (*geometry_destroy)(struct renderer_plugin* plugin, geometry* g);

    void (*geometry_draw)(struct renderer_plugin* plugin, geometry_render_data* data);
    b8 (*shader_create)(struct renderer_plugin* plugin, struct shader* shader, const shader_config* config, renderpass* pass, u8 stage_count, const char** stage_filenames, shader_stage* stages);
    void (*shader_destroy)(struct renderer_plugin* plugin, struct shader* shader);
    b8 (*shader_initialize)(struct renderer_plugin* plugin, struct shader* shader);
    b8 (*shader_use)(struct renderer_plugin* plugin, struct shader* shader);
    b8 (*shader_bind_globals)(struct renderer_plugin* plugin, struct shader* s);
    b8 (*shader_bind_instance)(struct renderer_plugin* plugin, struct shader* s, u32 instance_id);
    b8 (*shader_apply_globals)(struct renderer_plugin* plugin, struct shader* s, b8 needs_update);
    b8 (*shader_apply_instance)(struct renderer_plugin* plugin, struct shader* s, b8 needs_update);
    b8 (*shader_instance_resources_acquire)(struct renderer_plugin* plugin, struct shader* s, u32 texture_map_count, texture_map** maps, u32* out_instance_id);
    b8 (*shader_instance_resources_release)(struct renderer_plugin* plugin, struct shader* s, u32 instance_id);
    b8 (*shader_uniform_set)(struct renderer_plugin* plugin, struct shader* frontend_shader, struct shader_uniform* uniform, const void* value);

    b8 (*texture_map_resources_acquire)(struct renderer_plugin* plugin, struct texture_map* map);
    void (*texture_map_resources_release)(struct renderer_plugin* plugin, struct texture_map* map);

    b8 (*render_target_create)(struct renderer_plugin* plugin, u8 attachment_count, render_target_attachment* attachments, renderpass* pass, u32 width, u32 height, render_target* out_target);
    void (*render_target_destroy)(struct renderer_plugin* plugin, render_target* target, b8 free_internal_memory);
    b8 (*renderpass_create)(struct renderer_plugin* plugin, const renderpass_config* config, renderpass* out_renderpass);
    void (*renderpass_destroy)(struct renderer_plugin* plugin, renderpass* pass);

    texture* (*window_attachment_get)(struct renderer_plugin* plugin, u8 index);
    texture* (*depth_attachment_get)(struct renderer_plugin* plugin, u8 index);
    u8 (*window_attachment_index_get)(struct renderer_plugin* plugin);

	u8 (*window_attachment_count_get)(struct renderer_plugin* plugin);
    b8 (*is_multithreaded)(struct renderer_plugin* plugin);

	b8 (*flag_enabled_get)(struct renderer_plugin* plugin, renderer_config_flags flag);

	void (*flag_enabled_set)(struct renderer_plugin* plugin, renderer_config_flags flag, b8 enabled);
    b8 (*renderbuffer_internal_create)(struct renderer_plugin* plugin, renderbuffer* buffer);
    void (*renderbuffer_internal_destroy)(struct renderer_plugin* plugin, renderbuffer* buffer);

    b8 (*renderbuffer_bind)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset);
    b8 (*renderbuffer_unbind)(struct renderer_plugin* plugin, renderbuffer* buffer);

    void* (*renderbuffer_map_memory)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset, u64 size);
    void (*renderbuffer_unmap_memory)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset, u64 size);

    b8 (*renderbuffer_flush)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset, u64 size);

    b8 (*renderbuffer_read)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset, u64 size, void** out_memory);
    b8 (*renderbuffer_resize)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 new_total_size);
    b8 (*renderbuffer_load_range)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset, u64 size, const void* data);
    b8 (*renderbuffer_copy_range)(struct renderer_plugin* plugin, renderbuffer* source, u64 source_offset, renderbuffer* dest, u64 dest_offset, u64 size);
    b8 (*renderbuffer_draw)(struct renderer_plugin* plugin, renderbuffer* buffer, u64 offset, u32 element_count, b8 bind_only);
} renderer_plugin;

struct render_view_packet;
struct linear_allocator;

typedef struct render_view {
    const char* name;
    u16 width;
    u16 height;

    u8 renderpass_count;
    renderpass* passes;

    const char* custom_shader_name;
    void* internal_data;

    b8 (*on_registered)(struct render_view* self);
    void (*on_destroy)(struct render_view* self);

    void (*on_resize)(struct render_view* self, u32 width, u32 height);

    b8 (*on_packet_build)(const struct render_view* self, struct linear_allocator* frame_allocator, void* data, struct render_view_packet* out_packet);

    void (*on_packet_destroy)(const struct render_view* self, struct render_view_packet* packet);

    b8 (*on_render)(const struct render_view* self, const struct render_view_packet* packet, u64 frame_number, u64 render_target_index, const struct frame_data* p_frame_data);
	b8 (*attachment_target_regenerate)(struct render_view* self, u32 pass_index, struct render_target_attachment* attachment);
} render_view;

typedef struct render_view_packet {
    const render_view* view;
    mat4 view_matrix;
    mat4 projection_matrix;
    vec3 view_position;
    vec4 ambient_color;
    u32 geometry_count;
    geometry_render_data* geometries;

	// The number of terrain geometries to be drawn
	u32 terrain_geometry_count;
	// The terrain geometries to be drawn
	geometry_render_data* terrain_geometries;
	
	u32 debug_geometry_count;
	geometry_render_data* debug_geometries;
	
	struct terrain** terrains;
    const char* custom_shader_name;
    void* extended_data;
} render_view_packet;

typedef struct mesh_packet_data {
    u32 mesh_count;
    mesh** meshes;
} mesh_packet_data;

struct ui_text;
typedef struct ui_packet_data {
    mesh_packet_data mesh_data;
    // TODO: temp
    u32 text_count;
    struct ui_text** texts;
} ui_packet_data;

typedef struct pick_packet_data {
    // Copy of frame data darray ptr
    geometry_render_data* world_mesh_data;
	// Copy of frame data darray ptr
	geometry_render_data* terrain_mesh_data;
    mesh_packet_data ui_mesh_data;
    u32 ui_geometry_count;
    // TODO: temp
    u32 text_count;
    struct ui_text** texts;
} pick_packet_data;

struct skybox;

typedef struct skybox_packet_data {
    struct skybox* sb;
} skybox_packet_data;

typedef struct render_packet {
    u16 view_count;
    render_view_packet* views;
} render_packet;
