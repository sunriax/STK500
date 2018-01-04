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

// Global PWM variables
volatile unsigned char PWM_SIGNAL_MODE;
volatile unsigned char PWM_SAWTOOTH_INCREASE;
volatile unsigned char PWM_TRIANGLE_STEP;
volatile unsigned char PWM_RAMP_UP;
volatile unsigned char PWM_RAMP_DOWN;
volatile unsigned char PWM_SINE_VALUE;
volatile unsigned char PWM_SINE_QUADRANT;


/* 10 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 20, 39, 58, 75, 90, 103, 113, 121, 125 };
/* 15 */		const unsigned char PWM_SINE_TABLE[] = { 0, 13, 26, 39, 52, 63, 75, 85, 94, 103, 110, 116, 121, 124, 126 };
/* 90 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 2, 4, 7, 9, 11, 13, 15, 18, 20, 22, 24, 26, 29, 31, 33, 35, 37, 39, 41, 43, 46, 48, 50, 52, 54, 56, 58, 60, 62, 63, 65, 67, 69, 71, 73, 75, 76, 78, 80, 82, 83, 85, 87, 88, 90, 91, 93, 94, 96, 97, 99, 100, 101, 103, 104, 105, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 119, 120, 121, 121, 122, 123, 123, 124, 124, 125, 125, 125, 126, 126, 126, 127, 127, 127, 127, 127 };

//	for(unsigned char i=0; i < 90; i++)
//		table[i] = 127 * sin((M_PI * i) / 180);

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
		#ifdef PWM_SAWTOOTH		// Enable sawtooth if defined
			case 1	:	if((OCR0 != UCHAR_MAX) && (OCR0 > (UCHAR_MAX - PWM_SAWTOOTH_INCREASE)))
						{
							OCR0 = UCHAR_MAX;
						}
						else
						{
							OCR0 += PWM_SAWTOOTH_INCREASE;
						}
						break;
		#endif
		#ifdef PWM_TRIANGLE		// Enable triangle if defined
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
		#endif
		#ifdef PWM_RAMP			// Enable ramp if defined
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
		#endif
		#ifdef PWM_SINE	// Enable sine if defined
			case 6	:	switch(PWM_SINE_QUADRANT)
						{
							case 1	:	if(PWM_SINE_VALUE < (sizeof(PWM_SINE_TABLE) - 1))
										{
											OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
											PWM_SINE_VALUE++;
										}
										else
										{
											PWM_SINE_QUADRANT = 2;
											OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
										}
										break;
							case 2	:	if(PWM_SINE_VALUE > CHAR_MIN)
										{
											OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
											PWM_SINE_VALUE--;
										}
										else
										{
											PWM_SINE_QUADRANT = 3;
											OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
										}
										break;
							case 3	:	if(PWM_SINE_VALUE < (sizeof(PWM_SINE_TABLE) - 1))
										{
											OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
											PWM_SINE_VALUE++;
										}
										else
										{
											PWM_SINE_QUADRANT = 4;
											OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
										}
										break;
							case 4	:	if(PWM_SINE_VALUE > CHAR_MIN)
										{
											OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
											PWM_SINE_VALUE--;
										}
										else
										{
											PWM_SINE_QUADRANT = 1;
											OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
										}
										break;
							default	:	PWM_SINE_QUADRANT = 1;
										PWM_SINE_VALUE = 0;
										break;
						}
						break;
		#endif
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

#ifdef PWM_SQUARE
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
#endif

#ifdef PWM_SAWTOOTH
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
#endif

#ifdef PWM_TRIANGLE
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
#endif

#ifdef PWM_RAMP
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
#endif

#ifdef PWM_SINE
	void pwm_sine(void)
	{	
		PWM_SIGNAL_MODE = 6;
	
		TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
	
		#ifdef PWM_PIN_OC0
			TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01);
		#else
			TCCR0 |= (1<<WGM01) | (1<<WGM00);
		#endif
	
		TIMSK |= (1<<OCIE0) | (1<<TOIE0);
		// TIMSK &= ~(1<<TOIE0);

		sei();
	}
#endif




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