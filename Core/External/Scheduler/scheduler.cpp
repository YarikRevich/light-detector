#include "scheduler.h"

void Scheduler::handle_tick() {
    handle_request();
    handle_response();
}

void Scheduler::handle_status_check() {

}

void Scheduler::handle_request() {}() {
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == SET) {
        HAL_UART_Receive(&huart2, (int16_t *) &CAM_reso_W, 2, 1000);
    }
}

void Scheduler::handle_response() {}() {
    if (TSL2591X::is_configured()) {
        TSL2591X::read_lux();

        TSL2591X::invoke_lux_interrupt(50, 200);
//    	sprintf(buffer, "%d\r\n", TSL2591_ReadLux());
//    	TSL2591X_SetLuxInterrupt(50,200);
//    	printf("Infrared light: %d\r\n", TSL2591_ReadInfrared());
//    	printf("Visible light: %d\r\n", TSL2591_ReadVisible());
//    	printf("Full spectrum (IR + visible) light: %d\r\n\r\n", TSL2591X_ReadFull());
    }
}