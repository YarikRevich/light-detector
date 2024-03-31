#include "scheduler.h"

void Scheduler::handle_tick() {
    if (handle_request() != EXIT_SUCCESS) {
        Indicator::toggle_invalid_request();

        return;
    }

    if (handle_response() != EXIT_SUCCESS) {
        // TODO: indicate response processing error;
    }
}

int Scheduler::handle_request() {
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == SET) {
        auto buffer = ProtoCodec::getRequestBuffer();

        HAL_UART_Receive(&huart2, buffer.get_raw_buffer(), buffer.get_size(), 1000);



        State::getRequestContainerSequence().add();
    }

    return EXIT_SUCCESS;


    if(reply_msg.deserialize(read_buffer) == ::EmbeddedProto::Error::NO_ERRORS) {
        switch(reply_msg.get_which_type())
        {
            case demo::reply::FieldNumber::A:
            {
                // Do something with the data.
                uint32_t ans_a = reply_msg.a().x() + reply_msg.a().y() + reply_msg.a().z();
                break;
            }

            case demo::reply::FieldNumber::B:
            {
                // Do something with the data.
                uint32_t ans_b = reply_msg.b().u() * reply_msg.b().v() * reply_msg.b().w();
                break;
            }

            default:
                break;
        }
    }


    return EXIT_SUCCESS;
}

void Scheduler::handle_response() {
//    if (TSL2591X::is_configured()) {
//        TSL2591X::read_lux();
//
//        TSL2591X::invoke_lux_interrupt(50, 200);
//    	sprintf(buffer, "%d\r\n", TSL2591_ReadLux());
//    	TSL2591X_SetLuxInterrupt(50,200);
//    	printf("Infrared light: %d\r\n", TSL2591_ReadInfrared());
//    	printf("Visible light: %d\r\n", TSL2591_ReadVisible());
//    	printf("Full spectrum (IR + visible) light: %d\r\n\r\n", TSL2591X_ReadFull());
//    }
}

void Scheduler::handle_status_check() {

}