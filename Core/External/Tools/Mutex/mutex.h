#ifndef LIGHT_DETECTOR_MUTEX_H
#define LIGHT_DETECTOR_MUTEX_H

/**
 * Represents mutex implementation for the board.
 */
class Mutex {
public:
    /**
     * Attempts to perform lock operation for the mutex.
     */
    static void lock();

    /**
     * Attempts to perform unlock operation for the mutex.
     */
    static void unlock();
};

#endif //LIGHT_DETECTOR_MUTEX_H
