/*
 * itemperature.h
 *
 * Created: 11/25/2020 12:32:48 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 


#ifndef ITEMPERATURE_H_
#define ITEMPERATURE_H_

void initialize_temp(QueueHandle_t *ptrQueue);
void measure_temp();
void send_temp_to_queue();


#endif /* ITEMPERATURE_H_ */