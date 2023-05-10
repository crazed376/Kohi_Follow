#pragma once

#include "defines.h"

// A function pointer definition for jobs
typedef b8 (*pfn_job_start)(void*, void*);

// A function pointer definition for completion of a job
typedef void (*pfn_job_on_complete)(void*);

struct frame_data;
typedef enum job_type {
    // A general job that does not have any specific thread requirements
    // This means it matters little which job thread this job runs on
    JOB_TYPE_GENERAL = 0x02,
    // A resource loading job. Resources should always load on the same
    // thread to avoid potential disk thrashing
    JOB_TYPE_RESOURCE_LOAD = 0x04,
    // Jobs using GPU resources should be bound to a thread using this job
    // type. Multithreaded renderers will use a specific job thread, and
    // this type of job will run on that thread. For single-threaded
    // renderers, this will be on the main thread.
    JOB_TYPE_GPU_RESOURCE = 0x08,
} job_type;

// Determines which job queue a job uses. The high-priority queue is
// always exhausted first before processing the normal-priority queue,
// which must also be exhausted before processing the low-priority queue.
typedef enum job_priority {
    // The lowest-priority job, used for things that can wait to be done if need be, such as log flushing
    JOB_PRIORITY_LOW,
    // A normal-priority job. Should be used for medium-priority tasks such as loading assets
    JOB_PRIORITY_NORMAL,
    // The highest-priority job. Should be used sparingly, and only for time-critical operations
    JOB_PRIORITY_HIGH
} job_priority;

typedef struct job_info {
    job_type type;
    job_priority priority;
    pfn_job_start entry_point;
    pfn_job_on_complete on_success;
    pfn_job_on_complete on_fail;
    void* param_data;
    u32 param_data_size;
    void* result_data;
    u32 result_data_size;
} job_info;

typedef struct job_system_config {
	u8 max_job_thread_count;
	u32* type_masks;
} job_system_config;

b8 job_system_initialize(u64* memory_requirement, void* state, void* config);
void job_system_shutdown(void* state);

b8 job_system_update(void* state, const struct frame_data* p_frame_data);
KAPI void job_system_submit(job_info info);

KAPI job_info job_create(pfn_job_start entry_point, pfn_job_on_complete on_success, pfn_job_on_complete on_fail, void* param_data, u32 param_data_size, u32 result_data_size);
KAPI job_info job_create_type(pfn_job_start entry_point, pfn_job_on_complete on_success, pfn_job_on_complete on_fail, void* param_data, u32 param_data_size, u32 result_data_size, job_type type);
KAPI job_info job_create_priority(pfn_job_start entry_point, pfn_job_on_complete on_success, pfn_job_on_complete on_fail, void* param_data, u32 param_data_size, u32 result_data_size, job_type type, job_priority priority);
