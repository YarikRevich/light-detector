#ifndef LIGHT_DETECTOR_SCHEDULER_H
#define LIGHT_DETECTOR_SCHEDULER_H

#include "usart.h"

#include "proto.h"
#include "tsl2591x.h"

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
private:
    /**
     * Handles incoming request, handled during one exact timer tick.
     */
    static void handle_request();

    /**
     * Handles outcoming response, handled during one exact timer tick.
     */
    static void handle_response();
};

#endif //LIGHT_DETECTOR_SCHEDULER_H
