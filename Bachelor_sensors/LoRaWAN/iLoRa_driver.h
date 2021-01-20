/*
 * iLoRa_driver.h
 *
 * Created: 12/2/2020 10:00:50 AM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

#ifndef ILORA_DRIVER_H_
#define ILORA_DRIVER_H_

void initialize_lora(QueueHandle_t *ptrQueue);
void send_measurements();
void lora_join();


#endif /* ILORA_DRIVER_H_ */