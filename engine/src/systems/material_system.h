#pragma once

#include "defines.h"

#include "resources/resource_types.h"

#define DEFAULT_MATERIAL_NAME "default"

#define DEFAULT_UI_MATERIAL_NAME "default_ui"

#define DEFAULT_TERRAIN_MATERIAL_NAME "default_terrain"

typedef struct material_system_config {
    u32 max_material_count;
} material_system_config;

b8 material_system_initialize(u64* memory_requirement, void* state, void* config);
void material_system_shutdown(void* state);

KAPI material* material_system_acquire(const char* name);

KAPI material* material_system_acquire_terrain_material(const char* material_name, u32 material_count, const char** material_names, b8 auto_release);
KAPI material* material_system_acquire_from_config(material_config* config);
KAPI void material_system_release(const char* name);

KAPI material* material_system_get_default(void);

KAPI material* material_system_get_default_ui(void);

KAPI material* material_system_get_default_terrain(void);
KAPI b8 material_system_apply_global(u32 shader_id, u64 renderer_frame_number, const mat4* projection, const mat4* view, const vec4* ambient_color, const vec3* view_position, u32 render_mode);
KAPI b8 material_system_apply_instance(material* m, b8 needs_update);
KAPI b8 material_system_apply_local(material* m, const mat4* model);
KAPI void material_system_dump(void);
