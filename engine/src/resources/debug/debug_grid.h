#include "defines.h"
#include "math/math_types.h"
#include "resources/resource_types.h"

typedef enum debug_grid_orientation {
	// A grid that lies "flat" in the world along the ground plane (y-plane)
	// This is the default configuration
	DEBUG_GRID_ORIENTATION_XZ = 0,
	// A grid that lies on the z-plane (facing the screen by default, orthogonal to the ground plane)
	DEBUG_GRID_ORIENTATION_XY = 1,
	// A grid that lies on the x-plane (orthagonal to the default screen plane and the ground plane)
	DEBUG_GRID_ORIENTATION_YZ = 2
} debug_grid_orientation;

typedef struct debug_grid_config {
	char* name;
	debug_grid_orientation orientation;
	// The space count in the first dimension of the orientation from both directions outward from origin
	u32 tile_count_dim_0;
	// The space count in the second dimension of the orientation from both directions outward from origin
	u32 tile_count_dim_1;
	// How large each tile is on both axes, relative to one unit (default = 1.0)
	f32 tile_scale;
	
	// Indicates if a third axis is to be rendered
	b8 use_third_axis;
	
	// The total number of vertices
	u32 vertex_length;
	// Generated vertex data
	color_vertex_3d* vertices;
} debug_grid_config;

typedef struct debug_grid {
	u32 unique_id;
	char* name;
	debug_grid_orientation orientation;
	// The space count in the first dimension of the orientation from both directions outward from origin
	u32 tile_count_dim_0;
	// The space count in the second dimension of the orientation from both directions outward from origin
	u32 tile_count_dim_1;
	// How large each tile is on both axes, relative to one unit (default = 1.0)
	f32 tile_scale;
	
	// Indicates if a third axis is to be rendered
	b8 use_third_axis;
	
	extents_3d extents;
	vec3 origin;
	
	u32 vertex_count;
	color_vertex_3d* vertices;
	
	geometry geo;
} debug_grid;

KAPI b8 debug_grid_create(const debug_grid_config* config, debug_grid* out_grid);
KAPI void debug_grid_destroy(debug_grid* grid);

KAPI b8 debug_grid_initialize(debug_grid* grid);
KAPI b8 debug_grid_load(debug_grid* grid);
KAPI b8 debug_grid_unload(debug_grid* grid);

KAPI b8 debug_grid_update(debug_grid* grid);
