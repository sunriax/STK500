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

// PORT settings
#define OUTPUT 0b00000100	// Set output PORT (PORTC)
#define INPUT 0b00000001	// Set input PORT (PORTA)

// Systemclock
#define F_CPU 16000000UL

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../port/port.h"
#include "../spi/spi.h"

int main(void)
{	
	// Port setup
	port_init(OUTPUT, 0xFF, 0x00);	// Initialize PORT4 (PORTC) as OUTPUT
	port_init(INPUT, 0x00, 0x0F);	// Initialize PORT1 (PORTA) as INPUT with pullup @ BIT(3:0)
	
	// SPI Initialization
	// SPI mode:      Master
	// SPI direction: MSB
	// SPI polarity:  LOW/offset
	// SPI clock:     F_CPU/2 (SPI2X=enabled)
	spi_init(0xFF, 0x00, 0x00, 0x00);
	
    while (1) 
    {
		// This is a simple loopback mode (connect MOSI to MISO)
		// to check the function of the SPI bus. There are 4 Switches
		// connected to PORTA (3:0). If one or more switches are
		// active the status LEDs on PORTC should remain the status
		// of the switches. If the connection between MOSI and MISO
		// is removed the status LEDs should all be HIGH (active)
		// because of the pullup on MISO!!!
		unsigned char data = spi_transfer(~((((pin_status(INPUT))<<4) & 0xF0) | ((pin_status(INPUT)) & 0x0F)));
		
		port_write(OUTPUT, data, 0);	// Write received data to output
    }	// End of loop
}	// End of main

