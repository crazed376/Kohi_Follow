#pragma once

#include "defines.h"

struct linear_allocator;

typedef struct frame_data {
	f32 delta_time;
	
	f64 total_time;
	
	u32 drawn_mesh_count;
	struct linear_allocator* frame_allocator;
	
	void* application_frame_data;
} frame_data;
