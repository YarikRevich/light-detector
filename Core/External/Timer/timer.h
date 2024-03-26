#ifndef LIGHT_DETECTOR_TIMER_H
#define LIGHT_DETECTOR_TIMER_H

#include "tsl2591x.h"

/**
 * Represents timer handler implementation.
 */
class Timer {
public:
    /**
     * Handles incoming timer tick action.
     */
    static void handle();
private:
};

#endif //LIGHT_DETECTOR_TIMER_H
