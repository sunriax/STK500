/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * www.github.com/sunriax
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16
 * -------------------------------------
 * Name: counter8
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       run 8 bit counters
 * -------------------------------------
 */

#include "counter8.h"

//	+---------------------------------------------------------------------------------------+
//	| !!! 8 Bit COUNTER initialization														|
//	+---------------------------------------------------------------------------------------+
//	|   counter: Select counter to setup													|
//	|            ATmega8/16 Timer/Counter (8 Bit) -> Timer0 = 0								|
//	|                                             -> Timer2 = 2								|
//	+---------------------------------------------------------------------------------------+
//	|      mode: Select counter mode														|
//	|            ATmega8/16 ->  Normal -> 0													|
//	|                              CTC -> 1													|
//	|                              PWM -> 2													|
//	|                          FastPWM -> 3													|
//	+---------------------------------------------------------------------------------------+
//	| prescaler: Select counter prescaler													|
//	|            ATmega8/16 -> 0 -> No prescaler											|
//	|                          1 -> System Clock											|
//	|                          2 -> System Clock/8											|
//	|                          3 -> System Clock/64											|
//	|                          4 -> System Clock/256										|
//	|                          5 -> System Clock/1024										|
//	|                          6 -> External Clock Tn (falling edge)						|
//	|                          7 -> External Clock Tn (rising edge)							|
//	+---------------------------------------------------------------------------------------+
//	|    output: Select counter output mode													|
//	|            ATmega8/16 -> Normal/CTC -> 0 -> OCn/other PIN disconnected				|
//	|                                        1 -> Toogle OCn/other PIN on overflow/match	|
//	|                                        2 -> Clear OCn/other PIN on overflow/match		|
//	|                                        3 -> Set OCn/other PIN on overflow/match		|
//	|                                 PWM -> 0 -> OCn/other PIN disconnected				|
//	|                                        1 -> Reserved									|
//	|                                        2 -> Clear OCn/other PIN on match				|
//	|                                             Set OCn/other PIN on match				|
//	|                                        3 -> Set OCn/other PIN on match				|
//	|                                             Clear OCn/other PIN on match				|
//	|                            Fast PWM -> 0 -> OCn/other PIN disconnected				|
//	|                                        1 -> Reserved									|
//	|                                        2 -> Clear OCn/other PIN on match				|
//	|                                             Set OCn/other PIN at bottom				|
//	|                                        3 -> Set OCn/other PIN on match				|
//	|                                             Clear OCn/other PIN at bottom				|
//	| Information: If #COUNTER_OC0_P or #COUNTER0_OTHER_OC0_PX are not defined. Operation	|
//	|              on PORT will not be initialized and permitted!							|
//	+---------------------------------------------------------------------------------------+
unsigned char counter8_init(unsigned char counter, unsigned char mode, unsigned char prescaler, unsigned char output)
{	
	switch (counter)	// Switch to counter which should be initialized
	{
		case 0	:	switch(mode)	// Setup counter operation mode
					{
						case 1	:	TCCR0 = (1<<WGM01) | (0x07 & prescaler) | (0x30 & (output<<4));					break;	// Clear timer on compare match
						case 2	:	TCCR0 = (1<<WGM00) | (0x07 & prescaler) | (0x30 & (output<<4));					break;	// PWM phase correct
						case 3	:	TCCR0 = (1<<WGM01) | (1<<WGM00) | (0x07 & prescaler) | (0x30 & (output<<4));	break;	// Fast PWM
						default	:	TCCR0 = (0x07 & prescaler) | (0x30 & (output<<4));								break;	// Normal operation
					}
					
					// Check if OCn/other Pin is activated
					if(mode > 0)
					{
						// Enable OCn Pin
						#ifndef COUNTER0_OC_P
							COUNTER0_OC_DDR |= (1<<COUNTER0_OC_P);
						#endif
						
						// Enable Other Pin
						#ifdef COUNTER0_OTHER_OC_P
							COUNTER0_OTHER_OC_DDR |= (1<<COUNTER0_OTHER_OC_P);
						#endif
					}
					else
					{
						// Disable OCn Pin
						#ifndef COUNTER0_OC_P
							COUNTER0_OC_DDR &= ~(1<<COUNTER0_OC_P);
						#endif
						
						// Disable other Pin
						#ifdef COUNTER0_OTHER_OC_P
							COUNTER0_OTHER_OC_DDR &= ~(1<<COUNTER0_OTHER_OC_P);
						#endif
					}
					
					break;
		case 2	:	switch(mode)	// Setup counter operation mode
					{
						case 1	:	TCCR2 = (1<<WGM21) | (0x07 & prescaler) | (0x30 & (output<<4));					break;	// Clear timer on compare match
						case 2	:	TCCR2 = (1<<WGM20) | (0x07 & prescaler) | (0x30 & (output<<4));					break;	// PWM phase correct
						case 3	:	TCCR2 = (1<<WGM21) | (1<<WGM20) | (0x07 & prescaler) | (0x30 & (output<<4));	break;	// Fast PWM
						default	:	TCCR2 = (0x07 & prescaler) | (0x30 & (output<<4));								break;	// Normal operation
					}
				
					// Check if OCn/other Pin is activated
					if(mode > 0)
					{
						// Enable OCn Pin
						#ifndef COUNTER2_OC_P
							COUNTER2_OC_DDR |= (1<<COUNTER0_OC_P);
						#endif
					
						// Enable Other Pin
						#ifdef COUNTER2_OTHER_OC_P
							COUNTER2_OTHER_OC_DDR |= (1<<COUNTER2_OTHER_OC_P);
						#endif
					}
					else
					{
						// Disable OCn Pin
						#ifndef COUNTER2_OC_P
							COUNTER2_OC_DDR &= ~(1<<COUNTER2_OC_P);
						#endif
					
						// Disable other Pin
						#ifdef COUNTER2_OTHER_OC_P
							COUNTER2_OTHER_OC_DDR &= ~(1<<COUNTER2_OTHER_OC_P);
						#endif
					}
				
					break;
		default: return 0xFF;
	}
	return 0x00;
}


