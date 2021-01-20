/*
 * iRTOS_driver.h
 *
 * Created: 12/12/2020 2:05:19 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 


#ifndef IRTOS_DRIVER_H_
#define IRTOS_DRIVER_H_

#include <stdbool.h>

void intialize_timer();
void consumeFlag();
bool getTimeout();

#endif /* IRTOS_DRIVER_H_ */