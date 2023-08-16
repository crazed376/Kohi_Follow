#pragma once

#include "defines.h"
#include "renderer/renderer_types.inl"
#include "systems/font_system.h"

struct application;
struct frame_data;

// Application configurations
typedef struct application_config {
    // Window starting position x axis, if applicable
    i16 start_pos_x;

    // Window starting position y axis, if applicable
    i16 start_pos_y;

    // Window starting width, if applicable
    i16 start_width;

    // Window starting height, if applicable
    i16 start_height;

    // The application name used in windowing, if applicable
    char* name;

	// Configuration for the font system
	font_system_config font_config;
	
	// A darray of render view configurations
	render_view* views;

    renderer_plugin renderer_plugin;

	u64 frame_allocator_size;
	u64 app_frame_data_size;
} application_config;

KAPI b8 engine_create(struct application* game_inst);
KAPI b8 engine_run(struct application* game_inst);
void engine_on_event_system_initialized(void);

KAPI const struct frame_data* engine_frame_data_get(struct application* game_inst);
