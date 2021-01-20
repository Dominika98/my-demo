/*
 * _7segment_driver.c
 *
 * Created: 3/30/2020 1:40:46 PM
 *  Author: Dominika Kubicz
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "i7segment_driver.h"
#include <stdbool.h>

static uint8_t digit_id;
static uint8_t digits[4];
static uint8_t dp; //this value holds the id of the digit that has to display the decimal point
static bool isNegative;

//used to clock rck
void clk_rck() {
	//set PB0 high
	PORTB |= _BV(PB0);
	//set PB0 low
	PORTB &= ~(_BV(PB0));
}

//displays error message
void error()
{
	digits[0] = 13;  	// no 13 gives led configuration to turn the digit off
	digits[1] = 11;	    // no 11 gives led configuration to display E
	digits[2] = 12;   	// no 12 gives led configuration to display r
	digits[3] = 12;
	dp = 5;             // decimal point off
}

//this function is used to change a number to an array of digits (for an uint)
void convert_uint_to_digits(uint16_t value)
{
	//show error if the number won't fit in the display
	if (value > 9999)
	{
		error();
	}
	else
	{
		//converting number to digits ex 123 to digits[] = [1, 2, 3]
		uint16_t number = value;
		for (uint8_t i = 3; i < 4; i--)
		{
			digits[i] = number % 10;
			number /= 10;
		}

		if (isNegative)
		{
			digits[0] = 10;		//no 10 gives led configuration to display a minus
		}
	}
}

void SPI_transmit(uint8_t value)
{
	/* Start transmission */
	SPDR = value;
	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)))
		;
	clk_rck();
}

void display(uint8_t number)
{
	uint8_t led_config = 0;
	//if the digit that is being displayed is the same digit as the one that is supposed to
	//display the decimal point then the dp led will be on
	if(!(digit_id==dp))
	{
		 //dp off
		 led_config = 1;
	}
	if(!((number == 2) | (number == 3) | (number == 4) | (number == 5) | (number == 6) | (number == 8) | (number == 9) | (number == 10) | (number == 11) | (number == 12)))
	{
		//g off
		led_config += 2;
	}
	if(!((number == 0) | (number == 4) | (number == 5) | (number == 6) | (number == 8) | (number == 9) | (number == 11)))
	{
		//f off
		led_config += 4;
	}
	if(!((number == 0) | (number == 2) | (number == 6) | (number == 8) | (number == 12) | (number == 11)))
	{
		//e off
		led_config += 8;
	}
	if(!((number == 0) | (number == 2) | (number == 3) | (number == 5) | (number == 6) | (number == 8) | (number == 9) | (number == 11)))
	{
		//d off
		led_config += 16;
	}
	if(!((number == 0) | (number == 1) | (number == 3) | (number == 4) | (number == 5) | (number == 6) | (number == 7) | (number == 8) | (number == 9)))
	{
		//c off
		led_config += 32;
	}
	if(!((number == 0) | (number == 1) | (number == 2) | (number == 3) | (number == 4) | (number == 7) | (number == 8) | (number == 9)))
	{
		//b off
		led_config += 64;
	}
	if(!((number == 0) | (number == 2) | (number == 3) | (number == 5) | (number == 6) | (number == 7) | (number == 8) | (number == 9) | (number == 11)))
	{
		//a off
		led_config += 128;
	}
	SPI_transmit(led_config);
}

void display_digit(uint8_t digit)
{
	display(digits[digit]);
	//switching between the digits
	switch(digit)
	{
		case 1:
		PORTF |= _BV(PF0);
		PORTF &= ~(_BV(PF1));
		break;
		case 2:
		PORTF |= _BV(PF1);
		PORTF &= ~(_BV(PF2));
		break;
		case 3:
		PORTF |= _BV(PF2);
		PORTF &= ~(_BV(PF3));
		break;
		default:
		PORTF |= _BV(PF3);
		PORTF &= ~(_BV(PF0));
		break;
	}
}

void init_tim5()
{
	//enable Tim5 Output Compare Match Interrupt
	TIMSK5 |= _BV(OCIE5A);

	//set CTC mode
	//OCR5AH = 12499
	OCR5AH = 0b00110000;
	OCR5AL = 0b11010011;
	TCCR5B |= _BV(WGM52); //change top value of OCR5A

	//don't set up the prescaler so the timer doesn't start yet
	TCCR5B &= ~(_BV(CS51) | _BV(CS50));
}

void init_SPI()
{
	/* Enable SPI, Master, set clock rate fck/16*/
	SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(DORD);
}

void init_7_segment()
{
	// set direction for SI, SCK, RCK, D1-D4 to output
	DDRB = 0x07;
	DDRF = 0x0F;
	// set all pins low
	PORTB = 0x00;
	PORTF = 0x0F;
	//initialize values
	digit_id = 0;
	digits[0] = 0;
	digits[1] = 0;
	digits[2] = 0;
	digits[3] = 0;
	dp = 0;
	
	init_tim5();
	init_SPI();
}

void printint_7s(uint16_t value)
{
	//don't display decimal point (the dp will never be the same as the current digit ID)
	dp = 5;
	isNegative = false;
	convert_uint_to_digits(value);
	//start the timer, prescaler 1
	TCCR5B |= _BV(CS50);
}

void convert_float_to_digits(float value, uint8_t no_of_decimals)
{
	//by default it's positive
	isNegative = false;
	//temporary holder for the value
	uint16_t no = 0;
	if(value < 0)
	{
		//overwrite to true if negative
		isNegative = true;
	}
	//show error when the number won't fit in the display
	if ((no_of_decimals > 3 && (!isNegative)) || (no_of_decimals == 3 && value > 9.999 && (!isNegative)) || (no_of_decimals == 2 && value > 99.99 && (!isNegative)) || 
		(no_of_decimals == 1 && value > 999.9 && (!isNegative)) || (no_of_decimals > 2 && isNegative) || (no_of_decimals == 2 && value < -9.99  && isNegative)
		|| (no_of_decimals == 1 && value < -99.9  && isNegative))
	{
		error();
	}
	else if(no_of_decimals == 0)
	{
		//turn off decimal point
		dp=5; 
		if(isNegative)
		{
			//switch to positive
			no = (uint16_t) (value*(-1));
		}
		else
		{
			no = (uint16_t) value;
		}
		convert_uint_to_digits(no);
	}
	else
	{
		//switch the float to an integer and set the proper decimal point
		switch (no_of_decimals)
		{
			case 1:
			dp = 2;
			no = 10*value;
			break;
			case 2:
			dp = 1;
			no = 100*value;
			break;
			case 3:
			dp = 0;
			no = 1000*value;
			break;
		}
		if(isNegative)
		{
			//switch to positive
			no = no*(-1);
		}
		convert_uint_to_digits(no);
	}
	
}

void printfloat_7s(float value, uint8_t no_of_decimals)
{
	convert_float_to_digits(value, no_of_decimals);
	//start the timer, prescaler 1
	TCCR5B |= _BV(CS50);
}

//interrupt handler
ISR(TIMER5_COMPA_vect)
{
	display_digit(digit_id);
	digit_id++;
	digit_id = digit_id%4;
}