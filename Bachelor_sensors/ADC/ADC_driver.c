/*
 * ADC_driver.c
 *
 * Created: 11/18/2020 3:27:55 PM
 * Author: Dominika Kubicz
 * Project: Herning Vand Reduction of Supervision
 */ 

#include "iADC_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <display_7seg.h>

/**Since both task need to share the ADC there
is a need for semaphore, so they don't overlap**/
// define semaphore handle
SemaphoreHandle_t xADCSemaphore;

int *value;

void init_adc()
{
	if ( xADCSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xADCSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xADCSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xADCSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}
	
	//Set PK0 and PK1 as input
	DDRK &= (~(_BV(PK0)) & ~(_BV(PK1)));
	
	/** Enable ADC (ADEN), set free running mode (ADATE)
	enable interrupt (ADIE), set prescaler to 128**/
	ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
}

void start_temp_read(int *ptrTemp)
{
	xSemaphoreTake(xADCSemaphore, portMAX_DELAY);
	value = ptrTemp;
	//Choosing ADC8 channel (100000);
	ADMUX &= ~(_BV(MUX0));
	ADMUX |= _BV(REFS0);
	ADCSRB |= _BV(MUX5);
	//start conversion
	ADCSRA |= _BV(ADSC);
	printf("Temperature conversion started\n");
}

void start_pressure_read(int *ptrPress)
{
	xSemaphoreTake(xADCSemaphore, portMAX_DELAY);
	value = ptrPress;
	//Choosing ADC9 channel (100001);
	ADMUX |= _BV(REFS0) | _BV(MUX0);
	ADCSRB |= _BV(MUX5);
	//start conversion
	ADCSRA |= _BV(ADSC);
	printf("Pressure conversion started\n");
}

//reading the converted value
ISR(ADC_vect)
{
	*value = ADC;
	printf("ADC converted value: %d\n", *value);
	vTaskDelay(2);
	xSemaphoreGive(xADCSemaphore);
}
