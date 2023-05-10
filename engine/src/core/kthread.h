#pragma once

#include "defines.h"

// Represents a process thread in the system to be used for work.
// Generally should not be created directly in user code.
// This calls to the platform-specific thread implementation.

typedef struct kthread {
    void* internal_data;
    u64 thread_id;
} kthread;

// A function pointer to be invoked when the thread starts
typedef u32 (*pfn_thread_start)(void*);

b8 kthread_create(pfn_thread_start start_function_ptr, void* params, b8 auto_detach, kthread* out_thread);
void kthread_destroy(kthread* thread);

void kthread_detach(kthread* thread);
void kthread_cancel(kthread* thread);

b8 kthread_is_active(kthread* thread);
void kthread_sleep(kthread* thread, u64 ms);

u64 platform_current_thread_id(void);
