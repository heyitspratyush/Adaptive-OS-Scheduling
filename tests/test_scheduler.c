
#include <stdio.h>
#include "../src/core/scheduler.h"

static int test_select(
    Process ready_queue[],
    int queue_size,
    int current_time
) {
    (void)ready_queue;
    (void)current_time;

    if (queue_size == 0) {
        return -1;
    }

    return 0;
}

static int test_preempt(
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

int main(void) {
    Scheduler scheduler;

    scheduler.select_process = test_select;
    scheduler.should_preempt = test_preempt;

    Process processes[1];
    processes[0] = process_create(1, 0, 5, 1);

    int selected = scheduler.select_process(
        processes, 1, 0
    );

    int preempt = scheduler.should_preempt(
        &processes[0], NULL, 0, 0
    );

    if (selected != 0 || preempt != 0) {
        printf("FAIL: Scheduler interface test\n");
        return 1;
    }

    printf("PASS: Scheduler interface test\n");
    return 0;
}
