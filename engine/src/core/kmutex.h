#pragma once

#include "defines.h"

// A mutex to be used for synchronization purposes. A mutex (or
// mutual exclusion) is used to limit access to a resource when
// there are multiple threads of execution around that resource.

typedef struct kmutex {
    void* internal_data;
} kmutex;

b8 kmutex_create(kmutex* out_mutex);
void kmutex_destroy(kmutex* mutex);

b8 kmutex_lock(kmutex* mutex);
b8 kmutex_unlock(kmutex* mutex);
