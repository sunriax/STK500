/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Function file for irq library
 * -----------------------------------------
 */

#include "irq.h"

//	+---------------------------------------------------------------+
//	|					IRQ initialization							|
//	+---------------------------------------------------------------+
unsigned char irq_init(unsigned char mode)
{
	// Setup mode
	// 0x00 -> LOW state
	// 0x01 -> State changing
	// 0x02 -> Falling edge
	// 0x03 -> Rising edge
	// Reset MCUCR INT0 with BIT masking before set, because of overwriting other interrupts
	MCUCR &= ~(0x03);			// Reset INT0 control register
	MCUCR |= (0x03  & mode);	// Setup INT0 control register
	
	#ifdef IRQ_ISR	// Check if IRQ is enabled
		GICR |= (1<<INT0);		// Enable INT0 ISR
		sei();					// Enable interrupts globally
	#endif
	
	return MCUCR;	// Return control register
}

#ifndef IRQ_ISR	// Check if interrupt control is disabled

	//	+---------------------------------------------------------------+
	//	|					IRQ status									|
	//	+---------------------------------------------------------------+
	unsigned char irq_status(void)
	{
		// If IRQ status is active
		if(GIFR & (1<<INTF0))
		{
			GIFR |= (1<<INTF0);	// Reset interrupt flag
			return 0xFF;		// Return true
		}
		return 0x00;	// Return false
	}

#endif

