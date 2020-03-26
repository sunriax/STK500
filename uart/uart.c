/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Function file for uart library
 * -----------------------------------------
 */

#include "uart.h"

//	+---------------------------------------------------------------+
//	|					UART initialization							|
//	+---------------------------------------------------------------+
void uart_init(unsigned char datasize, unsigned char parity, unsigned char stopbits)	{

	// Baudrate calculation (depends on sample setting)
	#ifdef U2XEN
		UCSRA = (1<<U2X);											// Double Speed Mode activated
		UBRRH = (((unsigned int)(F_CPU / (8 * (BAUD - 1))))>>8);	// Calculate UBRR factor
		UBRRL = (unsigned int)(F_CPU / (8 * (BAUD - 1)));
	#else
		UCSRA = ~(1<<U2X);											// Double Speed Mode deactivated
		UBRRH = (((unsigned int)(F_CPU / (16 * (BAUD - 1))))>>8);	// Calculate UBRR factor
		UBRRL = (unsigned int)(F_CPU / (16 * (BAUD - 1)));
	#endif

	unsigned char SETREG = (1<<URSEL);	// Activate URSEL (normally in register UCSRC)
	
	// Setup datasize
	switch(datasize)
	{
		case 5	: SETREG &= ~((1<<UCSZ2) | (1<<UCSZ1) | (1<<UCSZ0));	break;	// 5 Bit mode
		case 6	: SETREG |= (1<<UCSZ0);								break;	// 6 Bit mode
		case 7	: SETREG |= (1<<UCSZ1);								break;	// 7 Bit mode
		case 9	: SETREG |= (1<<UCSZ2) | (1<<UCSZ1) | (1<<UCSZ0);		break;	// 9 Bit mode
		default	: SETREG |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);		break;	// 8 Bit mode (Standard)
	}
	
	// Setup paritybit
	switch(parity)
	{
		case 'E' :	SETREG |= (1<<UPM1);				break;	// even parity
		case 'O' :	SETREG |= (1<<UPM1) | (1<<UPM0);	break;	// odd parity
		default  :  SETREG &= ~((1<<UPM1) | (1<<UPM0));	break;	// none parity (Standard)
	}
	
	// Setup stopbits
	switch(stopbits)
	{
		case 2	:	SETREG |= (1<<USBS);		break;	// 2 stopbit
		default	:	SETREG &= ~(1<<USBS);		break;	// 1 stopbit (Standard)
	}
	
	
	UCSRC = SETREG;					// Write SETREG settings to UCSRC
	UCSRB = (1<<RXEN) | (1<<TXEN);	// Activate UART transmitter and receiver

	// Interrupt control
	
	// Receiver interrupt setup
	#ifdef UARTRXCIE
		UCSRB  |= (1<<RXCIE);
		sei();
	#endif

	// Transmitter interrupt setup
	#ifdef UARTTXCIE
		UCSRB  |= (1<<TXCIE);
		sei();
	#endif

	// Transmitter interrupt setup
	#ifdef UARTUDRIE
		#ifndef UARTTXCIE
			UCSRB  |= (1<<UDRIE);
			sei();
		#endif
	#endif

	uart_setchar(0x00);		// Transmit a Dummy Byte
}

//	+---------------------------------------------------------------+
//	|					UART disable function						|
//	+---------------------------------------------------------------+
void uart_disable(void)
{
	// Disable UART
	UCSRB = ~((1<<RXEN) | (1<<TXEN));
	
	// Receiver interrupt setup
	#ifdef UARTRXCIE
		UCSRB  &= ~(1<<RXCIE);
	#endif

	// Transmitter interrupt setup
	#ifdef UARTTXCIE
		UCSRB  &= ~(1<<TXCIE);
	#endif

	// Transmitter interrupt setup
	#ifdef UARTUDRIE
		#ifndef UARTTXCIE
			UCSRB  &= ~(1<<UDRIE);
		#endif
	#endif
}

void uart_reset(void)
{
	UDR;	// Clear the error flags (by reading UDR)
}

#ifndef UARTRXCIE	// Check if interrupt control is disabled

	//	+---------------------------------------------------------------+
	//	|					UART transmit character						|
	//	+---------------------------------------------------------------+
	void uart_setchar(unsigned char data)	{
		while(!(UCSRA & (1<<UDRE)));			// Wait until transmit buffer is free
			UDR = data;							// Write data into transmit buffer
	}

	//	+---------------------------------------------------------------+
	//	|					UART transmit string						|
	//	+---------------------------------------------------------------+
	void uart_setstring(unsigned char *string, unsigned char delimiter)	{
		// Repeat until end of string (\0)
		while(*string) {
				uart_setchar(*string);	// Send Character
			string++;					// Increase string variable
		}
		
		switch (delimiter)
		{
			case 0	:	uart_setchar(0x00);	break;	// NUL		(NULL)
			case 1	:	uart_setchar(0x0D);	break;	// CR		(CR)
			case 2	:	uart_setchar(0x0A);	break;	// LF		(NULL)
			case 3	:	uart_setchar(0x0A);			// LF		(Line Feed)
						uart_setchar(0x0D);	break;	// CR		(Carriage Return)
			case 4	:	uart_setchar(0x09);	break;	// TAB		(tab)
			case 5	:	uart_setchar(0x20);	break;	// SPACE	(space)
			case 6	:	uart_setchar(0x1B);	break;	// ESC		(escape)
			default	:						break;	// do nothing
		}
	}

#endif

#ifndef UARTTXCIE	// Check if interrupt control is disabled
	#ifndef UARTUDRIE	// Check if interrupt control is disabled

		//	+---------------------------------------------------------------+
		//	|					UART receive character						|
		//	+---------------------------------------------------------------+
		unsigned char uart_getchar(unsigned char *data, unsigned char echo)	{
			// Check data buffer
			if(UCSRA & (1<<RXC))
			{
				if(UCSRA & (1<<FE))
					return 0x01;			// Frame error
				else if(UCSRA & (1<<DOR))
					return 0x02;			// Receiver overflow
				else if(UCSRA & (1<<PE))
					return 0x03;			// Parity error
				
				*data = UDR;		// Write received data to pointer address
			}
			else
			{
				return 0x00;		// When no data received
			}
			
			// Transmit an echo if active
			if(echo != 0x00)
				uart_setchar(*data);
			
			return 0xFF;			// When data received
		}

		//	+---------------------------------------------------------------+
		//	|					UART receive string							|
		//	+---------------------------------------------------------------+
		unsigned char uart_getstring(unsigned char *string, unsigned char length, unsigned char delimiter, unsigned char echo)	{
			
			// Temporary variable
			unsigned char data;
			
			// Run through the string
			for(unsigned char i=0; i < (length - 1); i++)
			{
				// Loop until char is received
				unsigned char receive;
				
				do 
				{
					receive = uart_getchar(&data, echo);
					
					if(receive != 0x00 && receive != 0xFF)
						return receive;
					
				} while (receive != 0xFF);
				
				*string = data;	// Write data to string
				string++;		// Increase string pointer
				
				// If received data is equal delimiter return
				if(data == delimiter)
				{
					// If LF & CR are required
					if(echo == 0xF0)
					{
						uart_setchar('\n');
						uart_setchar('\r');
					}
					
					return 0x00;
				}
			}
			return 0xFF;	// if delimiter not found buffer overflow
		}
		
	#endif
#endif

