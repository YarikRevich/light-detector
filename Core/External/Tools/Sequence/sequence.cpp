#include "sequence.h"

template <typename T>
int Sequence<T>::traverse(std::function<int(T)> callback) {
    while (!sequence.empty()) {
        if (callback(sequence.front()) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }

        sequence.pop();
    }

    return EXIT_SUCCESS;
}

template <typename T>
void Sequence<T>::add(T src) {
    sequence.push(src);
}

template <typename T>
bool Sequence<T>::is_empty() {
    return sequence.empty();
}