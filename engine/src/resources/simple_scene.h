#pragma once

#include "defines.h"
#include "math/math_types.h"

struct frame_data;
struct render_packet;
struct directional_light;
struct point_light;
struct mesh;
struct skybox;
struct geometry_config;
struct camera;
struct simple_scene_config;

typedef enum simple_scene_state {
    SIMPLE_SCENE_STATE_UNINITIALIZED,
    SIMPLE_SCENE_STATE_INITIALIZED,
    SIMPLE_SCENE_STATE_LOADING,
    SIMPLE_SCENE_STATE_LOADED,
    SIMPLE_SCENE_STATE_UNLOADING,
    SIMPLE_SCENE_STATE_UNLOADED
} simple_scene_state;

typedef struct pending_mesh {
	struct mesh* m;
	
	const char* mesh_resource_name;
	
	u32 geometry_config_count;
	struct geometry_config** g_configs;
} pending_mesh;
typedef struct simple_scene {
    u32 id;
    simple_scene_state state;
    b8 enabled;

	char* name;
	char* description;
	
	transform scene_transform;
	
	// Singular pointer to a directional light
	struct directional_light* dir_light;
	
	// darray of point lights
	struct point_light* point_lights;
	
	// darray of meshes
	struct mesh* meshes;
	
	// darray of meshes to be loaded
	pending_mesh* pending_meshes;
	
	// Singular pointer to a skybox
	struct skybox* sb;
	
	// A pointer to the scene configuration, if provided
	struct simple_scene_config* config;
} simple_scene;

KAPI b8 simple_scene_create(void* config, simple_scene* out_scene);

KAPI b8 simple_scene_initialize(simple_scene* scene);

KAPI b8 simple_scene_load(simple_scene* scene);
KAPI b8 simple_scene_unload(simple_scene* scene, b8 immediate);

KAPI b8 simple_scene_update(simple_scene* scene, const struct frame_data* p_frame_data);

KAPI b8 simple_scene_populate_render_packet(simple_scene* scene, struct camera* current_camera, f32 aspect, struct frame_data* p_frame_data, struct render_packet* packet);


KAPI b8 simple_scene_directional_light_add(simple_scene* scene, const char* name, struct directional_light* light);

KAPI b8 simple_scene_point_light_add(simple_scene* scene, const char* name, struct point_light* light);

KAPI b8 simple_scene_mesh_add(simple_scene* scene, const char* name, struct mesh* m);

KAPI b8 simple_scene_skybox_add(simple_scene* scene, const char* name, struct skybox* sb);

KAPI b8 simple_scene_directional_light_remove(simple_scene* scene, const char* name);

KAPI b8 simple_scene_point_light_remove(simple_scene* scene, const char* name);

KAPI b8 simple_scene_mesh_remove(simple_scene* scene, const char* name);

KAPI b8 simple_scene_skybox_remove(simple_scene* scene, const char* name);

KAPI struct directional_light* simple_scene_directional_light_get(simple_scene* scene, const char* name);

KAPI struct point_light* simple_scene_point_light_get(simple_scene* scene, const char* name);

KAPI struct mesh* simple_scene_mesh_get(simple_scene* scene, const char* name);

KAPI struct skybox* simple_scene_skybox_get(simple_scene* scene, const char* name);
