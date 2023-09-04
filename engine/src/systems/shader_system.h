#pragma once

#include "containers/hashtable.h"
#include "defines.h"
#include "renderer/renderer_types.h"

typedef struct shader_system_config {
    u16 max_shader_count;
    u8 max_uniform_count;
    u8 max_global_textures;
    u8 max_instance_textures;
} shader_system_config;

typedef enum shader_state {
    SHADER_STATE_NOT_CREATED,
    SHADER_STATE_UNINITIALIZED,
    SHADER_STATE_INITIALIZED,
} shader_state;

typedef struct shader_uniform {
    u64 offset;
    u16 location;
    u16 index;
    u16 size;
    u8 set_index;
    shader_scope scope;
    shader_uniform_type type;
} shader_uniform;

// Represents a single shader vertex attribute
typedef struct shader_attribute {
    char* name;
    shader_attribute_type type;
    u32 size;
} shader_attribute;

typedef enum shader_flags {
	SHADER_FLAG_NONE = 0x0,
	SHADER_FLAG_DEPTH_TEST = 0x1,
	SHADER_FLAG_DEPTH_WRITE = 0x2,
	SHADER_FLAG_WIREFRAME = 0x4
} shader_flags;

typedef u32 shader_flag_bits;
// Represents a shader on the frontend
typedef struct shader {
    u32 id;

    char* name;

	shader_flag_bits flags;
	
	u32 topology_types;
    // The amount of bytes that are required for UBO alignment
    // This is used along with the UBO size to determine the ultimate
    // stride, which is how much the UBOs are spaced out in the buffer.
    // For example, a required alignment of 256 means that the stride
    // must be a multiple of 256 (true for some nVidia cards).
    u64 required_ubo_alignment;

    u64 global_ubo_size;
    u64 global_ubo_stride;
    u64 global_ubo_offset;

    u64 ubo_size;

    u64 ubo_stride;

    u64 push_constant_size;
    u64 push_constant_stride;

    texture_map** global_texture_maps;

    u8 instance_texture_count;

    shader_scope bound_scope;

    u32 bound_instance_id;
    u32 bound_ubo_offset;

    void* hashtable_block;
    hashtable uniform_lookup;

    shader_uniform* uniforms;

    shader_attribute* attributes;

    shader_state state;

    u8 push_constant_range_count;
    range push_constant_ranges[32];
    u16 attribute_stride;

    u64 render_frame_number;
    
    u8 draw_index;

    void* internal_data;
} shader;

b8 shader_system_initialize(u64* memory_requirement, void* memory, void* config);

void shader_system_shutdown(void* state);

KAPI b8 shader_system_create(renderpass* pass, const shader_config* config);

KAPI u32 shader_system_get_id(const char* shader_name);

KAPI shader* shader_system_get_by_id(u32 shader_id);

KAPI shader* shader_system_get(const char* shader_name);

KAPI b8 shader_system_use(const char* shader_name);

KAPI b8 shader_system_use_by_id(u32 shader_id);

KAPI u16 shader_system_uniform_index(shader* s, const char* uniform_name);

KAPI b8 shader_system_uniform_set(const char* uniform_name, const void* value);

KAPI b8 shader_system_sampler_set(const char* sampler_name, const texture* t);

KAPI b8 shader_system_uniform_set_by_index(u16 index, const void* value);

KAPI b8 shader_system_sampler_set_by_index(u16 index, const struct texture* t);

KAPI b8 shader_system_apply_global(b8 needs_update);

KAPI b8 shader_system_apply_instance(b8 needs_update);

KAPI b8 shader_system_bind_instance(u32 instance_id);
