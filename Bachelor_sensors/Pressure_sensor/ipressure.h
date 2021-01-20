/*
 * ipressure.h
 *
 * Created: 11/25/2020 12:39:33 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#ifndef IPRESSURE_H_
#define IPRESSURE_H_

void initialize_pressure(QueueHandle_t *ptrQueue);
void measure_pressure();
void send_press_to_queue();


#endif /* IPRESSURE_H_ */