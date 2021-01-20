/*
 * LoRa_driver.c
 *
 * Created: 12/2/2020 10:01:22 AM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#include "../reading_struct.h"
#include "iLoRa_driver.h"
#include <ihal.h>
#include <lora_driver.h>

#define LED_TASK_PRIORITY 5

uint16_t temp;
uint16_t press;
QueueHandle_t xQueue;
struct reading temporary;


void initialize_lora(QueueHandle_t *ptrQueue){
	printf("Initializing\n");
	xQueue = *(QueueHandle_t*)ptrQueue;
	temp = 0;
	press = 0;
	
}

void lora_join(){
	
	lora_driver_returnCode_t rc;
	// Join the LoRaWAN
	uint8_t maxJoinTriesLeft = 10;
	
	do {
		rc = lora_driver_join(LORA_OTAA);
		printf("Join Network TriesLeft:%d >%s<\n", maxJoinTriesLeft, lora_driver_mapReturnCodeToText(rc));

		if ( rc != LORA_ACCEPTED)
		{
			// Wait 5 sec and lets try again
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else
		{
			break;
		}
	} while (--maxJoinTriesLeft);
	
}

void send_measurements(){
	
	// put data in the payload
	lora_driver_payload_t uplinkPayload;
		
	uplinkPayload.len = 4; // Length of the actual payload
	uplinkPayload.port_no = 2; // The LoRaWAN port no to sent the message to
	
	// read two queue entries
	for(int i=0; i<2;i++) {
		if(xQueueReceive(xQueue, (void*)&temporary, 5)){
			if(temporary.readingLabel==0){
				temp = temporary.value;
				uplinkPayload.bytes[0] = (temp>>8)&0b11;
				uplinkPayload.bytes[1] = temp & 0xFF;
				printf("Adding to payload temperature: %d\n", temp);
			} else if (temporary.readingLabel==1){
				press = temporary.value;
				uplinkPayload.bytes[2] = (press>>8)&0b11;
				uplinkPayload.bytes[3] = press & 0xFF;
				printf("Adding to payload pressure: %d\n", press);
			}
			} else {
			printf("Something went wrong while getting the data from the queue\n");
		}
	}
	
	lora_driver_returnCode_t ret;
	
	for(int i = 0; i<5; i++){
		ret = lora_driver_sendUploadMessage(false, &uplinkPayload);
		printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(ret));
		if(ret==LORA_MAC_RX || ret==LORA_MAC_TX_OK){
			break;
		}
	}
}