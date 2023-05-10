#pragma once

#include "renderer/renderer_types.inl"

typedef struct texture_system_config {
    u32 max_texture_count;
} texture_system_config;

#define DEFAULT_TEXTURE_NAME "default"
#define DEFAULT_DIFFUSE_TEXTURE_NAME "default_DIFF"
#define DEFAULT_SPECULAR_TEXTURE_NAME "default_SPEC"
#define DEFAULT_NORMAL_TEXTURE_NAME "default_NORM"

b8 texture_system_initialize(u64* memory_requirement, void* state, void* config);
void texture_system_shutdown(void* state);

KAPI texture* texture_system_acquire(const char* name, b8 auto_release);
KAPI texture* texture_system_acquire_cube(const char* name, b8 auto_release);
KAPI texture* texture_system_acquire_writeable(const char* name, u32 width, u32 height, u8 channel_count, b8 has_transparency);
KAPI void texture_system_release(const char* name);

KAPI void texture_system_wrap_internal(const char* name, u32 width, u32 height, u8 channel_count, b8 has_transparency, b8 is_writeable, b8 register_texture, void* internal_data, texture* out_texture);
KAPI b8 texture_system_set_internal(texture* t, void* internal_data);
KAPI b8 texture_system_resize(texture* t, u32 width, u32 height, b8 regenerate_internal_data);
KAPI b8 texture_system_write_data(texture* t, u32 offset, u32 size, void* data);

KAPI texture* texture_system_get_default_texture(void);
KAPI texture* texture_system_get_default_diffuse_texture(void);
KAPI texture* texture_system_get_default_specular_texture(void);
KAPI texture* texture_system_get_default_normal_texture(void);
