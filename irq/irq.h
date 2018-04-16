/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: irq
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       run interrupt service request
 * -------------------------------------
 */ 

#ifndef IRQ_H_
#define IRQ_H_

#ifndef IRQ_ISR		// Setup Interrupt Request
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Interrupt handler has to be enabled      !!!
	// !!! through user.                            !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#define IRQ_ISR
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char irq_init(unsigned char mode);

#ifndef IRQ_ISR
	unsigned char irq_status(void);
#endif

#endif /* IRQ_H_ */