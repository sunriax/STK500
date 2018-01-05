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
	// Port setup
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Actual there is no abstraction for the PORT setup !!!
	// !!! It will be integrated in future developments      !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DDRA = 0x00;	// Set PORTA as input
	DDRC = 0xFF;	// Set PORTC as output
	PORTA = 0x0F;	// Set PULLUPs at PORTA(3:0)
	PORTC = 0x00;	// Set PORTC to LOW
	
	// ADC Initialization
	adc_init();
 
    while (1) 
    {
		// If PA0 is pressed measure a single value on ADC channel 5 (Potentiometer on Megacard)
		if(!(PINA & (1<<PA0)))
		{
			adc_channel(5);	// Select channel 5
			
			while((PINA & (1<<PA1)) && (PINA & (1<<PA2)))
			{
				unsigned int single = adc_read();		// Read single ADC sample
				PORTC = (single>>2);					// Write data to PORTC (remove BIT 1:0)
			}
		}
		// If PA1 is pressed measure an average value on ADC channel 5 (Potentiometer on Megacard)
		else if(!(PINA & (1<<PA1)))
		{
			adc_channel(5);	// Select channel 5
			
			while((PINA & (1<<PA0)) && (PINA & (1<<PA2)))
			{
				unsigned int average = adc_average(20);	// Make average from 20 ADC samples
				PORTC = (average>>2);					// Write data to PORTC (remove BIT 1:0)
			}
		}
		// If PA2 is pressed measure a single value on ADC channel 6 (Temperature Sensor on Megacard)
		else if(!(PINA & (1<<PA2)))
		{
			adc_channel(6);	// Select channel 5
			
			while((PINA & (1<<PA0)) && (PINA & (1<<PA1)))
			{
				unsigned int temperature = adc_read();		// Read single ADC sample
				PORTC = temperature;						// Write data to PORTC (remove BIT 1:0)
			}
		}
		else
		{
			PORTC = 0xF0;	// Display that nothing is selected
		}
    }	// End of loop
}	// End of main
