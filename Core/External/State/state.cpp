#include "state.h"

int State::amount_of_processed_requests = 0;

int State::current_response_nonce = 0;

Sequence<light_detector::RequestContainer> State::request_container_sequence =
        Sequence<light_detector::RequestContainer>();

int State::get_amount_of_processed_requests() {
    return amount_of_processed_requests;
};

int State::get_current_response_nonce() {
    return current_response_nonce;
}

Sequence<light_detector::RequestContainer> State::get_request_container_sequence() {
    return request_container_sequence;
}
