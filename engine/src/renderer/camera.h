#pragma once

#include "math/math_types.h"

// Represents a camera that can be used for a variety of things, especially
// rendering. Ideally, these are created and managed by the camera system
typedef struct camera {
    vec3 position;
    vec3 euler_rotation;
    b8 is_dirty;

    mat4 view_matrix;
} camera;

KAPI camera camera_create(void);
KAPI void camera_reset(camera* c);

KAPI vec3 camera_position_get(const camera* c);
KAPI void camera_position_set(camera* c, vec3 position);

KAPI vec3 camera_rotation_euler_get(const camera* c);
KAPI void camera_rotation_euler_set(camera* c, vec3 rotation);

KAPI mat4 camera_view_get(camera* c);

KAPI vec3 camera_forward(camera* c);
KAPI vec3 camera_backward(camera* c);
KAPI vec3 camera_left(camera* c);
KAPI vec3 camera_right(camera* c);

KAPI vec3 camera_up(camera* c);
KAPI void camera_move_forward(camera* c, f32 amount);
KAPI void camera_move_backward(camera* c, f32 amount);
KAPI void camera_move_left(camera* c, f32 amount);
KAPI void camera_move_right(camera* c, f32 amount);
KAPI void camera_move_up(camera* c, f32 amount);
KAPI void camera_move_down(camera* c, f32 amount);

KAPI void camera_yaw(camera* c, f32 amount);
KAPI void camera_pitch(camera* c, f32 amount);
