/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: counter
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       run counter
 * -------------------------------------
 */ 

#ifndef COUNTER_H_
#define COUNTER_H_

#include <avr/io.h>

#ifndef COUNTER_TOGGLE	// OC0 Port setting
	// 0x00 -> OC0 disabled
	// 0x01 -> Toggle OC0
	// 0x02 -> Clear OC0
	// 0x03 -> Set OC0
	#define COUNTER_TOGGLE 0
#endif

#ifndef COUNTER_CTC		// Setup CTC (Clear Timer on Compare match)
	#define COUNTER_CTC
#endif

#ifndef COUNTER_IRQ		// Setup Interrupt Request
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Interrupt handler has to be enabled      !!!
	// !!! through user.                            !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#define COUNTER_IRQ
#endif

	unsigned char counter_init(unsigned char prescaler);
			 void counter_reset(void);
			 void counter_stop(void);
			 void counter_start(unsigned char prescaler);

#ifdef COUNTER_CTC
			 void counter_limit(unsigned char data);
#endif

#ifndef COUNTER_IRQ
	unsigned char counter_overflow(void);
#endif

#endif /* COUNTER_H_ */