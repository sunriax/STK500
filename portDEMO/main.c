/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: portDEMO
 * Ver.: 1.0 Release
 * Type: Executeable
 * Text: Demo application for PORT
 *       interaction
 * -------------------------------------
 */

// Systemclock
#define F_CPU 12000000UL

// PORT settings
#define OUTPUT 0b00000100	// Set output PORT
#define INPUT 0b00000001	// Set input PORT
#define S1 (1<<0)			// Set input PIN0

// Include standard libraries
#include <avr/io.h>
#include <util/delay.h>

// Include hardware abstraction library
#include "../port/port.h"

int main(void)
{
	port_init(OUTPUT, 0xFF, 0x00);	// Initialize PORT4 (PORTC) as OUTPUT
	port_init(INPUT, 0x00, 0x0F);	// Initialize PORT1 (PORTA) as INPUT with pullup @ BIT(3:0)

	while (1)
	{	
		// Check if PIN S1 is pressed (negative logic)
		if(pin_read(INPUT, S1, 0) == 0xFF)
		{
			port_write(OUTPUT, 0x0F, 0);	// Write 0x0F to PORT4
			_delay_ms(10);			// Wait some time to eliminate bouncing
		}
		else
		{
			port_write(OUTPUT, 0xF0, 0);	// Write 0xF= to PORT4
			_delay_ms(10);				// Wait some time to eliminate bouncing
		}
	}
}

