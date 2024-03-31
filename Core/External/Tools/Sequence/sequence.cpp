#include "sequence.h"

template <typename T>
void Sequence<T>::add(T src) {
    sequence.push(src);
}

template <typename T>
bool Sequence<T>::isEmpty() {
    return sequence.empty();
}