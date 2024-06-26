#include "scheduler_handler.h"


int SchedulerHandler::handle_request() {
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == SET) {
        if (try_process_request_container() != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }

        State::increase_processed_requests();
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::handle_response() {
    auto request_container_sequence = State::get_request_container_sequence();

    if (!request_container_sequence->is_empty()) {
        return request_container_sequence->traverse_with_break(
                [](const light_detector::RequestContainer &content) -> int {
                    return SchedulerHandler::try_process_response_container(content);
                });
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::try_process_request_container() {
    auto request_buffer = ProtoCodec::get_request_buffer();

    uint8_t max_size;

    if (HAL_UART_Receive(
            &huart2, &max_size, 1, POLL_TIMEOUT) != HAL_OK) {
        return EXIT_FAILURE;
    }

    request_buffer->set_max_size(max_size);

    uint8_t raw_buffer[max_size];

    if (HAL_UART_Receive(&huart2, raw_buffer, max_size, POLL_TIMEOUT) != HAL_OK) {
        return EXIT_FAILURE;
    }

    request_buffer->set_raw_buffer(raw_buffer);

    return ProtoCodec::decode_request_container();
}

int SchedulerHandler::try_process_response_container(const light_detector::RequestContainer &content) {
    if (ProtoHelper::is_data_bus_request_container(content)) {

        if (SchedulerHandler::process_data_bus_request_content_response(content) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    } else if (ProtoHelper::is_info_bus_request_container(content)) {

        if (SchedulerHandler::process_info_bus_request_content_response(content) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    } else if (ProtoHelper::is_settings_bus_request_container(content)) {

        if (SchedulerHandler::process_settings_bus_request_content_response(content) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    }

    return SchedulerHandler::try_transmit_response_container();
}

int SchedulerHandler::try_transmit_response_container() {
    auto response_buffer = ProtoCodec::get_response_buffer();

    auto conversion_result = Converter::convertUint32ToUint8(response_buffer->get_size());

    if (HAL_UART_Transmit(
            &huart2,
            conversion_result.data,
            3,
            TRANSMIT_TIMEOUT) != HAL_OK) {
        return EXIT_FAILURE;
    }

    if (HAL_UART_Transmit(
            &huart2,
            response_buffer->get_raw_buffer(),
            response_buffer->get_size(),
            TRANSMIT_TIMEOUT) != HAL_OK) {
        return EXIT_FAILURE;
    }

    response_buffer->clear();

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_data_bus_request_content_response(
        const light_detector::RequestContainer &content) {
    auto data_bus_request_content =
            ProtoHelper::extract_data_bus_request_content(content);

    if (ProtoHelper::is_data_bus_request_content_of_raw_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_raw_data_type_response();
    } else if (ProtoHelper::is_data_bus_request_content_of_full_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_full_data_type_response();
    } else if (ProtoHelper::is_data_bus_request_content_of_infrared_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_infrared_data_type_response();
    } else if (ProtoHelper::is_data_bus_request_content_of_visible_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_visible_data_type_response();
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_data_bus_request_content_of_raw_data_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_dataType(light_detector::DataType::Raw);

    if (TSL2591X::is_available()) {
        data_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        data_bus_response_content.set_value(TSL2591X::read_lux());

        TSL2591X::invoke_lux_interrupt(LUX_LOW, LUX_HIGH);
    } else {
        data_bus_response_content.set_deviceId(0);

        data_bus_response_content.set_value(0);
    }

    data_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_full_data_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_dataType(light_detector::DataType::Full);

    if (TSL2591X::is_available()) {
        data_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::invoke_lux_interrupt(LUX_LOW, LUX_HIGH);

        data_bus_response_content.set_value(TSL2591X::read_full());
    } else {
        data_bus_response_content.set_deviceId(0);

        data_bus_response_content.set_value(0);
    }

    data_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_infrared_data_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_dataType(light_detector::DataType::Infrared);

    if (TSL2591X::is_available()) {
        data_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        data_bus_response_content.set_value(TSL2591X::read_infrared());
    } else {
        data_bus_response_content.set_deviceId(0);

        data_bus_response_content.set_value(0);
    }

    data_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_visible_data_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_dataType(light_detector::DataType::Visible);

    if (TSL2591X::is_available()) {
        data_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::invoke_raw_interrupt_threshold(LUX_LOW, LUX_HIGH);

        data_bus_response_content.set_value(TSL2591X::read_visible());
    } else {
        data_bus_response_content.set_deviceId(0);

        data_bus_response_content.set_value(0);
    }

    data_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_info_bus_request_content_response(
        const light_detector::RequestContainer &content) {
    auto info_bus_request_content =
            ProtoHelper::extract_info_bus_request_content(content);

    if (ProtoHelper::is_info_bus_request_content_of_gain_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_gain_info_type_response();
    } else if (ProtoHelper::is_info_bus_request_content_of_integral_time_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_integral_time_info_type_response();
    } else if (ProtoHelper::is_info_bus_request_content_of_processed_requests_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_processed_requests_info_type_response();
    } else if (ProtoHelper::is_info_bus_request_content_of_device_available_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_device_available_info_type_response();
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_info_bus_request_content_of_gain_info_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::InfoBusResponseContent info_bus_response_content;

    info_bus_response_content.set_infoType(light_detector::InfoType::Gain);

    if (TSL2591X::is_available()) {
        info_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        info_bus_response_content.set_value(TSL2591X::get_gain());
    } else {
        info_bus_response_content.set_deviceId(0);

        info_bus_response_content.set_value(0);
    }

    info_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_infoBus(info_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
};

int SchedulerHandler::process_info_bus_request_content_of_integral_time_info_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::InfoBusResponseContent info_bus_response_content;

    info_bus_response_content.set_infoType(light_detector::InfoType::IntegralTime);

    if (TSL2591X::is_available()) {
        info_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        info_bus_response_content.set_value(TSL2591X::get_integral_time());
    } else {
        info_bus_response_content.set_deviceId(0);

        info_bus_response_content.set_value(0);
    }

    info_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_infoBus(info_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
};

int SchedulerHandler::process_info_bus_request_content_of_processed_requests_info_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::InfoBusResponseContent info_bus_response_content;

    if (TSL2591X::is_available()) {
        info_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    } else {
        info_bus_response_content.set_deviceId(0);
    }

    info_bus_response_content.set_infoType(light_detector::InfoType::ProcessedRequests);

    info_bus_response_content.set_value(State::get_processed_requests());
    info_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_infoBus(info_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
};

int SchedulerHandler::process_info_bus_request_content_of_device_available_info_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::InfoBusResponseContent info_bus_response_content;

    if (TSL2591X::is_available()) {
        info_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    } else {
        info_bus_response_content.set_deviceId(0);
    }

    info_bus_response_content.set_infoType(light_detector::InfoType::DeviceAvailable);

    info_bus_response_content.set_value(TSL2591X::is_available());
    info_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_infoBus(info_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
};

int SchedulerHandler::process_settings_bus_request_content_response(
        const light_detector::RequestContainer &content) {
    auto settings_bus_request_content =
            ProtoHelper::extract_settings_bus_request_content(content);

    if (ProtoHelper::is_settings_bus_request_content_of_reset_settings_type(
            settings_bus_request_content)) {

        if (SchedulerHandler::process_settings_bus_request_content_of_reset_settings_type_response() != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    } else if (ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type(
            settings_bus_request_content)) {

        if (ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_low_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_gain_low_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_medium_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_gain_medium_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_high_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_gain_high_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type_of_max_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_gain_max_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else {

            return EXIT_FAILURE;
        }
    } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type(
            settings_bus_request_content)) {

        if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_first_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_first_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_second_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_second_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_third_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_third_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_forth_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_forth_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_fifth_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_fifth_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type_of_sixth_type(
                content.settingsBus())) {

            if (SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_sixth_settings_type_response()
                != EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }
        } else {

            return EXIT_FAILURE;
        }
    }

    Indicator::toggle_action_success();

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_settings_bus_request_content_of_reset_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::Reset);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::reset();

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_gain_low_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetGainLow);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_gain(LOW_AGAIN);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_gain_medium_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetGainMedium);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_gain(MEDIUM_AGAIN);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_gain_high_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetGainHigh);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_gain(HIGH_AGAIN);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_gain_max_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetGainMax);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_gain(MAX_AGAIN);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_first_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTimeFirst);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(ATIME_100MS);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}


int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_second_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTimeSecond);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(ATIME_200MS);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}


int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_third_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTimeThird);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(ATIME_300MS);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_forth_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTimeForth);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(ATIME_400MS);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_fifth_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTimeFifth);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(ATIME_500MS);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_sixth_settings_type_response() {
    light_detector::ResponseContainer response_container;

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTimeSixth);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(ATIME_600MS);

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}
