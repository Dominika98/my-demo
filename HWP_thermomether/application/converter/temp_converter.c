/*
 * temp_converter.c
 *
 * Created: 5/5/2020 2:36:33 PM
 *  Author: Dominika Kubicz
 */ 

#include <stdio.h>
#include <avr/io.h>

static float (*cb)(uint16_t value);
//this is the value of voltage for one step for the ADC converter
#define VOLTAGE 4.883
static uint8_t case_id = 0;
static float temperature = 0;

//returns the temperature in celcius degrees
float to_celcius(uint16_t value)
{
	temperature = (value*VOLTAGE)/40;
	return temperature;
}

//returns the temperature in farenheit degrees
float to_farenheit(uint16_t value)
{
	temperature = (to_celcius(value) * 1.8) + 32;
	return temperature;
}

//returns the temperature in kelvin degrees
float to_kelvin(uint16_t value)
{
	temperature = to_celcius(value) + 273.15;
	return temperature;
}

//changes the callback which will convert the ADC value
//to a temperature, so the unit changes
void switch_callback()
{
	switch(case_id)
	{
		case 0:
		cb = to_celcius;
		break;
		case 1:
		cb = to_farenheit;
		break;
		case 2:
		cb = to_kelvin;
		break;
	}
		case_id++;
		case_id = case_id%3;
}

//converts to temperature, depending which callback is set
//the unit might be different
float convert_to_temperature(uint16_t value)
{
	return cb(value);
}