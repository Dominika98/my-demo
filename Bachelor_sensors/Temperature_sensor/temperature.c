/*
 * temperature.c
 *
 * Created: 11/25/2020 12:33:07 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#include "../ADC/iADC_driver.h"
#include "../reading_struct.h"

#define TEMP_LABEL 0

QueueHandle_t xQueue;
int adc_read;

void initialize_temp(QueueHandle_t *ptrQueue)
{
	xQueue = *(QueueHandle_t*)ptrQueue;
	adc_read = -1;
}

void send_temp_to_queue()
{
	struct reading measurmentTemp;
	
	measurmentTemp.readingLabel = TEMP_LABEL;
	measurmentTemp.value = adc_read;
	
	if(!xQueueSend(xQueue, (void*)&measurmentTemp, 100)) {
		printf("Failed to send temperature to the queue\n");
		} else {
		printf("Temperature added to queue\n");
	};
	
	//reset value
	adc_read = -1;
}

void measure_temp()
{
	start_temp_read(&adc_read);
	
	//wait for the ADC to read the value
	while(adc_read==-1){
		;
	}
	send_temp_to_queue();
}