/*
 * itemp_converter.h
 *
 * Created: 5/5/2020 2:36:15 PM
 *  Author: Dominika Kubicz
 */ 


#ifndef ITEMP_CONVERTER_H_
#define ITEMP_CONVERTER_H_

float convert_to_temperature(uint16_t value);
void switch_callback();
/*Following methods are in the header file for testing purposes*/
float to_celcius(uint16_t value);
float to_farenheit(uint16_t value);
float to_kelvin(uint16_t value);


#endif /* ITEMP_CONVERTER_H_ */