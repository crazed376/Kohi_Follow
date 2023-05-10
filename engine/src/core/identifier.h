#pragma once

#include "defines.h"

// Acquires a new identifier for the given owner
KAPI u32 identifier_acquire_new_id(void* owner);

// REleases the given identifier, which can then be used again
KAPI void identifier_release_id(u32 id);
