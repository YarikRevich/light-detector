#ifndef LIGHT_DETECTOR_STATE_H
#define LIGHT_DETECTOR_STATE_H

#include "request.h"
#include "mutex.h"
#include "sequence.h"

#include <queue>

/**
 * Represents device state handler.
 */
class State {
public:
    /**
     * Checks if the device is configured.
     *
     * @return result of the check.
     */
    static bool is_device_configured();

    /**
     * Sets device configured mode with the given value.
     *
     * @param value - value of the configure mode.
     */
    static void set_device_configured(bool value);

    /**
     * Checks if the device is enabled.
     *
     * @return result of the check.
     */
    static bool is_device_enabled();

    /**
     * Sets device enabled mode with the given value.
     *
     * @param value - value of the enabled mode.
     */
    static void set_device_enabled(bool value);

    /**
     * Retrieves amount of processed events.
     *
     * @return amount of processed events.
     */
    static int get_amount_of_processed_requests();

    /**
     * Allocates new response nonce.
     *
     * @return allocated response nonce.
     */
    static int allocate_response_nonce();

    /**
     * Retrieves button mutex.
     *
     * @return retrieved button mutex.
     */
    static Mutex& get_button_mutex();

    /**
     * Retrieves task sequence used to perform scheduled tasks execution.
     *
     * @return retrieved task sequence.
     */
    static Sequence<std::function<int()>>& get_task_sequence();

    /**
     * Retrieves request container sequence.
     *
     * @return retrieved request container sequence.
     */
    static Sequence<light_detector::RequestContainer>& get_request_container_sequence();

private:
    /**
     * Represents device configured mode.
     */
    static bool device_configured;

    /**
     * Represents device enabled mode.
     */
    static bool device_enabled;

    /**
     * Represents amount of processed incoming requests.
     */
    static int amount_of_processed_requests;

    /**
     * Represents current(latest) response nonce.
     */
    static int current_response_nonce;

    /**
     * Represents button mutex used to manage pressed button operations invokation.
     */
    static Mutex button_mutex;

    /**
    * Represents scheduled tasks sequence.
    */
    static Sequence<std::function<int()>> task_sequence;

    /**
     * Represents sequence of request containers. Used for internal scheduler logic.
     */
    static Sequence<light_detector::RequestContainer> request_container_sequence;
};

#endif //LIGHT_DETECTOR_STATE_H
