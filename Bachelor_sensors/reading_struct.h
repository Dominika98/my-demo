/*
 * reading_struct.h
 *
 * Created: 11/25/2020 2:26:51 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 


#ifndef READING_STRUCT_H_
#define READING_STRUCT_H_

#include <stdio.h>


struct reading {
	int readingLabel; // e.g. 0 - temp, 1 - pressure
	uint16_t value; // the ADC reading
};


#endif /* READING_STRUCT_H_ */