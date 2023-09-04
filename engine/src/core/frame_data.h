#pragma once

#include "defines.h"

struct linear_allocator;

typedef struct frame_allocator_int {
	void* (*allocate)(u64 size);
	void (*free)(u64 size);
	void (*free_all)(void);
} frame_allocator_int;
typedef struct frame_data {
	f32 delta_time;
	
	f64 total_time;
	
	u32 drawn_mesh_count;
	frame_allocator_int allocator;
	
	u64 renderer_frame_number;
	
	u8 draw_index;
	
	u64 render_target_index;
	void* application_frame_data;
} frame_data;
