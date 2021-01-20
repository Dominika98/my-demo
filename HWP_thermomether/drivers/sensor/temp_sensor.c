/*
 * temp_sensor.c
 *
 * Created: 5/4/2020 3:16:58 PM
 *  Author: Dominika Kubicz
 */ 

#include <stdio.h>
#include <avr/io.h>

void enable_sensor()
{
	//Set PG0 as input
	DDRG &= ~(_BV(PG0));
	//enable sensor
	PORTG |= _BV(PG0);
}