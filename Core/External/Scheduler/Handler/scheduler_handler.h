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
    static int process_data_bus_request_content_response(const light_detector::DataBusRequestContent& content);

    /**
     * Attempts to process data bus request content of raw data type response.
     *
     * @param content - given data bus request content.
     * @return status of the data bus request content response processing.
     */
    static int process_data_bus_request_content_of_raw_data_type_response(
            const light_detector::DataBusRequestContent& content);

    /**
     * Attempts to process info bus request content response.
     *
     * @param content - given info bus request content.
     * @return status of the info bus request content response processing.
     */
    static int process_info_bus_request_content_response(const light_detector::InfoBusRequestContent& content);

    /**
     * Attempts to process settings bus request content response.
     *
     * @param content - given settings bus request content.
     * @return status of the settings bus request content response processing.
     */
    static int process_settings_bus_request_content_response(const light_detector::SettingsBusRequestContent& content);
};

#endif //LIGHT_DETECTOR_SCHEDULER_HANDLER_H
