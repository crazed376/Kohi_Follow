#pragma once

#include "defines.h"

KAPI void metrics_initialize(void);
KAPI void metrics_update(f64 frame_elapsed_time);
KAPI f64 metrics_fps(void);
KAPI f64 metrics_frame_time(void);
KAPI void metrics_frame(f64* out_fps, f64* out_frame_ms);
