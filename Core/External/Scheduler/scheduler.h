#ifndef LIGHT_DETECTOR_SCHEDULER_H
#define LIGHT_DETECTOR_SCHEDULER_H

#include "stm32l4xx_hal.h"

#include "proto_codec.h"
#include "state.h"
#include "indicator.h"
#include "tsl2591x.h"

extern UART_HandleTypeDef huart2;

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
     *
     * @return status of the request processing.
     */
    static int handle_request();

    /**
     * Handles outcoming response, handled during one exact timer tick.
     *
     * @return status of the response processing.
     */
    static int handle_response();
};

#endif //LIGHT_DETECTOR_SCHEDULER_H
