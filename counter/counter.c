/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Function file for counter library
 * -----------------------------------------
 */

#include "counter.h"

// Global variables needed for COUNTER  (!!! Do not change !!!)
static unsigned char COUNTER_PRESCALER;

//	+---------------------------------------------------------------+
//	|					COUNTER initialization						|
//	+---------------------------------------------------------------+
unsigned char counter_init(unsigned char prescaler)
{
	// Setup presacler
	// 000 -> none
	// 001 -> F_CPU
	// 010 -> F_CPU/8
	// 011 -> F_CPU/64
	// 100 -> F_CPU/256
	// 101 -> F_CPU/1024
	// 110 -> External Clock (T0, falling edge)
	// 111 -> External Clock (T0, rising edge)
	TCCR0 = (0x07 & prescaler);
	
	#ifdef COUNTER_CTC		// Check if CTC is defined
	
		TCCR0 |= (1<<WGM01);		// Setup CTC mode
		
		#ifdef COUNTER_ISR	// Check if ISR is enabled
			TIMSK |= (1<<OCIE0);	// Enable compare match overflow interrupt
			sei();					// Interrupts global freigeben
		#endif
		
	#else
	
		#ifdef COUNTER_ISR	// Check if ISR is enabled
			TIMSK |= (1<<TOIE0);	// Enable timer overflow interrupt
			sei();					// Enable interrupts globally
		#endif
	
	#endif
	
	#if COUNTER_TOGGLE != 0	// Check if toggling is enabled
		DDRB |= (1<<PB3);		// Setup PIN OC0 as output
	#endif
	
	#if COUNTER_TOGGLE == 1
		TCCR0 |= (1<<COM00);				// Toggle OC0
	#elif COUNTER_TOGGLE == 2
		TCCR0 |= (1<<COM01);				// Clear OC0
	#elif COUNTER_TOGGLE == 3
		TCCR0 |= (1<<COM01) | (1<<COM00);	// Set OC0
	#endif
	
	COUNTER_PRESCALER = (0x07 & TCCR0);		// Save prescaler status
	
	return TCCR0;
}

//	+---------------------------------------------------------------+
//	|					COUNTER reset (zero)						|
//	+---------------------------------------------------------------+
void counter_reset(void)
{
	TCNT0 = 0;	// Reset Timer/Counter 0
	OCR0 = 0;	// Reset compare match register
}

//	+---------------------------------------------------------------+
//	|					COUNTER start								|
//	+---------------------------------------------------------------+
void counter_start(unsigned char prescaler)
{
	// counter_stop();	// Uncomment only if necessary!
	
	// If prescaler is not equal zero
	if(prescaler != 0)
		TCCR0 |= (0x07 & prescaler);			// Start timer with new prescaler
	else
		TCCR0 |= (0x07 & COUNTER_PRESCALER);	// Start timer with last defined prescaler
}

//	+---------------------------------------------------------------+
//	|					COUNTER stop								|
//	+---------------------------------------------------------------+
void counter_stop(void)
{
	TCCR0 &= ~(0x07);			// Stop timer
}


#ifdef COUNTER_CTC	// Check if CTC mode is enabled

	//	+---------------------------------------------------------------+
	//	|					COUNTER limit								|
	//	+---------------------------------------------------------------+
	void counter_limit(unsigned char data)
	{
		OCR0 = data;	// Setup timer compare register with data
	}

#endif

#ifndef COUNTER_ISR	// Check if interrupt control is disabled

	//	+---------------------------------------------------------------+
	//	|					COUNTER overflow							|
	//	+---------------------------------------------------------------+
	unsigned char counter_overflow(void)
	{
		#ifdef COUNTER_CTC	// Check if CTC mode is enabled
		
			// If Timer compare match interrupt flag is set
			if(TIFR & (1<<OCF0))
			{
				TIFR |= (1<<OCF0);	// Reset interrupt flag
				return 0xFF;		// Return true
			}
			return 0x00;	// Return false
		
		#else
		
			// If Timer overflow interrupt flag is set
			if(TIFR & (1<<TOV0))
			{
				TIFR |= (1<<TOV0);	// Reset interrupt flag
				return 0xFF;		// Return true
			}
			return 0x00;	// Return false
		
		#endif
	}

#endif