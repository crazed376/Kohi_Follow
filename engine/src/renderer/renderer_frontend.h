#pragma once

#include "renderer_types.h"

struct shader;
struct shader_uniform;
struct frame_data;
struct viewport;

typedef struct renderer_system_config {
	char* application_name;
	renderer_plugin plugin;
} renderer_system_config;

KAPI b8 renderer_system_initialize(u64* memory_requirement, void* state, void* config);
KAPI void renderer_system_shutdown(void* state);

KAPI void renderer_on_resized(u16 width, u16 height);

KAPI b8 renderer_frame_prepare(struct frame_data* p_frame_data);

KAPI b8 renderer_begin(struct frame_data* p_frame_data);

KAPI b8 renderer_end(struct frame_data* p_frame_data);

KAPI b8 renderer_present(struct frame_data* p_frame_data);

KAPI void renderer_viewport_set(vec4 rect);

KAPI void renderer_viewport_reset(void);

KAPI void renderer_scissor_set(vec4 rect);

KAPI void renderer_scissor_reset(void);

KAPI void renderer_winding_set(renderer_winding winding);
KAPI void renderer_texture_create(const u8* pixels, struct texture* texture);
KAPI void renderer_texture_destroy(struct texture* texture);

KAPI void renderer_texture_create_writeable(texture* t);
KAPI void renderer_texture_resize(texture* t, u32 new_width, u32 new_height);
KAPI void renderer_texture_write_data(texture* t, u32 offset, u32 size, const u8* pixels);

KAPI void renderer_texture_read_data(texture* t, u32 offset, u32 size, void** out_memory);

KAPI void renderer_texture_read_pixel(texture* t, u32 x, u32 y, u8** out_rgba);
KAPI b8 renderer_geometry_create(geometry* geometry, u32 vertex_size, u32 vertex_count, const void* vertices, u32 index_size, u32 index_count, const void* indices);

KAPI b8 renderer_geometry_upload(geometry* geometry);
KAPI void renderer_geometry_vertex_update(geometry* g, u32 offset, u32 vertex_count, void* vertices);
KAPI void renderer_geometry_destroy(geometry* geometry);

KAPI void renderer_geometry_draw(geometry_render_data* data);

KAPI b8 renderer_renderpass_begin(renderpass* pass, render_target* target);
KAPI b8 renderer_renderpass_end(renderpass* pass);

KAPI b8 renderer_shader_create(struct shader* s, const shader_config* config, renderpass* pass, u8 stage_count, const char** stage_filenames, shader_stage* stages);
KAPI void renderer_shader_destroy(struct shader* s);

KAPI b8 renderer_shader_initialize(struct shader* s);

KAPI b8 renderer_shader_use(struct shader* s);

KAPI b8 renderer_shader_bind_globals(struct shader* s);
KAPI b8 renderer_shader_bind_instance(struct shader* s, u32 instance_id);

KAPI b8 renderer_shader_apply_globals(struct shader* s, b8 needs_update);
KAPI b8 renderer_shader_apply_instance(struct shader* s, b8 needs_update);

KAPI b8 renderer_shader_instance_resources_acquire(struct shader* s, u32 texture_map_count, texture_map** maps, u32* out_instance_id);
KAPI b8 renderer_shader_instance_resources_release(struct shader* s, u32 instance_id);

KAPI b8 renderer_shader_uniform_set(struct shader* s, struct shader_uniform* uniform, const void* value);

KAPI b8 renderer_texture_map_resources_acquire(struct texture_map* map);
KAPI void renderer_texture_map_resources_release(struct texture_map* map);

KAPI void renderer_render_target_create(u8 attachment_count, render_target_attachment* attachments, renderpass* pass, u32 width, u32 height, render_target* out_target);
KAPI void renderer_render_target_destroy(render_target* target, b8 free_internal_memory);

KAPI texture* renderer_window_attachment_get(u8 index);

KAPI texture* renderer_depth_attachment_get(u8 index);

KAPI u8 renderer_window_attachment_index_get(void);

KAPI u8 renderer_window_attachment_count_get(void);
KAPI b8 renderer_renderpass_create(const renderpass_config* config, renderpass* out_renderpass);
KAPI void renderer_renderpass_destroy(renderpass* pass);

KAPI b8 renderer_is_multithreaded(void);

KAPI b8 renderer_flag_enabled_get(renderer_config_flags flag);
KAPI void renderer_flag_enabled_set(renderer_config_flags flag, b8 enabled);
KAPI b8 renderer_renderbuffer_create(const char* name, renderbuffer_type type, u64 total_size, b8 use_freelist, renderbuffer* out_buffer);
KAPI void renderer_renderbuffer_destroy(renderbuffer* buffer);
KAPI b8 renderer_renderbuffer_bind(renderbuffer* buffer, u64 offset);
KAPI b8 renderer_renderbuffer_unbind(renderbuffer* buffer);

KAPI void* renderer_renderbuffer_map_memory(renderbuffer* buffer, u64 offset, u64 size);
KAPI void renderer_renderbuffer_unmap_memory(renderbuffer* buffer, u64 offset, u64 size);

KAPI b8 renderer_renderbuffer_flush(renderbuffer* buffer, u64 offset, u64 size);
KAPI b8 renderer_renderbuffer_read(renderbuffer* buffer, u64 offset, u64 size, void** out_memory);
KAPI b8 renderer_renderbuffer_resize(renderbuffer* buffer, u64 new_total_size);
KAPI b8 renderer_renderbuffer_allocate(renderbuffer* buffer, u64 size, u64* out_offset);
KAPI b8 renderer_renderbuffer_free(renderbuffer* buffer, u64 size, u64 offset);
KAPI b8 renderer_renderbuffer_load_range(renderbuffer* buffer, u64 offset, u64 size, const void* data);
KAPI b8 renderer_renderbuffer_copy_range(renderbuffer* source, u64 source_offset, renderbuffer* dest, u64 dest_offset, u64 size);
KAPI b8 renderer_renderbuffer_draw(renderbuffer* buffer, u64 offset, u32 element_count, b8 bind_only);

KAPI struct viewport* renderer_active_viewport_get(void);

KAPI void renderer_active_viewport_set(struct viewport* v);
