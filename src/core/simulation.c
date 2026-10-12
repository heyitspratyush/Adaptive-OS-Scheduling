
#include <stdlib.h>
#include "simulation.h"
#include <stdio.h>


static int build_ready_queue(
    Process processes[],
    int process_count,
    int current_time,
    Process ready_queue[],
    int original_indices[]
) {
    int queue_size = 0;

    for (int i = 0; i < process_count; i++) {
        if (
            processes[i].arrival_time <= current_time &&
            processes[i].remaining_time > 0
        ) {
            ready_queue[queue_size] = processes[i];
            original_indices[queue_size] = i;
            queue_size++;
        }
    }

    return queue_size;
}



int simulation_run(
    Process processes[],
    int process_count,
    Scheduler scheduler
) {
    if (processes == NULL || process_count <= 0) {
        return -1;
    }

    if (scheduler.select_process == NULL ||
        scheduler.should_preempt == NULL) {
        return -1;
    }

    
    for (int i = 0; i < process_count; i++) {
        if (processes[i].arrival_time < 0 ||
            processes[i].burst_time <= 0 ||
            processes[i].remaining_time <= 0) {
            return -1;
        }
    }

    Process *ready_queue =
        malloc(sizeof(Process) * process_count);

    int *original_indices =
        malloc(sizeof(int) * process_count);

    if (ready_queue == NULL || original_indices == NULL) {
        free(ready_queue);
        free(original_indices);
        return -1;
    }

    int current_time = 0;
    int completed_count = 0;
    Process *current_process = NULL;
    int status = 0;

    while (completed_count < process_count) {
        int queue_size = build_ready_queue(
            processes,
            process_count,
            current_time,
            ready_queue,
            original_indices
        );

        if (queue_size == 0) {
            current_time++;
            current_process = NULL;
            continue;
        }

        int should_select = (current_process == NULL);

        if (!should_select) {
            should_select = scheduler.should_preempt(
                current_process,
                ready_queue,
                queue_size,
                current_time
            );
        }

        if (should_select) {
            int selected_index = scheduler.select_process(
                ready_queue,
                queue_size,
                current_time
            );

            if (selected_index < 0 ||
                selected_index >= queue_size) {
                status = -1;
                break;
            }

            int process_index =
                original_indices[selected_index];

            current_process = &processes[process_index];
        }

        if (current_process->start_time == -1) {
            current_process->start_time = current_time;
        }

        current_process->remaining_time--;
        current_time++;

        printf(
            "PID %d | Remaining: %d | Time: %d\n",
            current_process->pid,
            current_process->remaining_time,
            current_time
        );

        if (current_process->remaining_time == 0) {
            current_process->completion_time = current_time;
            completed_count++;
            current_process = NULL;
        }
    }

    free(ready_queue);
    free(original_indices);

    return status;
}
