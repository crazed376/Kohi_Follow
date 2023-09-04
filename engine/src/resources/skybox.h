#pragma once

#include "math/math_types.h"
#include "renderer/renderer_types.h"
#include "resources/resource_types.h"
#include "systems/geometry_system.h"

typedef struct skybox_config {
	// The name of the cubemap to be used for the skybox
	const char* cubemap_name;
	geometry_config g_config;
} skybox_config;

typedef struct skybox {
	skybox_config config;
    texture_map cubemap;
    geometry* g;
    u32 instance_id;
    // Synced to the renderer's current frame number when the material has been applied that frame
    u64 render_frame_number;
    
    u8 draw_index;
} skybox;

// Attempts to create a skybox using the specified parameters
KAPI b8 skybox_create(skybox_config config, skybox* out_skybox);

KAPI b8 skybox_initialize(skybox* sb);

KAPI b8 skybox_load(skybox* sb);

KAPI b8 skybox_unload(skybox* sb);
// Destroys the provided skybox
KAPI void skybox_destroy(skybox* sb);
