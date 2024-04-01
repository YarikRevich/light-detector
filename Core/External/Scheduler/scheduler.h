#ifndef LIGHT_DETECTOR_SCHEDULER_H
#define LIGHT_DETECTOR_SCHEDULER_H

#include "scheduler_handler.h"
#include "state.h"
#include "indicator.h"

/**
 * Represents task scheduler implementation.
 */
class Scheduler {
public:
    /**
     * Handles external timer tick action.
     */
    static void handle_tick();

    /**
     * Handles external button status check action.
     */
    static void handle_status_check();
};

#endif //LIGHT_DETECTOR_SCHEDULER_H
