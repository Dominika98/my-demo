/*
 * ADC_driver.c
 *
 * Created: 4/20/2020 4:32:17 PM
 *  Author: Dominika Kubicz
 */ 

#include "iADC_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../7segment/i7segment_driver.h"
#include "../../app/converter/itemp_converter.h"

static uint16_t result;

static uint8_t read;

void init_adc()
{
	//Set PK7 as input
	DDRK &= ~(_BV(PK7));
	//Choosing ADC14 channel (100111) and setting reference to AREF
	ADMUX |= _BV(REFS0) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
	ADCSRB |= _BV(MUX5);
	/** Enable ADC (ADEN), set free running mode (ADATE)
	enable interrupt (ADIE), set prescaler to 128**/
	ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
	// set ADC trigger selection to TIM1 compare match B
	ADCSRB |= _BV(ADTS2) | _BV(ADTS0);
	
	//start convertion
	ADCSRA |= _BV(ADSC);
}

//reading the converted value
ISR(ADC_vect)
{
	result = ADC;
	printfloat_7s(convert_to_temperature(result), 1);
}
