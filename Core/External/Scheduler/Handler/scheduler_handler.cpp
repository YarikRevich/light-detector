#include "scheduler_handler.h"


int SchedulerHandler::handle_request() {
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == SET) {
        return try_process_request_container();
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::handle_response() {
    auto request_container_sequence = State::get_request_container_sequence();

    if (!request_container_sequence.is_empty()) {
        return request_container_sequence.traverse([](const light_detector::RequestContainer &content) -> int {
            if (ProtoHelper::is_data_bus_request_container(content)) {

                return SchedulerHandler::process_data_bus_request_content_response(content);
            } else if (ProtoHelper::is_info_bus_request_container(content)) {

                return SchedulerHandler::process_info_bus_request_content_response(content);
            } else if (ProtoHelper::is_settings_bus_request_container(content)) {

                return SchedulerHandler::process_settings_bus_request_content_response(content);
            }

            return EXIT_SUCCESS;
        });
    }

    return EXIT_SUCCESS;
}

int SchedulerHandler::try_process_request_container() {
    auto request_buffer = ProtoCodec::get_request_buffer();

    HAL_UART_Receive(
            &huart2, request_buffer.get_raw_buffer(), request_buffer.get_size(), 1000);

    return ProtoCodec::decode_request_container();
}

int SchedulerHandler::process_data_bus_request_content_response(
        const light_detector::RequestContainer& content) {
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

    data_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    data_bus_response_content.set_dataType(light_detector::DataType::Raw);

    uint16_t value = TSL2591X::read_lux();
    TSL2591X::invoke_lux_interrupt(LUX_LOW, LUX_HIGH);

    data_bus_response_content.set_value(value);
    data_bus_response_content.set_nonce(State::get_current_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_full_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    data_bus_response_content.set_dataType(light_detector::DataType::Full);

    uint32_t value = TSL2591X::read_full();

    data_bus_response_content.set_value(value);
    data_bus_response_content.set_nonce(State::get_current_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_infrared_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    data_bus_response_content.set_dataType(light_detector::DataType::Infrared);

    uint16_t value = TSL2591X::read_infrared();

    data_bus_response_content.set_value(value);
    data_bus_response_content.set_nonce(State::get_current_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_data_bus_request_content_of_visible_data_type_response(
        const light_detector::RequestContainer &content) {
    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::DataBusResponseContent data_bus_response_content;

    data_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    data_bus_response_content.set_dataType(light_detector::DataType::Visible);

    uint32_t value = TSL2591X::read_visible();

    data_bus_response_content.set_value(value);
    data_bus_response_content.set_nonce(State::get_current_response_nonce());

    response_container.set_dataBus(data_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_info_bus_request_content_response(
        const light_detector::RequestContainer& content) {
    auto info_bus_request_content =
            ProtoHelper::extract_info_bus_request_content(content);

    if (ProtoHelper::is_info_bus_request_content_of_gain_info_type(info_bus_request_content)) {

    }

    light_detector::ResponseContainer response_container;

    response_container.set_msgId(content.get_msgId());

    light_detector::InfoBusResponseContent info_bus_response_content;

    info_bus_response_content.set_deviceId(TSL2591X::get_device_id());
    info_bus_response_content.set_infoType(light_detector::InfoType::GetGain);


//    uint32_t value = TSL2591X::read_visible();
//
//    data_bus_response_content.set_value(value);
//    data_bus_response_content.set_nonce(State::get_current_response_nonce());

    response_container.set_infoBus(info_bus_response_content);

    return ProtoCodec::encode_response_container(response_container);
}

int SchedulerHandler::process_settings_bus_request_content_response(
        const light_detector::RequestContainer& content) {

}