/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Header file for irq library
 * -----------------------------------------
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