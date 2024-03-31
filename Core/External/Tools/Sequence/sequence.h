#ifndef LIGHT_DETECTOR_SEQUENCE_H
#define LIGHT_DETECTOR_SEQUENCE_H

#include <queue>

/**
 * Represents sequence wrapper implementation.
 *
 * @tparam T given type of the content for sequence.
 */
template <typename T>
class Sequence {
public:
    /**
     * Adds new value to the sequence.
     *
     * @param src - given value to be added to the sequence.
     */
    void add(T src);

    /**
     * Checks if the sequence is empty.
     *
     * @return result of the check.
     */
    bool isEmpty();
private:
    std::queue<T> sequence;
};

#endif //LIGHT_DETECTOR_SEQUENCE_H
