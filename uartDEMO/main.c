/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: uart
 * Ver.: 1.0 Debug
 * Type: Executable
 * Text: Demo application for UART
 *       Transmission
 * -------------------------------------
 */

// Systemclock
#define F_CPU 12000000UL

// PORT settings
#define OUTPUT 0b00000100	// Set output PORT (PORTC)
#define INPUT 0b00000001	// Set input PORT (PORTA)

// Include standard libraries
#include <avr/io.h>
#include <util/delay.h>

// Include hardware abstraction library
#include "../port/port.h"
#include "../uart/uart.h"

int main(void)
{
	// Port setup
	port_init(OUTPUT, 0xFF, 0x00);	// Initialize PORT4 (PORTC) as OUTPUT
	port_init(INPUT, 0x00, 0x0F);	// Initialize PORT1 (PORTA) as INPUT with pullup @ BIT(3:0)
	
	// UART Initialization
	// Databits: 8
	// Parity:   Even
	// Stopbits: 1
	uart_init(8, 'E', 1);
	
	unsigned char data;	// Databyte

	while (1)
	{	
		// This is a simple loopback mode (connect TXD to RXD)
		// to check the function of the UART. There are 4 Switches
		// connected to PORTA (3:0). If one or more switches are
		// active the status LEDs on PORTC should remain the status
		// of the switches. If the connection between RXD and TXD
		// is removed the status LEDs should all be LOW (inactive)!!!
		
		// Send databyte (PINA doubled) over UART
		uart_setchar(~((((pin_status(INPUT))<<4) & 0xF0) | ((pin_status(INPUT)) & 0x0F)));
		_delay_ms(2);
		
		// Receive databyte over UART
		uart_getchar(&data, 0x00);
		_delay_ms(2);
		
		port_write(OUTPUT, data, 0);	// Write received data to output
		
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// !!! All other UART functions will be used at the module !!!
		// !!! repository on SUNriaX Github                        !!!
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }	// End of loop
}	// End of main
