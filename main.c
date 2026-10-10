
#include <stdio.h>
#include "src/core/process.h"

int main(void) {
    Process p1 = process_create(1, 0, 8, 3);

    printf("Process ID: %d\n", p1.pid);
    printf("Arrival Time: %d\n", p1.arrival_time);
    printf("Burst Time: %d\n", p1.burst_time);
    printf("Remaining Time: %d\n", p1.remaining_time);
    printf("Priority: %d\n", p1.priority);
    printf("Start Time: %d\n", p1.start_time);
    printf("Completion Time: %d\n", p1.completion_time);

    return 0;
}
