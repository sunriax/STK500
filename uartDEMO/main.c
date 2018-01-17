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

// Include standard libraries
#include <avr/io.h>
#include <util/delay.h>

// Include hardware abstraction library
#include "../uart/uart.h"

int main(void)
{
	// Port setup
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Actual there is no abstraction for the PORT setup !!!
	// !!! It will be integrated in future developments      !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DDRA = 0x00;	// Set PORTA to input
	DDRC = 0xFF;	// Set PORTC to output
	PORTA = 0x0F;	// Set PULLUP at PORTA (3:0)
	PORTC = 0x00;	// Set PORTC to LOW
	
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
		uart_setchar(~(((PINA<<4) & 0xF0) | (PINA & 0x0F)));
		_delay_ms(2);
		
		// Receive databyte over UART
		uart_getchar(&data, 0x00);
		_delay_ms(2);
		
		PORTC = data;	// Write received data to PORTC
		
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// !!! All other UART functions will be used at the module !!!
		// !!! repository on SUNriaX Github                        !!!
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }	// End of loop
}	// End of main
