#ifndef SIMULATION_H
#define SIMULATION_H

#include "process.h"
#include "scheduler.h"

int simulation_run(
    Process processes[],
    int process_count,
    Scheduler scheduler
);

#endif