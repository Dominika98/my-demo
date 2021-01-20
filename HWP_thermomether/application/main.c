/*
 * thermometer.c
 *
 * Created: 5/4/2020 1:29:20 PM
 * Author : Dominika Kubicz
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../drivers/button/iext_ints_driver.h"
#include "../drivers/timer/itim_driver.h"
#include "../drivers/7segment/i7segment_driver.h"
#include "../drivers/sensor/itemp_sensor.h"
#include "../drivers/ADC/iADC_driver.h"
#include "converter/itemp_converter.h"

int main(void)
{
	init_ext_ints();
	init_7_segment();
	enable_sensor();
	init_tim1();
	init_adc();
	sei();
	/* Replace with your application code */
	while (1)
	{
	}
}

/*The ISR are implemented in driver files, because drivers are tested in Visual Studio*/