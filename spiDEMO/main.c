/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: spi
 * Ver.: 1.0 Debug
 * Type: Executable
 * Text: Demo application for SPI
 *       transmission
 * -------------------------------------
 */

// Systemclock
#define F_CPU 16000000UL

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../spi/spi.h"

int main(void)
{	
	// SPI Initialization
	// SPI mode:      Master
	// SPI direction: MSB
	// SPI polarity:  LOW/offset
	// SPI clock:     F_CPU/2 (SPI2X=enabled)
	spi_init(0xFF, 0x00, 0x00, 0x00);
	
	// Port setup
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Actual there is no abstraction for the PORT setup !!!
	// !!! It will be integrated in future developments      !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DDRA = 0x00;	// Set PORTA to input
	DDRC = 0xFF;	// Set PORTC to output
	PORTA = 0x0F;	// Set PULLUP at PORTA (3:0)
	PORTC = 0x00;	// Set PORTC to LOW
	
    while (1) 
    {
		// This is a simple loopback mode (connect MOSI to MISO)
		// to check the function of the SPI bus. There are 4 Switches
		// connected to PORTA (3:0). If one or more switches are
		// active the status LEDs on PORTC should remain the status
		// of the switches. If the connection between MOSI and MISO
		// is removed the status LEDs should all be HIGH (active)
		// because of the pullup on MISO!!!
		PORTC = spi_transfer(~(((PINA<<4) & 0xF0) | (PINA & 0x0F)));
    }	// End of loop
}	// End of main

