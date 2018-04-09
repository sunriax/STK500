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

#include "counter.h"

static unsigned char COUNTER_PRESCALER;

unsigned char counter_init(unsigned char prescaler)
{
	TCCR0 = (0x07 & prescaler);
	
	// Setup CTC if mode is not equal 0
	#if COUNTER_MODE != 0
	
		TCCR0 |= (1<<WGM01);
		
		#if COUNTER_IRQ != 0
			TIMSK |= (1<<OCIE0);
		#endif
		
	#else
	
		#if COUNTER_IRQ != 0
			TIMSK |= (1<<TOIE0);
		#endif
	
	#endif
	
	#if COUNTER_TOGGLE == 1
		TCCR0 |= (1<<COM00);
	#elif COUNTER_TOGGLE == 2
		TCCR0 |= (1<<COM01);
	#elif COUNTER_TOGGLE == 3
		TCCR0 |= (1<<COM01) | (1<<COM00);
	#endif
	
	return TCCR0;
}

void counter_reset(unsigned char data)
{
	TCNT0 = 0;
	OCR0 = 0;
}

void counter_start(unsigned char data)
{
	if(data != 0)
	TCCR0 |= (0x07 & data);
	else
	TCCR0 |= (0x07 & COUNTER_PRESCALER);
}

void counter_stop(void)
{
	COUNTER_PRESCALER = (0x07 & TCCR0);
	
	TCCR0 &= ~(0x07);
}


#if COUNTER_MODE != 0

	void counter_limit(unsigned char data)
	{
		OCR0 = data;
	}

#endif

#if COUNTER_IRQ == 0

	unsigned char counter_overflow(void)
	{
		#if COUNTER_MODE != 0
		
			if(TIFR & (1<<OCF0))
			{
				return 0xFF;
			}
			return 0x00;
		
		#else
		
			if(TIFR & (1<<TOV0))
			{
				return 0xFF;
			}
			return 0x00;
		
		#endif
	}

#endif