/*
 * tim_driver.c
 *
 * Created: 3/21/2020 2:28:40 PM
 *  Author: Dominika Kubicz
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "itim_driver.h"

//setting up tim1 to throw interrupts every 1sec
void init_tim1()
{
	//enable Tim4 Output Compare Match Interrupt
	TIMSK1 |= _BV(OCIE1B);
	
	//set CTC mode
	//set Foc4a to 1Hz
	//OCR4AH = 62499
	OCR1BH = 0b11110100;
	OCR1BL = 0b00100011;
	
	//start the timer (psc=256)
	TCCR1B |= _BV(CS12);
}

//ISR to make the counter start counting again from 0
ISR(TIMER1_COMPB_vect)
{
	//restart the counter
	TCNT1H = 0;
	TCNT1L = 0;
}