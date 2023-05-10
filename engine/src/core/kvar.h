#pragma once

#include "defines.h"

b8 kvar_initialize(u64* memory_requirement, void* memory, void* config);
void kvar_shutdown(void* state);

KAPI b8 kvar_int_create(const char* name, i32 value);
KAPI b8 kvar_int_get(const char* name, i32* out_value);
KAPI b8 kvar_int_set(const char* name, i32 value);
