#pragma once

#include "defines.h"

#include "math/math_types.h"

typedef struct directional_light_data {
	vec4 color;
	vec4 direction;
} directional_light_data;
typedef struct directional_light {
	char* name;
    directional_light_data data;
	void* debug_data;
} directional_light;

typedef struct point_light_data {
    vec4 color;
    vec4 position; 
    // Usually 1, make sure denominator never gets smaller than 1
    f32 constant_f;
    // Reduces light intensity linearly
    f32 linear;
    // Makes the light fall off slower at longer distances
    f32 quadratic;
    f32 padding;
} point_light_data;

typedef struct point_light {
	char* name;
	point_light_data data;
	void* debug_data;
} point_light;

b8 light_system_initialize(u64* memory_requirement, void* memory, void* config);
void light_system_shutdown(void* state);

KAPI b8 light_system_directional_add(directional_light* light);
KAPI b8 light_system_point_add(point_light* light);

KAPI b8 light_system_directional_remove(directional_light* light);
KAPI b8 light_system_point_remove(point_light* light);

KAPI directional_light* light_system_directional_light_get(void);

KAPI u32 light_system_point_light_count(void);
KAPI b8 light_system_point_lights_get(point_light* p_lights);
