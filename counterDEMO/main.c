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

int main(void)
{

	while (1)
	{
		
	}
}

