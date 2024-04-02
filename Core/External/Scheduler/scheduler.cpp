#include "scheduler.h"

void Scheduler::schedule_tick() {
    State::get_task_sequence().add([]() -> int {
        if (SchedulerHandler::handle_request() != EXIT_SUCCESS) {
            Indicator::toggle_invalid_request();

            return EXIT_FAILURE;
        }

        if (SchedulerHandler::handle_response() != EXIT_SUCCESS) {
            Indicator::toggle_invalid_response();

            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    });
}

void Scheduler::schedule_status_check() {
    State::get_task_sequence().add([]() -> int {
        if (TSL2591X::is_available()) {
            Indicator::toggle_action_success();
        } else {
            Indicator::toggle_action_failure();
        }

        return EXIT_SUCCESS;
    });
}