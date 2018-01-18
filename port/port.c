/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: port
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing port
 *       and logic
 * -------------------------------------
 */

#include "port.h"

//	+---------------------------------------------------------------+
//	|						PORT initialization						|
//	+---------------------------------------------------------------+
unsigned char port_init(unsigned char port, unsigned char direction, unsigned char pullup)
{
	// Switch to selected port
	switch(port)
	{
		// If port bit(s) is/are set to input (LOW) pullup values will take effect
		case 0b00000001	:	DDRA = direction;	PORTA = ~(direction) & pullup;	break;	// Setup PORTA direction (input/output)
		case 0b00000010	:	DDRB = direction;	PORTB = ~(direction) & pullup;	break;	// Setup PORTB direction (input/output)
		case 0b00000100	:	DDRC = direction;	PORTC = ~(direction) & pullup;	break;	// Setup PORTC direction (input/output)
		case 0b00001000	:	DDRD = direction;	PORTD = ~(direction) & pullup;	break;	// Setup PORTD direction (input/output)
		default	:	return 0xFF;										break;	// If wrong port setup fails
	}
	return 0x00; // Port setup done
}

//	+---------------------------------------------------------------+
//	|						PORT disable							|
//	+---------------------------------------------------------------+
unsigned char port_disable(unsigned char port)
{
	// This will set selected port to input (no pullup)
	if(port_init(port, 0x00, 0x00) != 0)
		return 0xFF;
	return 0x00;
	
	// Why a disable function returns an unsigned char:
	// If the port is driven bidirectional it could be
	// shorten up/down to other devices because the function
	// was called, but it tool no effect. So if the function
	// fails it is necessary to do an error handling
}

//	+---------------------------------------------------------------+
//	|						PORT write								|
//	+---------------------------------------------------------------+
unsigned char port_write(unsigned char port, unsigned char data, unsigned char logic)
{
	// Switch to selected port
	switch(port)
	{
		// If port bit(s) is/are set to input (LOW) pullup values will take effect
		case 0b00000001	:	if (logic == 1)		// Check if PORT or is selected
								PORTA |= DDRA & data;
							else if(logic == 2)	// Check if PORT and is selected
								PORTA &= DDRA & data;
							else
								PORTA = DDRA & data;	// Check if PORT direct is selected
							break;
		case 0b00000010	:	if (logic == 1)		// Check if PORT or is selected
								PORTB |= DDRB & data;
							else if(logic == 2)	// Check if PORT and is selected
								PORTB &= DDRB & data;
							else
								PORTB = DDRB & data;	// Check if PORT direct is selected
							break;
		case 0b00000100	:	if (logic == 1)		// Check if PORT or is selected
								PORTC |= DDRC & data;
							else if(logic == 2)	// Check if PORT and is selected
								PORTC &= DDRC & data;
							else
								PORTC = DDRC & data;	// Check if PORT direct is selected
							break;
		case 0b00001000	:	if (logic == 1)		// Check if PORT or is selected
								PORTD |= DDRD & data;
							else if(logic == 2)	// Check if PORT and is selected
								PORTD &= DDRD & data;
							else
								PORTD = DDRD & data;	// Check if PORT direct is selected
							break;
		default	:	return 0xFF;			break;	// If wrong port data write fails
	}
	return 0x00; // Port write done
}

//	+---------------------------------------------------------------+
//	|						PIN read								|
//	+---------------------------------------------------------------+
unsigned char pin_read(unsigned char pin, unsigned char bit, unsigned char logic)
{
	// Switch to selected port
	switch(pin)
	{
		// If port bit(s) is/are set to input (LOW) pullup values will take effect
		case 0b00000001	:	if(logic != 0x00)	// If positive logic
							{
								// Check if selected bit is set
								if(PINA & (bit))
									return 0xFF;
							}
							else
							{
								// Check if selected bit is not set
								if(!(PINA & (bit)))
									return 0xFF;
							}
							break;
		case 0b00000010	:	if(logic != 0x00)	// If positive logic
							{
								// Check if selected bit is set
								if(PINB & (bit))
								return 0xFF;
							}
							else
							{
								// Check if selected bit is not set
								if(!(PINB & (bit)))
								return 0xFF;
							}
							break;	
		case 0b00000100	:	if(logic != 0x00)	// If positive logic
							{
								// Check if selected bit is set
								if(PINC & (bit))
								return 0xFF;
							}
							else
							{
								// Check if selected bit is not set
								if(!(PINC & (bit)))
								return 0xFF;
							}
							break;	
		case 0b00001000	:	if(logic != 0x00)	// If positive logic
							{
								// Check if selected bit is set
								if(PIND & (bit))
								return 0xFF;
							}
							else
							{
								// Check if selected bit is not set
								if(!(PIND & (bit)))
								return 0xFF;
							}
							break;
		default	:	return 0xF0;	break;	// If wrong pin data check fails
	}
	return 0x00; // Port check done
}

//	+---------------------------------------------------------------+
//	|						PIN status								|
//	+---------------------------------------------------------------+
unsigned char pin_status(unsigned char pin)
{
	// Switch to selected port
	switch(pin)
	{
		// If port bit(s) is/are set to input (LOW) pullup values will take effect
		case 0b00000001	:	return PINA;	break;	// Return PINA status
		case 0b00000010	:	return PINB;	break;	// Return PINB status
		case 0b00000100	:	return PINC;	break;	// Return PINC status
		case 0b00001000	:	return PIND;	break;	// Return PIND status
		default	:	return 0xF0;	break;	// If wrong pin data check fails
	}
	return 0x00; // Port check done
}