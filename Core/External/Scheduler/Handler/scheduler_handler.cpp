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

                return SchedulerHandler::process_data_bus_request_content_response(
                        ProtoHelper::extract_data_bus_request_content(content));
            } else if (ProtoHelper::is_info_bus_request_container(content)) {

                return SchedulerHandler::process_info_bus_request_content_response(
                        ProtoHelper::extract_info_bus_request_content(content));
            } else if (ProtoHelper::is_settings_bus_request_container(content)) {

                return SchedulerHandler::process_settings_bus_request_content_response(
                        ProtoHelper::extract_settings_bus_request_content(content));
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
        const light_detector::DataBusRequestContent& content) {
    if (ProtoHelper::is_data_bus_request_content_of_raw_data_type(content)) {

        SchedulerHandler::process_data_bus_request_content_of_raw_data_type_response(content);
    } else if (ProtoHelper::is_data_bus_request_content_of_full_data_type(content)) {

    } else if (ProtoHelper::is_data_bus_request_content_of_infrared_data_type(content)) {

    } else if (ProtoHelper::is_data_bus_request_content_of_visible_data_type(content)) {

    }




//    	printf("Infrared light: %d\r\n", TSL2591_ReadInfrared());
//    	printf("Visible light: %d\r\n", TSL2591_ReadVisible());
//    	printf("Full spectrum (IR + visible) light: %d\r\n\r\n", TSL2591X_ReadFull());
//    }
}

int SchedulerHandler::process_data_bus_request_content_of_raw_data_type_response(
        const light_detector::DataBusRequestContent &content) {
    light_detector::DataBusResponseContent data_bus_response_content;


    TSL2591X::read_lux();
    TSL2591X::invoke_lux_interrupt(50, 200);
}

int SchedulerHandler::process_info_bus_request_content_response(
        const light_detector::InfoBusRequestContent& content) {

}

int SchedulerHandler::process_settings_bus_request_content_response(
        const light_detector::SettingsBusRequestContent& content) {

}