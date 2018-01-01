/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: adc
 * Ver.: 1.0 Debug
 * Type: Executable
 * Text: Demo application for A/D
 *       converstion
 * -------------------------------------
 */

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../adc/adc.h"

int main(void)
{	
	DDRC = 0xFF;	// Set PORTC as output
	
	adc_init();		// Initialize A/D Converter
	adc_channel(5);	// Select channel 5
 
    while (1) 
    {
		unsigned int test = adc_read();	// Read data from channel 5
		PORTC = (test>>2);				// Write data to PORTC
	}
}

