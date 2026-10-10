
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef int (*SelectProcessFunc)(
    Process ready_queue[],
    int queue_size,
    int current_time
);

typedef int (*ShouldPreemptFunc)(
    Process *current_process,
    Process ready_queue[],
    int queue_size,
    int current_time
);

typedef struct {
    SelectProcessFunc select_process;
    ShouldPreemptFunc should_preempt;
} Scheduler;

#endif
