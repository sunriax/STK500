/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: uart
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       communication over UART
 * -------------------------------------
 */

#ifndef UART_H_
#define UART_H_

// Definition of SYSTEM parameters

#ifndef F_CPU	// Systemclock
	#define F_CPU 12000000UL
#endif

// Definition of UART parameters

#ifndef BAUD	// UART baudrate
	#define BAUD 9600UL
#endif

#ifndef U2XEN	// Samplerate (Enable = 8 Samples/Bit | Disable = 16 Samples/Bit)
	#define U2XEN
#endif

// Definition of UART processing (Enabled = Interrupt/Disabled = Polling)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ! Interrupts are not included in this library !
// ! If interrupts are used, disable the polling !
// ! by uncommenting the next lines              !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//#ifndef UARTRXCIE	// Receiver Interrupt based processing
//	#define UARTRXCIE
//#endif

//#ifndef UARTTXCIE	// Transmitter Interrupt based processing
//	#define UARTTXCIE
//#endif

//#ifndef UARTUDRIE	// Transmitter Interrupt based processing
//	#ifndef UARTTXCIE
//		#define UARTUDRIE
//	#else
//		#undef UARTUDRIE
//	#endif
//#endif

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(unsigned char datasize, unsigned char parity, unsigned char stopbits);
void uart_reset(void);

#ifndef UARTTXCIE
	#ifndef UARTUDRIE
		void uart_setchar(unsigned char data);
		void uart_setstring(unsigned char *string, unsigned char delimiter);
	#endif
#endif

#ifndef UARTRXCIE
	unsigned char uart_getchar(unsigned char *data, unsigned char echo);
	unsigned char uart_getstring(unsigned char *string, unsigned char length, unsigned char delimiter, unsigned char echo);
#endif

#endif /* UART_H_ */