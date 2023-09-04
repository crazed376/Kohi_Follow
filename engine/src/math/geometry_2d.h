#ifndef _KOHI_MATH_GEOMETRY_2D_H_
#define _KOHI_MATH_GEOMETRY_2D_H_

#include "defines.h"
#include "kmath.h"
#include "math_types.h"

typedef struct circle_2d {
	vec2 center;
	f32 radius;
} circle_2d;

// Indicates if the provided point is within the given rectangle
KINLINE b8 point_in_rect_2d(vec2 point, rect_2d rect) {
	return point.x >= rect.x && point.x <= rect.x + rect.width && point.y >= rect.y && point.y <= rect.y + rect.height;
}

// Indicates if the provided point is within the given circle
KINLINE b8 point_in_circle_2d(vec2 point, circle_2d circle) {
	f32 r_squared = circle.radius * circle.radius;
	return vec2_distance_squared(point, circle.center) <= r_squared;
}

#endif
