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

#ifndef COUNTER_TOGGLE
	#define COUNTER_TOGGLE 0	// OC0 disconnected
#endif

#ifndef COUNTER_MODE
	#define COUNTER_MODE 1
#endif

#ifndef COUNTER_IRQ
	#define COUNTER_IRQ 1
#endif

	unsigned char counter_init(unsigned char prescaler);
			 void counter_reset(unsigned char data);
			 void counter_stop(void);
			 void counter_start(unsigned char data);

#if COUNTER_MODE != 0
			 void counter_limit(unsigned char data);
#endif

#if COUNTER_IRQ == 0
	unsigned char counter_overflow(void);
#endif

#endif /* COUNTER_H_ */