#include "math_types.h"

KAPI transform transform_create(void);

KAPI transform transform_from_position(vec3 position);
KAPI transform transform_from_rotation(quat rotation);
KAPI transform transform_from_position_rotation(vec3 position, quat rotation);
KAPI transform transform_from_position_rotation_scale(vec3 position, quat rotation, vec3 scale);

KAPI transform* transform_parent_get(transform* t);
KAPI void transform_parent_set(transform* t, transform* parent);

KAPI vec3 transform_position_get(const transform* t);
KAPI void transform_position_set(transform* t, vec3 position);
KAPI void transform_translate(transform* t, vec3 translation);

KAPI quat transform_rotation_get(const transform* t);
KAPI void transform_rotation_set(transform* t, quat rotation);
KAPI void transform_rotate(transform* t, quat rotation);

KAPI vec3 transform_scale_get(const transform* t);
KAPI void transform_scale_set(transform* t, vec3 scale);
KAPI void transform_scale(transform* t, vec3 scale);

KAPI void transform_position_rotation_set(transform* t, vec3 position, quat rotation);
KAPI void transform_position_rotation_scale_set(transform* t, vec3 position, quat rotation, vec3 scale);

KAPI void transform_translate_rotate(transform* t, vec3 translation, quat rotation);

KAPI mat4 transform_local_get(transform* t);
KAPI mat4 transform_world_get(transform* t);
