#pragma once

#include "defines.h"

typedef union vec2_u {
    // An arry of x, y
    f32 elements[2];
    struct {
        union {
            // The first element
            f32 x, r, s, u;
        };
        union {
            // The second element
            f32 y, g, t, v;
        };
    };
} vec2;

typedef union vec3_u {
    // AN array of x, y, z
    f32 elements[3];
    struct {
        union {
            // The first element
            f32 x, r, s, u;
        };
        union {
            // The secont element
            f32 y, g, t, v;
        };
        union {
            // The third element
            f32 z, b, p, w;
        };
    };
} vec3;

typedef union vec4_u {
    // An array of x, y, z, w
    f32 elements[4];
    union {
        struct {
            union {
                // THe first element
                f32 x, r, s;
            };
            union {
                // THe second element
                f32 y, g, t;
            };
            union {
                // THe third element
                f32 z, b, p;
            };
            union {
                // THe fourth element
                f32 w, a, q;
            };
        };
    };
} vec4;

typedef vec4 quat;

typedef union mat4_u {
    f32 data[16];
} mat4;

typedef struct extents_2d {
    vec2 min;
    vec2 max;
} extents_2d;

typedef struct extents_3d {
    vec3 min;
    vec3 max;
} extents_3d;


typedef struct vertex_3d {
    vec3 position;
    vec3 normal;
    vec2 texcoord;
    vec4 color;
    vec3 tangent;
} vertex_3d;

typedef struct vertex_2d {
    vec2 position;
    vec2 texcoord;
} vertex_2d;

// Represents the transform of an object in the world.
// Transforms can have a parent whose own transform is then
// taken into account. NOTE: The properties of this should not
// be edited directly, but done via the functions in transform.h
// to ensure proper matrix generation.
typedef struct transform {
    vec3 position;
    quat rotation;
    vec3 scale;
    
    // Indicates if the position, rotation or scale have changed,
    // indication that the local matrix needs to be recalculated.
    b8 is_dirty;
    // The local transformation matrix, updated whenever the
    // position, rotation or scale have changed
    mat4 local;

    struct transform* parent;
} transform;

typedef struct plane_3d {
    vec3 normal;
    f32 distance;
} plane_3d;

typedef struct frustum {
    // Top, bottom, right, left, far, near
    plane_3d sides[6];
} frustum;

