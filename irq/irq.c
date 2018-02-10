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
 *       handling interrupt
 * -------------------------------------
 */ 

#include "irq.h"

ISR(TIMER0_COMP_vect)
{
	extern unsigned char compare_count += 1;
}

ISR(TIMER0_OVF_vect)
{
	extern unsigned char overflow_count += 1;
}

ISR(INT0_vect)
{
	
}

ISR(INT1_vect)
{
	
}

unsigned char interrupt_init(unsigned char interrupt, unsigned char *option)
{
	switch(interrupt)
	{
		case 1	:	// External Interrupt INT(0/1)
					
		
					break;
		default	:	return 0xFF;
	}
}



