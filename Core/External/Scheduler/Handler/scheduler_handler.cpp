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

    if (!request_container_sequence.is_empty()) {
        return request_container_sequence.traverse_with_break(
                [](const light_detector::RequestContainer &content) -> int {
                    return SchedulerHandler::try_process_response_container(content);
                });
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::try_process_request_container() {
    auto request_buffer = ProtoCodec::get_request_buffer();

//    uint8_t test[100] = {0, 0, 0, 0, 0, 0};

    HAL_UART_Receive(
            &huart2, &request_buffer.get_raw_buffer()[0], 100, 100000);

//    request_buffer.get_raw_buffer()[0] = test[0];
//    request_buffer.get_raw_buffer()[1] = test[1];
//    request_buffer.get_raw_buffer()[2] = test[2];
//    request_buffer.get_raw_buffer()[3] = test[3];
//    request_buffer.get_raw_buffer()[4] = test[4];
//    request_buffer.get_raw_buffer()[5] = test[5];

//    if (request_buffer.get_raw_buffer()[0] != 1 && request_buffer.get_raw_buffer()[4] != 1) {
//        Indicator::toggle_action_success();
//    }

//    HAL_UART_Receive(
//            &huart2, request_buffer.get_raw_buffer(), request_buffer.get_size(), 100000);

    return ProtoCodec::decode_request_container();
}

int SchedulerHandler::try_process_response_container(const light_detector::RequestContainer &content) {
    if (content.msgId() == 1) {
        Indicator::toggle_action_success();
    }

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

    HAL_UART_Transmit(
            &huart2, response_buffer.get_raw_buffer(), response_buffer.get_size(), 1000);

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_data_bus_request_content_response(
        const light_detector::RequestContainer &content) {
    auto data_bus_request_content =
            ProtoHelper::extract_data_bus_request_content(content);

    if (ProtoHelper::is_data_bus_request_content_of_raw_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_raw_data_type_response(content);
    } else if (ProtoHelper::is_data_bus_request_content_of_full_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_full_data_type_response(content);
    } else if (ProtoHelper::is_data_bus_request_content_of_infrared_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_infrared_data_type_response(content);
    } else if (ProtoHelper::is_data_bus_request_content_of_visible_data_type(data_bus_request_content)) {

        return SchedulerHandler::process_data_bus_request_content_of_visible_data_type_response(content);
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_data_bus_request_content_of_raw_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

int SchedulerHandler::process_data_bus_request_content_of_full_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_dataType(light_detector::DataType::Full);

    if (TSL2591X::is_available()) {
        data_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        data_bus_response_content.set_value(TSL2591X::read_full());
    } else {
        data_bus_response_content.set_deviceId(0);

        data_bus_response_content.set_value(0);
    }

    data_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_infrared_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

int SchedulerHandler::process_data_bus_request_content_of_visible_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_dataType(light_detector::DataType::Visible);

    if (TSL2591X::is_available()) {
        data_bus_response_content.set_deviceId(TSL2591X::get_device_id());

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

        return process_info_bus_request_content_of_gain_info_type_response(content);
    } else if (ProtoHelper::is_info_bus_request_content_of_integral_time_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_integral_time_info_type_response(content);
    } else if (ProtoHelper::is_info_bus_request_content_of_processed_requests_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_processed_requests_info_type_response(content);
    } else if (ProtoHelper::is_info_bus_request_content_of_device_available_info_type(info_bus_request_content)) {

        return process_info_bus_request_content_of_device_available_info_type_response(content);
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_info_bus_request_content_of_gain_info_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

int SchedulerHandler::process_info_bus_request_content_of_integral_time_info_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

int SchedulerHandler::process_info_bus_request_content_of_processed_requests_info_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

int SchedulerHandler::process_info_bus_request_content_of_device_available_info_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

        return SchedulerHandler::process_settings_bus_request_content_of_reset_settings_type_response(content);
    } else if (ProtoHelper::is_settings_bus_request_content_of_set_gain_settings_type(
            settings_bus_request_content)) {

        return SchedulerHandler::process_settings_bus_request_content_of_set_gain_settings_type_response(content);
    } else if (ProtoHelper::is_settings_bus_request_content_of_set_integral_time_settings_type(
            settings_bus_request_content)) {

        return SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_settings_type_response(
                content);
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::process_settings_bus_request_content_of_reset_settings_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

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

int SchedulerHandler::process_settings_bus_request_content_of_set_gain_settings_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetGain);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_gain(content.get_settingsBus().get_value());

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_of_set_integral_time_settings_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::SettingsBusResponseContent settings_bus_response_content;

    settings_bus_response_content.set_settingsType(light_detector::SettingsType::SetIntegralTime);

    if (TSL2591X::is_available()) {
        settings_bus_response_content.set_deviceId(TSL2591X::get_device_id());

        TSL2591X::set_integral_time(content.get_settingsBus().get_value());

        settings_bus_response_content.set_result(true);
    } else {
        settings_bus_response_content.set_deviceId(0);

        settings_bus_response_content.set_result(false);
    }

    settings_bus_response_content.set_nonce(State::allocate_response_nonce());

    response_container.set_settingsBus(settings_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}
