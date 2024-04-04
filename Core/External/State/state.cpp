#include "state.h"

bool State::device_configured = false;

bool State::device_enabled = false;

int State::amount_of_processed_requests = 0;

int State::current_response_nonce = 0;

Mutex State::button_mutex = Mutex();

Sequence<std::function<int()>> State::task_sequence =
        Sequence<std::function<int()>>();

Sequence<light_detector::RequestContainer> State::request_container_sequence =
        Sequence<light_detector::RequestContainer>();

bool State::is_device_configured() {
    return device_configured;
}

void State::set_device_configured(bool value) {
    device_configured = true;
}

bool State::is_device_enabled() {
    return device_enabled;
}

void State::set_device_enabled(bool value) {
    device_enabled = true;
}

int State::get_amount_of_processed_requests() {
    return amount_of_processed_requests;
};

int State::allocate_response_nonce() {
    return current_response_nonce++;
}

Mutex& State::get_button_mutex() {
    return button_mutex;
}

Sequence<std::function<int()>>& State::get_task_sequence() {
    return task_sequence;
}

Sequence<light_detector::RequestContainer>& State::get_request_container_sequence() {
    return request_container_sequence;
}