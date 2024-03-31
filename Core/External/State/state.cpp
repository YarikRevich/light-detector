#include "state.h"

Sequence<light_detector::RequestContainer> State::requestContainerSequence = NULL;

Sequence<light_detector::RequestContainer> State::getRequestContainerSequence() {
    return this->sequence;
}
