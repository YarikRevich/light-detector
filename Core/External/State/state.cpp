#include "state.h"

int State::amount_of_processed_requests = 0;

int State::current_response_nonce = 0;

Sequence<std::function<int()>> State::task_sequence =
        Sequence<std::function<int()>>();

Sequence<light_detector::RequestContainer> State::request_container_sequence =
        Sequence<light_detector::RequestContainer>();

int State::get_amount_of_processed_requests() {
    return amount_of_processed_requests;
};

int State::allocate_response_nonce() {
    return current_response_nonce++;
}

Sequence<std::function<int()>> State::get_task_sequence() {
    return task_sequence;
}

Sequence<light_detector::RequestContainer> State::get_request_container_sequence() {
    return request_container_sequence;
}