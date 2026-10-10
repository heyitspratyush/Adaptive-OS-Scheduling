
#include "fcfs.h"

int fcfs_select_process(
    Process ready_queue[],
    int queue_size,
    int current_time
) {
    (void)current_time;

    if (queue_size <= 0) {
        return -1;
    }

    int selected = 0;

    for (int i = 1; i < queue_size; i++) {
        if (ready_queue[i].arrival_time <
            ready_queue[selected].arrival_time) {
            selected = i;
        }
    }

    return selected;
}

int fcfs_should_preempt(
    Process *current_process,
    Process ready_queue[],
    int queue_size,
    int current_time
) {
    (void)current_process;
    (void)ready_queue;
    (void)queue_size;
    (void)current_time;

    return 0;
}

Scheduler create_fcfs_scheduler(void) {
    Scheduler scheduler;

    scheduler.select_process = fcfs_select_process;
    scheduler.should_preempt = fcfs_should_preempt;

    return scheduler;
}
