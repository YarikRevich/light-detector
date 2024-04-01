#include "scheduler.h"

void Scheduler::handle_tick() {
    if (SchedulerHandler::handle_request() != EXIT_SUCCESS) {
        Indicator::toggle_invalid_request();

        return;
    }

    if (SchedulerHandler::handle_response() != EXIT_SUCCESS) {
        Indicator::toggle_invalid_response();
    }
}

void Scheduler::handle_status_check() {
    if (TSL2591X::is_available()) {
        Indicator::toggle_action_success();
    }
}