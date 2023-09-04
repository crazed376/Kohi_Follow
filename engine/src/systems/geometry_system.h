#pragma once

#include "renderer/renderer_types.h"

typedef struct geometry_system_config {
    // Max number of geometries that can be loaded at once.
    // NOTE: Should be significantly greater than the number of static meshes because
    // there can and will be more than one of these per mesh.
    // Take other systems into account as well
    u32 max_geometry_count;
} geometry_system_config;

typedef struct geometry_config {
    u32 vertex_size;
    u32 vertex_count;
    void* vertices;
    u32 index_size;
    u32 index_count;
    void* indices;

    vec3 center;
    vec3 min_extents;
    vec3 max_extents;
    
    char name[GEOMETRY_NAME_MAX_LENGTH];
    char material_name[MATERIAL_NAME_MAX_LENGTH];
} geometry_config;

#define DEFAULT_GEOMETRY_NAME "default"

b8 geometry_system_initialize(u64* memory_requirement, void* state, void* config);
void geometry_system_shutdown(void* state);

KAPI geometry* geometry_system_acquire_by_id(u32 id);
KAPI geometry* geometry_system_acquire_from_config(geometry_config config, b8 auto_release);

KAPI void geometry_system_config_dispose(geometry_config* config);

KAPI void geometry_system_release(geometry* geometry);
KAPI geometry* geometry_system_get_default(void);
KAPI geometry* geometry_system_get_default_2d(void);

KAPI geometry_config geometry_system_generate_plane_config(f32 width, f32 height, u32 x_segment_count, u32 y_segment_count, f32 tile_x, f32 tile_y, const char* name, const char* material_name);
KAPI geometry_config geometry_system_generate_cube_config(f32 width, f32 height, f32 depth, f32 tile_x, f32 tile_y, const char* name, const char* material_name);
