#include "state.h"

int State::amount_of_processed_requests = 0;

int State::get_amount_of_processed_requests() {
    return amount_of_processed_requests;
};

Sequence<light_detector::RequestContainer> State::get_request_container_sequence() {
    return request_container_sequence;
}
