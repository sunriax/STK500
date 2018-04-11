/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: counter
 * Ver.: 1.0 Debug
 * Type: Executable
 * Text: Demo application for numeric
 *       counting operations
 * -------------------------------------
 */

// PORT settings
#define OUTPUT 0b00000100	// Set output PORT (PORTC)

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../port/port.h"
#include "../counter/counter.h"

volatile unsigned char counter;

ISR(TIMER0_COMP_vect)
{
	counter++;
	port_write(OUTPUT, counter, 0);
}

int main(void)
{

	port_init(OUTPUT, 0xFF, 0);

	counter_init(0x01);
	counter_limit(200);

	while (1)
	{
		// If interrupt handler is disabled
		/*
		if(counter_overflow() == 0xFF)
		{
			counter++;
			port_write(OUTPUT, counter, 0);
		}
		*/
	}
}

