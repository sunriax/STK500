/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: irq
 * Ver.: 1.0 Debug
 * Type: Executable
 * Text: Demo application for irq
 *       handling
 * -------------------------------------
 */

// PORT settings
#define OUTPUT 0b00000100	// Set output PORT (PORTC)
#define INPUT 0b00001000	// Set input PORT (PORTD)
#define INTPIN (1<<PD2)		// Set interrupt PIN (INT0)

// Include hardware abstraction library
#include "../port/port.h"
#include "../irq/irq.h"

// Global variable for counting
volatile unsigned char counter;

// Interrupt routine for external interrupt (INT0)
ISR(INT0_vect)
{
	counter++;						// Increment counter variable
	port_write(OUTPUT, counter, 0);	// Write counter to OUTPUT port
}

int main(void)
{
	// Port setup
	port_init(OUTPUT, 0xFF, 0);		// Initialize PORT3 (PORTC) as OUTPUT
	port_init(INPUT, 0x00, 0x04);	// Initialize PORT4 (PORTD) as INPUT with pullup @ BIT(2:2)

	// External interrupt (INT0) setup
	irq_init(0x03);	// Set execution to state changing

	while (1)
	{
		// If interrupt handler is disabled
		// if(irq_status() == 0xFF)
		// {
		//	 counter++;
		//	 port_write(OUTPUT, counter, 0);
		// }	
	}
}

