/*
 * key_driver.c
 *
 * Created: 3/21/2020 2:28:10 PM
 *  Author: Dominika Kubicz
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "iext_ints_driver.h"
#include "../../app/converter/itemp_converter.h"

void init_ext_ints()
{
    //set PD3 (INT3) as input with pull-up
    DDRD &= ~(_BV(PD3));
    PORTD |= _BV(PD3);

    //set interrupt in falling edge (interrupt scene control)
    EICRA &= ~(_BV(ISC30));
    EICRA |= _BV(ISC31);

    //enable interrupt mask INT3
    EIMSK |= _BV(INT3);
	
	//initialize callback
	switch_callback();
}

// key 8 interrupt handler
ISR(INT3_vect)
{
    switch_callback();
}

