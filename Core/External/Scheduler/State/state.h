#ifndef LIGHT_DETECTOR_STATE_H
#define LIGHT_DETECTOR_STATE_H

#include <mutex>

/**
 * Represents device state handler.
 */
class State {
public:


private:
    std::mutex mutex;
};

#endif //LIGHT_DETECTOR_STATE_H
