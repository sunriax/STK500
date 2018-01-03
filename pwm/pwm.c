/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: pwm
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       generating a pwm signal
 * -------------------------------------
 */

#include "pwm.h"

#ifdef PWM_OCIE
	ISR(TIMER0_COMP_vect)
	{
		#ifndef PWM_PIN_OC0
			if(PWM_PIN & (1<<PWM_PIN_OTHER))
				PWM_PORT &= ~(1<<PWM_PIN_OTHER);
			else
				PWM_PORT |= (1<<PWM_PIN_OTHER);
		#endif
		
		switch(PWM_SIGNAL_MODE)
		{
			// Sawtooth
			case 1	:	if((OCR0 != UCHAR_MAX) && (OCR0 > (UCHAR_MAX - PWM_SAWTOOTH_INCREASE)))
						{
							OCR0 = UCHAR_MAX;
						}
						else
						{
							OCR0 += PWM_SAWTOOTH_INCREASE;
						}
						break;
			// Triangle
			case 2	:	if((OCR0 > (CHAR_MAX - PWM_TRIANGLE_STEP)))
						{
							OCR0 = CHAR_MAX;
							PWM_SIGNAL_MODE = 3;
						}
						else
						{
							OCR0 += PWM_TRIANGLE_STEP;
						}
						break;
			case 3	:	if((OCR0 < (CHAR_MIN + PWM_TRIANGLE_STEP)))
						{
							OCR0 = CHAR_MIN;
							PWM_SIGNAL_MODE = 2;
						}
						else
						{
							OCR0 -= PWM_TRIANGLE_STEP;
						}
						break;
			// Ramp Up/Down
			case 4	:	if((OCR0 > (CHAR_MAX - PWM_RAMP_UP)))
						{
							OCR0 = CHAR_MAX;
							PWM_SIGNAL_MODE = 5;
						}
						else
						{
							OCR0 += PWM_RAMP_UP;
						}
						break;
			case 5	:	if((OCR0 < (CHAR_MIN + PWM_RAMP_DOWN)))
						{
							OCR0 = CHAR_MIN;
							PWM_SIGNAL_MODE = 4;
						}
						else
						{
							OCR0 -= PWM_RAMP_DOWN;
						}
						break;
			default	:	break;
		}
		
	}
#endif

#ifdef PWM_TOIE
	ISR(TIMER0_OVF_vect)
	{
		#ifndef PWM_PIN_OC0
			if(PWM_PIN & (1<<PWM_PIN_OTHER))
				PWM_PORT &= ~(1<<PWM_PIN_OTHER);
			else
				PWM_PORT |= (1<<PWM_PIN_OTHER);
		#endif
	}
#endif

void pwm_init(unsigned char prescaler)
{	
	// If there is a special PORT for PWM signal defined 
	#ifndef PWM_PIN_OC0
		PWM_DDR |= (1<<PWM_PIN_OTHER);			// Setup toggle PIN as output
		PWM_PORT &= ~(1<<PWM_PIN_OTHER);		// Set toggle PIN to LOW
	#else
		PWM_DDR |= (1<<PWM_PIN_OC0);	// Setup PIN OC0 as output
	#endif
	
	TCCR0 |= (0x07 & prescaler);
}

void pwm_disable(void)
{
	// Diable PWM
	TCCR0 = ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	OCR0 = CHAR_MIN;
	
	#ifndef PWM_PIN_OC0
		PWM_PORT &= ~(1<<PWM_PIN_OTHER);	// Disable toggle port
		PWM_DDR &= ~(1<<PWM_PIN_OTHER);		// Disable toggle pin
	#else
		PWM_PORT &= ~(1<<PWM_PIN_OC0);		// Disable OC0 port
		PWM_DDR &= ~(1<<PWM_PIN_OC0);		// Disable OC0 pin
	#endif
}

void pwm_square(unsigned char match)
{	
	PWM_SIGNAL_MODE = 0;
	
	if(match == 0)
	{
		TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
		
		#ifdef PWM_PIN_OC0 
			TCCR0 |= (1<<COM00);
		#endif
					
		TIMSK |= (1<<TOIE0);
		TIMSK &= ~(1<<OCIE0);
	}
	else
	{
		TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
		
		#ifdef PWM_PIN_OC0 
			TCCR0 |= (1<<WGM01) | (1<<COM00);
		#else
			TCCR0 |= (1<<WGM01);
		#endif
		
		TIMSK |= (1<<OCIE0);
		TIMSK &= ~(1<<TOIE0);
		OCR0 = match;
	}
	sei();
}

void pwm_sawtooth(unsigned char increase)
{	
	PWM_SIGNAL_MODE = 1;
	PWM_SAWTOOTH_INCREASE = increase;
	
	TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
	
	#ifdef PWM_PIN_OC0
		TCCR0 |= (1<<WGM00) | (1<<COM01);
	#else
		TCCR0 |= (1<<WGM00);
	#endif
	
	TIMSK |= (1<<OCIE0);
	TIMSK &= ~(1<<TOIE0);

	sei();
}

void pwm_triangle(unsigned char step)
{	
	PWM_SIGNAL_MODE = 2;
	PWM_TRIANGLE_STEP = step;
	
	TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
	
	#ifdef PWM_PIN_OC0
		TCCR0 |= (1<<WGM00) | (1<<COM01);
	#else
		TCCR0 |= (1<<WGM00);
	#endif
	
	TIMSK |= (1<<OCIE0);
	TIMSK &= ~(1<<TOIE0);

	sei();
}

void pwm_ramp(unsigned char increase, unsigned char decrease)
{	
	PWM_SIGNAL_MODE = 4;
	PWM_RAMP_UP = increase;
	PWM_RAMP_DOWN = decrease;
	
	TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
	
	#ifdef PWM_PIN_OC0
		TCCR0 |= (1<<WGM00) | (1<<COM01);
	#else
		TCCR0 |= (1<<WGM00);
	#endif
	
	TIMSK |= (1<<OCIE0);
	TIMSK &= ~(1<<TOIE0);

	sei();
}

unsigned char pwm_sine_table(unsigned char *table, unsigned char length)
{
	if(length > 45)
		return 0xFF;
	
	for(unsigned char i=0; i < 90; i += (90/length))
	{
		table[i] = 127 * sin((M_PI * i) / 180);
	}
	
	return 0x00;
}

void pwm_sine(unsigned char *table, unsigned char size)
{	
	PWM_SIGNAL_MODE = 6;
	
	TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
	
	#ifdef PWM_PIN_OC0
		TCCR0 |= (1<<WGM00) | (1<<COM01);
	#else
		TCCR0 |= (1<<WGM00);
	#endif
	
	TIMSK |= (1<<OCIE0);
	TIMSK &= ~(1<<TOIE0);

	sei();
	
	// Available Modes
	// -----------------------------------------------------------
	// 0: Normal PWM(50:50) frequency adjustable through prescaler
	// 1: PWM (xxx:511) frequency through prescaler
	// 2: FastPWM (xxx:255) frequency through prescaler
	// 3: CTC PWM(50:50) frequency adjustable through OCR register
	// -----------------------------------------------------------
	/*
	switch(operation)
	{
		case 1	:	TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<COM00);				break;	// PWM (Phase correct), OC0 toggle (up=1/down=0)
		case 2	:	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<COM00);	break;	// FastPWM, OC0 toggle (up=1/down=0)
		case 3	:	TCCR0 = (1<<WGM01) | (1<<COM00);							break;	// CTC mode, OC0 toggle
		default :	TCCR0 = (1<<COM00);											break;	// Normal, OC0 toggle
	}
	*/
}