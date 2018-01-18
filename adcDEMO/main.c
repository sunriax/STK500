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
#include "../adc/adc.h"

int main(void)
{	
	// Port setup
	port_init(OUTPUT, 0xFF, 0x00);	// Initialize PORT4 (PORTC) as OUTPUT
	port_init(INPUT, 0x00, 0x0F);	// Initialize PORT1 (PORTA) as INPUT with pullup @ BIT(3:0)
	
	// ADC Initialization
	adc_init();
 
    while (1) 
    {
		// If PA0 is pressed measure a single value on ADC channel 5 (Potentiometer on Megacard)
		if(pin_read(INPUT, S0, 0) == 0xFF)
		{
			adc_channel(5);	// Select channel 5
			
			// Quit if an other button is pressed
			while((pin_read(INPUT, S1, 1) == 0xFF) && (pin_read(INPUT, S2, 1) == 0xFF))
			{
				unsigned int single = adc_read();		// Read single ADC sample
				port_write(OUTPUT, (single>>2), 0);		// Write data to PORT4 (remove BIT 1:0)
			}
		}
		// If PA1 is pressed measure an average value on ADC channel 5 (Potentiometer on Megacard)
		else if(pin_read(INPUT, S1, 0) == 0xFF)
		{
			adc_channel(5);	// Select channel 5
			
			// Quit if an other button is pressed
			while((pin_read(INPUT, S0, 1) == 0xFF) && (pin_read(INPUT, S2, 1) == 0xFF))
			{
				unsigned int average = adc_average(20);	// Make average from 20 ADC samples
				port_write(OUTPUT, (average>>2), 0);	// Write data to PORT4 (remove BIT 1:0)
			}
		}
		// If PA2 is pressed measure a single value on ADC channel 6 (Temperature Sensor on Megacard)
		else if(pin_read(INPUT, S2, 0) == 0xFF)
		{
			adc_channel(6);	// Select channel 5
			
			// Quit if an other button is pressed
			while((pin_read(INPUT, S0, 1) == 0xFF) && (pin_read(INPUT, S1, 1) == 0xFF))
			{
				unsigned int temperature = adc_read();		// Read single ADC sample
				port_write(OUTPUT, temperature, 0);			// Write data to PORT4 (remove BIT 1:0)
			}
		}
		else
		{
			port_write(OUTPUT, 0xF0, 0);	// Display that nothing is selected
		}
    }	// End of loop
}	// End of main
