
#include "process.h"

Process process_create(
    int pid,
    int arrival_time,
    int burst_time,
    int priority
) {
    Process process;

    process.pid = pid;
    process.arrival_time = arrival_time;
    process.burst_time = burst_time;
    process.remaining_time = burst_time;
    process.priority = priority;

    process.start_time = -1;
    process.completion_time = -1;

    return process;
}

