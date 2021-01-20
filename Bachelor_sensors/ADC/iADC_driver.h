/*
 * iADC_driver.h
 *
 * Created: 11/18/2020 3:26:23 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#ifndef IADC_DRIVER_H_
#define IADC_DRIVER_H_

void init_adc();
void start_temp_read(int *ptrTemp);
void start_pressure_read(int *ptrPress);



#endif /* IADC_DRIVER_H_ */