/*
 * pressure.c
 *
 * Created: 11/25/2020 12:35:09 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#include "../ADC/iADC_driver.h"
#include "../reading_struct.h"
#include "ipressure.h"

#define PRESS_LABEL 1

QueueHandle_t xQueue;
int adc_reading;

void initialize_pressure(QueueHandle_t *ptrQueue)
{
	xQueue = *(QueueHandle_t*)ptrQueue;
	adc_reading = -1;
}

void send_press_to_queue()
{
	struct reading measurmentPress;
	
	measurmentPress.readingLabel = PRESS_LABEL;
	measurmentPress.value = adc_reading;
	
	if(!xQueueSend(xQueue, (void*)&measurmentPress, 100)) {
		printf("Failed to send pressure to the queue\n");
		} else {
		printf("Pressure added to queue\n");
		vTaskDelay(100); // let other sensors write their data to the queue
	};
	adc_reading = -1;
}

void measure_pressure()
{
	start_pressure_read(&adc_reading);
	
	//wait for the ADC to read the value
	while(adc_reading==-1){
		;
	}
	send_press_to_queue();
}