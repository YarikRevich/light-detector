#ifndef LIGHT_DETECTOR_SEQUENCE_H
#define LIGHT_DETECTOR_SEQUENCE_H

#include <queue>
#include <functional>
#include <cstdlib>

/**
 * Represents sequence wrapper implementation.
 *
 * @tparam T given type of the content for sequence.
 */
template <typename T>
class Sequence {
public:
    /**
     * Iterates over all available content and removes it from the sequence.
     *
     * @param callback - given callback to be called for each iteration.
     * @return status of the performed operation.
     */
    int traverse(std::function<int(T)> callback);

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
    bool is_empty();
private:
    std::queue<T> sequence;
};

#endif //LIGHT_DETECTOR_SEQUENCE_H
