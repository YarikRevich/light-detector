#include "proto_helper.h"

bool ProtoHelper::is_data_bus_request_container(const light_detector::RequestContainer &container) {
    return container.get_which_content() == light_detector::RequestContainer::FieldNumber::DATABUS;
}

bool ProtoHelper::is_info_bus_request_container(const light_detector::RequestContainer &container) {
    return container.get_which_content() == light_detector::RequestContainer::FieldNumber::INFOBUS;
}

bool ProtoHelper::is_settings_bus_request_container(const light_detector::RequestContainer &container) {
    return container.get_which_content() == light_detector::RequestContainer::FieldNumber::SETTINGSBUS;
}

light_detector::DataBusRequestContent ProtoHelper::extract_data_bus_request_content(
        const light_detector::RequestContainer &container) {
    return container.dataBus();
}

light_detector::InfoBusRequestContent ProtoHelper::extract_info_bus_request_content(
        const light_detector::RequestContainer &container) {
    return container.infoBus();
}

light_detector::SettingsBusRequestContent ProtoHelper::extract_settings_bus_request_content(
        const light_detector::RequestContainer &container) {
    return container.settingsBus();
}

bool ProtoHelper::is_data_bus_request_content_of_raw_data_type(const light_detector::DataBusRequestContent &content) {
    return content.dataType() == light_detector::DataType::Raw;
}

bool ProtoHelper::is_data_bus_request_content_of_full_data_type(const light_detector::DataBusRequestContent &content) {
    return content.dataType() == light_detector::DataType::Full;
}

bool
ProtoHelper::is_data_bus_request_content_of_infrared_data_type(const light_detector::DataBusRequestContent &content) {
    return content.dataType() == light_detector::DataType::Infrared;
}

bool
ProtoHelper::is_data_bus_request_content_of_visible_data_type(const light_detector::DataBusRequestContent &content) {
    return content.dataType() == light_detector::DataType::Visible;
}

bool ProtoHelper::is_info_bus_request_content_of_gain_info_type(
        const light_detector::InfoBusRequestContent &content) {
    return content.infoType() == light_detector::InfoType::Gain;
}

bool ProtoHelper::is_info_bus_request_content_of_integral_time_info_type(
        const light_detector::InfoBusRequestContent &content) {
    return content.infoType() == light_detector::InfoType::IntegralTime;
}

bool ProtoHelper::is_info_bus_request_content_of_processed_requests_info_type(
        const light_detector::InfoBusRequestContent &content) {
    return content.infoType() == light_detector::InfoType::ProcessedRequests;
}

bool ProtoHelper::is_info_bus_request_content_of_device_available_info_type(
        const light_detector::InfoBusRequestContent &content) {
    return content.infoType() == light_detector::InfoType::DeviceAvailable;
}

bool ProtoHelper::is_settings_bus_request_content_of_reset_settings_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::Reset;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type(
        const light_detector::SettingsBusRequestContent &content) {
    return is_settings_bus_request_content_of_set_gain_settings_type_of_low_type(content) ||
            is_settings_bus_request_content_of_set_gain_settings_type_of_medium_type(content) ||
            is_settings_bus_request_content_of_set_gain_settings_type_of_high_type(content) ||
            is_settings_bus_request_content_of_set_gain_settings_type_of_max_type(content);
}

bool ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_low_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetGainLow;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_medium_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetGainMedium;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_high_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetGainHigh;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_max_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetGainMax;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type(
        const light_detector::SettingsBusRequestContent &content) {
    return ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_first_type(content) ||
            ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_second_type(content) ||
            ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_third_type(content) ||
            ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_forth_type(content) ||
            ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_fifth_type(content) ||
            ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_sixth_type(content);
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_first_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetIntegralTimeFirst;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_second_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetIntegralTimeSecond;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_third_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetIntegralTimeThird;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_forth_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetIntegralTimeForth;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_fifth_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetIntegralTimeFifth;
}

bool ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_sixth_type(
        const light_detector::SettingsBusRequestContent &content) {
    return content.settingsType() == light_detector::SettingsType::SetIntegralTimeSixth;
}
