/*
 * i7segment_driver.h
 *
 * Created: 3/30/2020 1:40:26 PM
 *  Author: Dominika Kubicz
 */ 


#ifndef I7SEGMENT_DRIVER_H_
#define I7SEGMENT_DRIVER_H_

void init_7_segment();
void printint_7s(uint16_t value);
void printfloat_7s(float value, uint8_t no_of_decimals);


#endif /* I7SEGMENT_DRIVER_H_ */