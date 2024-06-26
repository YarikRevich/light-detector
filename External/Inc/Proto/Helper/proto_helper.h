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
    static bool is_data_bus_request_container(const light_detector::RequestContainer &container);

    /**
     * Checks if the given request container is related to info bus.
     *
     * @param container - given request container.
     * @return result of the check.
     */
    static bool is_info_bus_request_container(const light_detector::RequestContainer &container);

    /**
     * Checks if the given request container is related to settings bus.
     *
     * @param container - given request container.
     * @return result of the check.
     */
    static bool is_settings_bus_request_container(const light_detector::RequestContainer &container);

    /**
     * Extracts data bus request container from the raw request container.
     *
     * @param container - given raw request container.
     * @return extracted data bus request container.
     */
    static light_detector::DataBusRequestContent extract_data_bus_request_content(
            const light_detector::RequestContainer &container);

    /**
     * Extracts info bus request container from the raw request container.
     *
     * @param container - given raw request container.
     * @return extracted data bus request container.
     */
    static light_detector::InfoBusRequestContent extract_info_bus_request_content(
            const light_detector::RequestContainer &container);

    /**
     * Extracts settings bus request container from the raw request container.
     *
     * @param container - given raw request container.
     * @return extracted data bus request container.
     */
    static light_detector::SettingsBusRequestContent extract_settings_bus_request_content(
            const light_detector::RequestContainer &container);

    /**
     * Checks if the given data bus request content of raw data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_raw_data_type(const light_detector::DataBusRequestContent &content);

    /**
     * Checks if the given data bus request content of full data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_full_data_type(const light_detector::DataBusRequestContent &content);

    /**
     * Checks if the given data bus request content of infrared data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_infrared_data_type(const light_detector::DataBusRequestContent &content);

    /**
     * Checks if the given data bus request content of visible data type.
     *
     * @param content - given data bus request content.
     * @return result of the check.
     */
    static bool is_data_bus_request_content_of_visible_data_type(const light_detector::DataBusRequestContent &content);

    /**
     * Checks if the given info bus request content of gain info type.
     *
     * @param content - given info bus request content.
     * @return result of the check.
     */
    static bool is_info_bus_request_content_of_gain_info_type(const light_detector::InfoBusRequestContent &content);

    /**
     * Checks if the given info bus request content of integral time info type.
     *
     * @param content - given info bus request content.
     * @return result of the check.
     */
    static bool is_info_bus_request_content_of_integral_time_info_type(
            const light_detector::InfoBusRequestContent &content);

    /**
     * Checks if the given info bus request content of processed requests info type.
     *
     * @param content - given info bus request content.
     * @return result of the check.
     */
    static bool is_info_bus_request_content_of_processed_requests_info_type(
            const light_detector::InfoBusRequestContent &content);


    /**
     * Checks if the given info bus request content of device available info type.
     *
     * @param content - given info bus request content.
     * @return result of the check.
     */
    static bool is_info_bus_request_content_of_device_available_info_type(
            const light_detector::InfoBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of reset settings type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_reset_settings_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of set gain settings type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_gain_settings_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of set gain settings type of low type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_gain_settings_type_of_low_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of set gain settings type of medium type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_gain_settings_type_of_medium_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of set gain settings type of high type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_gain_settings_type_of_high_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of set gain settings type of max type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_gain_settings_type_of_max_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content of set integral time settings type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content set integral time of settings type of first type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type_of_first_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content set integral time of settings type of second type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type_of_second_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content set integral time of settings type of third type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type_of_third_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content set integral time of settings type of forth type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type_of_forth_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content set integral time of settings type of fifth type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type_of_fifth_type(
            const light_detector::SettingsBusRequestContent &content);

    /**
     * Checks if the given settings bus request content set integral time of settings type of sixth type.
     *
     * @param content - given settings bus request content.
     * @return result of the check.
     */
    static bool is_settings_bus_request_content_of_set_integral_time_settings_type_of_sixth_type(
            const light_detector::SettingsBusRequestContent &content);
};

#endif //LIGHT_DETECTOR_PROTO_HELPER_H
