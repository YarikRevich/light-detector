#ifndef LIGHT_DETECTOR_STATE_H
#define LIGHT_DETECTOR_STATE_H

#include "request.h"
#include "sequence.h"

#include <queue>

/**
 * Represents device state handler.
 */
class State {
public:
    /**
     * Retrieves request container sequence.
     *
     * @return retrieved request container sequence.
     */
    static Sequence<light_detector::RequestContainer> getRequestContainerSequence();
private:
    static Sequence<light_detector::RequestContainer> requestContainerSequence;
};

#endif //LIGHT_DETECTOR_STATE_H
