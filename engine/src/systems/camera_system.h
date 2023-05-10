#pragma once

#include "renderer/camera.h"

typedef struct camera_system_config {
    // The maximum number of cameras that can be managed by the system
    u16 max_camera_count;
} camera_system_config;

#define DEFAULT_CAMERA_NAME "default"

b8 camera_system_initialize(u64* memory_requirement, void* state, void* config);
void camera_system_shutdown(void* state);

KAPI camera* camera_system_acquire(const char* name);
KAPI void camera_system_release(const char* name);

KAPI camera* camera_system_get_default(void);
