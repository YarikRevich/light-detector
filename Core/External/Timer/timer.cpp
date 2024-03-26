#include "timer.h"

void Timer::handle() {
    TSL2591X::read_lux();

//    	sprintf(buffer, "%d\r\n", TSL2591_ReadLux());
//    	TSL2591X_SetLuxInterrupt(50,200);
//    	printf("Infrared light: %d\r\n", TSL2591_ReadInfrared());
//    	printf("Visible light: %d\r\n", TSL2591_ReadVisible());
//    	printf("Full spectrum (IR + visible) light: %d\r\n\r\n", TSL2591X_ReadFull());

}