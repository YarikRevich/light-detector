#ifndef LIGHT_DETECTOR_INDICATOR_H
#define LIGHT_DETECTOR_INDICATOR_H

#include "gpio.h"

/**
 * Represents indicator state machine.
 */
class Indicator {
public:
    /**
     * Indicated initialization process success.
     */
    static void toggle_initialization_success();

    /**
     * Indicated initialization process failure.
     */
    static void toggle_initialization_failure();

    /**
     * Indicated operation action success.
     */
    static void toggle_action_success();

    /**
     * Indicated operation action failure.
     */
    static void toggle_action_failure();
};

#endif //LIGHT_DETECTOR_INDICATOR_H
