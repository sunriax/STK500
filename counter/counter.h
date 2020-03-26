/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Header file for counter library
 * -----------------------------------------
 */

#ifndef COUNTER_H_
#define COUNTER_H_

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

#ifndef COUNTER_ISR		// Setup Interrupt Request
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Interrupt handler has to be enabled      !!!
	// !!! through user.                            !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#define COUNTER_ISR
#endif

	unsigned char counter_init(unsigned char prescaler);
			 void counter_reset(void);
			 void counter_stop(void);
			 void counter_start(unsigned char prescaler);

#ifdef COUNTER_CTC
			 void counter_limit(unsigned char data);
#endif

#ifndef COUNTER_ISR
	unsigned char counter_overflow(void);
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#endif /* COUNTER_H_ */