#ifndef LIGHT_DETECTOR_PROTO_HELPER_H
#define LIGHT_DETECTOR_PROTO_HELPER_H

#include "request.h"
#include "data.h"
#include "info.h"
#include "settings.h"

/**
 * Contains aliases to perform proto declaration related operation.
 */
class ProtoHelper {
public:
    /**
     * Checks if the given request container is related to data bus.
     *
     * @param container - given request container.
     * @return result of the check.
     */
    static bool is_data_bus_request_container(const light_detector::RequestContainer& container);

    /**
     * Checks if the given request container is related to info bus.
     *
     * @param container - given request container.
     * @return result of the check.
     */
    static bool is_info_bus_request_container(const light_detector::RequestContainer& container);

    /**
     * Checks if the given request container is related to settings bus.
     *
     * @param container - given request container.
     * @return result of the check.
     */
    static bool is_settings_bus_request_container(const light_detector::RequestContainer& container);

    /**
     * Extracts data bus request container from the raw request container.
     *
     * @param container - given raw request container.
     * @return extracted data bus request container.
     */
    static light_detector::DataBusRequestContent extract_data_bus_request_content(
            const light_detector::RequestContainer& container);

    /**
     * Extracts info bus request container from the raw request container.
     *
     * @param container - given raw request container.
     * @return extracted data bus request container.
     */
    static light_detector::InfoBusRequestContent extract_info_bus_request_content(
            const light_detector::RequestContainer& container);

    /**
     * Extracts settings bus request container from the raw request container.
     *
     * @param container - given raw request container.
     * @return extracted data bus request container.
     */
    static light_detector::SettingsBusRequestContent extract_settings_bus_request_content(
            const light_detector::RequestContainer& container);

    /**
     * Checks if the given data bus request content of raw data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_raw_data_type(const light_detector::DataBusRequestContent& content);

    /**
     * Checks if the given data bus request content of full data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_full_data_type(const light_detector::DataBusRequestContent& content);

    /**
     * Checks if the given data bus request content of infrared data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_infrared_data_type(const light_detector::DataBusRequestContent& content);

    /**
     * Checks if the given data bus request content of visible data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_visible_data_type(const light_detector::DataBusRequestContent& content);
};

#endif //LIGHT_DETECTOR_PROTO_HELPER_H
