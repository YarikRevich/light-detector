#ifndef LIGHT_DETECTOR_SCHEDULER_HANDLER_H
#define LIGHT_DETECTOR_SCHEDULER_HANDLER_H

#include "stm32l4xx_hal.h"
#include "tsl2591x.h"

#include "request.h"
#include "data.h"
#include "info.h"
#include "settings.h"
#include "proto_codec.h"
#include "proto_helper.h"

#include "state.h"

extern UART_HandleTypeDef huart2;

/**
 * Represents scheduler handler used to expose
 */
class SchedulerHandler {
public:
    /**
     * Handles high-level incoming request, received during one exact timer tick.
     *
     * @return status of the request handling.
     */
    static int handle_request();

    /**
     * Handles high-level outcoming response, sent during one exact timer tick.
     *
     * @return status of the response handling.
     */
    static int handle_response();
private:
    /**
     * Attempts to process incoming request container if there is one.
     *
     * @return status of the request container processing.
     */
    static int try_process_request_container();

    /**
     * Attempts to process data bus request content response.
     *
     * @param content - given data bus request content.
     * @return status of the data bus request content response processing.
     */
    static int process_data_bus_request_content_response(const light_detector::RequestContainer& content);

    /**
     * Attempts to process data bus request content of raw data type response.
     *
     * @param content - given data bus request content.
     * @return status of the data bus request content response processing.
     */
    static int process_data_bus_request_content_of_raw_data_type_response(
            const light_detector::RequestContainer& content);

    /**
     * Attempts to process data bus request content of full data type response.
     *
     * @param content - given data bus request content.
     * @return status of the data bus request content response processing.
     */
    static int process_data_bus_request_content_of_full_data_type_response(
            const light_detector::RequestContainer& content);

    /**
     * Attempts to process data bus request content of infrared data type response.
     *
     * @param content - given data bus request content.
     * @return status of the data bus request content response processing.
     */
    static int process_data_bus_request_content_of_infrared_data_type_response(
            const light_detector::RequestContainer& content);

    /**
     * Attempts to process data bus request content of visible data type response.
     *
     * @param content - given data bus request content.
     * @return status of the data bus request content response processing.
     */
    static int process_data_bus_request_content_of_visible_data_type_response(
            const light_detector::RequestContainer& content);

    /**
     * Attempts to process info bus request content response.
     *
     * @param content - given info bus request content.
     * @return status of the info bus request content response processing.
     */
    static int process_info_bus_request_content_response(const light_detector::RequestContainer& content);

    /**
     * Attempts to process info bus request content of gain info type response.
     *
     * @param content - given info bus request content.
     * @return status of the info bus request content response processing.
     */
    static int process_info_bus_request_content_of_gain_info_type_response(
            const light_detector::RequestContainer& content);

    /**
     * Attempts to process info bus request content of integral time info type response.
     *
     * @param content - given info bus request content.
     * @return status of the info bus request content response processing.
     */
    static int process_info_bus_request_content_of_integral_time_info_type_response(
            const light_detector::RequestContainer& content);

    /**
     * Attempts to process settings bus request content response.
     *
     * @param content - given settings bus request content.
     * @return status of the settings bus request content response processing.
     */
    static int process_settings_bus_request_content_response(const light_detector::RequestContainer& content);
};

#endif //LIGHT_DETECTOR_SCHEDULER_HANDLER_H