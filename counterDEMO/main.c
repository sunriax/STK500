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
#define INPUT 0b00000001	// Set input PORT (PORTA)
#define S0 (1<<0)			// Set input PIN0 (PIN A0)
#define S1 (1<<1)			// Set input PIN1 (PIN A1)
#define S2 (1<<2)			// Set input PIN2 (PIN A2)
#define S3 (1<<3)			// Set input PIN3 (PIN A3)

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../port/port.h"
#include "../counter/counter.h"

volatile unsigned char counter;
extern unsigned char COUNTER_PRESCALER;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! Interrupt Service Routine for TIMER0 compare match !!!
// !!! This only works with ATMEL AVR (ATmega8/16/32).    !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Interrupt routine for overflow
// ISR(TIMER0_OVF_vect)
// {
//	 counter++;							// Increment counter variable
//	 port_write(OUTPUT, counter, 0);	// Write counter to OUTPUT port
// }

// Interrupt routine for compare match
ISR(TIMER0_COMP_vect)
{
	counter++;						// Increment counter variable
	port_write(OUTPUT, counter, 0);	// Write counter to OUTPUT port
}

int main(void)
{

	// Port setup
	port_init(OUTPUT, 0xFF, 0);		// Initialize PORT3 (PORTC) as OUTPUT
	port_init(INPUT, 0x00, 0x0F);	// Initialize PORT1 (PORTA) as INPUT with pullup @ BIT(3:0)

	// Counter Setup
	counter_init(0x05);		// Select F_CPU/1024 prescaler
	counter_limit(10);		// Set compare match to 220 (only necessary for compare match)

	while (1)
	{
		// If interrupt handler is disabled
		// if(counter_overflow() == 0xFF)
		// {
		//	 counter++;
		//	 port_write(OUTPUT, counter, 0);
		// }
		
		// If S0 on Megacard / PA0 on STK500 pressed (not pulled!!!)
		if(pin_read(INPUT, S0, 0) == 0xFF)
			counter_stop();			// Stop counter
		// If S1 on Megacard / PA1 on STK500 pressed (not pulled!!!)
		else if(pin_read(INPUT, S1, 0) == 0xFF)
			counter_start(0);		// Start counter @ last state
		// If S2 on Megacard / PA2 on STK500 pressed (not pulled!!!)
		else if(pin_read(INPUT, S2, 0) == 0xFF)
			counter_start(0x03);	// Start counter @ new state
		// If S3 on Megacard / PA3 on STK500 pressed (not pulled!!!)
		else if(pin_read(INPUT, S3, 0) == 0xFF)
			counter_reset();		// Reset counter
	}
}

