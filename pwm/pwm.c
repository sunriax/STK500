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

/* !!! Calculation of the signal frequencies can be found at the pwm.md file !!! */

#include "pwm.h"

// Global variables needed for PWM  (!!! Do not change !!!)
volatile unsigned char PWM_SIGNAL_MODE;

#ifdef PWM_LINEAR
	volatile unsigned char PWM_RAMP;
	volatile unsigned char PWM_RAMP_UP;
	volatile unsigned char PWM_RAMP_DOWN;
#endif

#ifdef PWM_SINE
	volatile unsigned char PWM_SINE_VALUE;
	volatile unsigned char PWM_SINE_HOLD;
	volatile unsigned char PWM_SINE_COUNT;
	volatile unsigned char PWM_SINE_QUADRANT;

// Select the sine table size for the project (0°- 90°)

/* 10 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 20, 39, 58, 75, 90, 103, 113, 121, 125 };
/* 15 */		const unsigned char PWM_SINE_TABLE[] = { 0, 13, 26, 39, 52, 63, 75, 85, 94, 103, 110, 116, 121, 124, 126 };
/* 18 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 11, 22, 33, 43, 54, 63, 73, 82, 90, 97, 104, 110, 115, 119, 123, 125, 127 };
/* 30 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 7, 13, 20, 26, 33, 39, 46, 52, 58, 63, 69, 75, 80, 85, 90, 94, 99, 103, 107, 110, 113, 116, 119, 121, 123, 124, 125, 126, 127 };
/* 45 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 4, 9, 13, 18, 22, 26, 31, 35, 39, 43, 48, 52, 56, 60, 63, 67, 71, 75, 78, 82, 85, 88, 91, 94, 97, 100, 103, 105, 108, 110, 112, 114, 116, 118, 119, 121, 122, 123, 124, 125, 126, 126, 127, 127 };
/* 90 */	//	const unsigned char PWM_SINE_TABLE[] = { 0, 2, 4, 7, 9, 11, 13, 15, 18, 20, 22, 24, 26, 29, 31, 33, 35, 37, 39, 41, 43, 46, 48, 50, 52, 54, 56, 58, 60, 62, 63, 65, 67, 69, 71, 73, 75, 76, 78, 80, 82, 83, 85, 87, 88, 90, 91, 93, 94, 96, 97, 99, 100, 101, 103, 104, 105, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 119, 120, 121, 121, 122, 123, 123, 124, 124, 125, 125, 125, 126, 126, 126, 127, 127, 127, 127, 127 };

//	for(unsigned char i=0; i < 90; i++)
//		table[i] = 127 * sin((M_PI * i) / 180);
#endif

#ifdef PWM_OCIE

	//	+---------------------------------------------------------------+
	//	|				Timer 0 Compare interrupt vector				|
	//	+---------------------------------------------------------------+
	ISR(TIMER0_COMP_vect)
	{
		#ifndef PWM_PIN_OC0
		
			// Check if OTHER pin is HIGH
			if(PWM_PIN & (1<<PWM_PIN_OTHER))
				PWM_PORT &= ~(1<<PWM_PIN_OTHER);	// Set OTHER pin LOW
			else
				PWM_PORT |= (1<<PWM_PIN_OTHER);		// Set OTHER pin HIGH
		
		#endif
		
		// Create rectangle signal
		if(PWM_SIGNAL_MODE == 1)
		{
			OCR0 = PWM_RAMP_UP;
		}
		// Create linear (sawtooth/triangle/ramp)
		else if(PWM_SIGNAL_MODE == 2)
		{
			// If RAMP is 0x00 (increase) and RAMP_UP is greater than 0
			if((PWM_RAMP == 0x00) && (PWM_RAMP_UP > 0))
			{
				// If OCR0 is greater than 255 - UP
				if(OCR0 > (CHAR_MAX - PWM_RAMP_UP))
				{
					// Check if OCR0 is already 255
					if(OCR0 == CHAR_MAX)
						OCR0 = CHAR_MIN;	// Set OCR0 to min. value 0
					else
						OCR0 = CHAR_MAX;	// Set OCR0 to max. value 255
					
					// Check if RAMP_DOWN is greater than 0
					if(PWM_RAMP_DOWN > 0)
						PWM_RAMP = 0xFF;	// Set RAMP to 0xFF (decrease)
				}
				else
				{
					OCR0 += PWM_RAMP_UP;	// increase OCR0 with initialized level
				}
			}
			// If RAMP is 0xFF (decrease) and RAMP_DOWN is greater than 0
			else if((PWM_RAMP == 0xFF) && (PWM_RAMP_DOWN > 0))
			{
				// If OCR0 is lower than 0 + RAMP_DOWN
				if((OCR0 < (CHAR_MIN + PWM_RAMP_DOWN)))
				{
					OCR0 = CHAR_MIN;		// Set OCR0 to min. value 0
					
					// Check if RAMP_UP is greater than 0 (not necessary)
					if(PWM_RAMP_UP > 0)
						PWM_RAMP = 0x00;	// Set RAMP to 0x00 (increase)
				}
				else
				{
					OCR0 -= PWM_RAMP_DOWN;	// decrease OCR0 with initialized level
				}
			}
			else
			{
				PWM_RAMP = 0x00;			// Reset RAMP to 0x00 (increase)
			}
		}
		// Create sine signal
		else if(PWM_SIGNAL_MODE == 3)
		{
			// Switch to active quadrant
			switch(PWM_SINE_QUADRANT)
			{
				// Quadrant 1 (0° - 90°)
				case 1	:	// If VALUE lower than (SINE_TABLE_SIZE - 1)
							if(PWM_SINE_VALUE < (sizeof(PWM_SINE_TABLE) - 1))
							{
								// Set OCR0 to 127 + TABLE[VALUE]
								OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
				
								// VALUE is not equal 0 AND COUNT lower than HOLD(function setup)
								if((PWM_SINE_VALUE != 0) && PWM_SINE_COUNT < PWM_SINE_HOLD)
								{
									PWM_SINE_COUNT++;		// Increase COUNT
								}
								else
								{
									PWM_SINE_VALUE++;		// Increase TABLE VALUE (next sine value)
									PWM_SINE_COUNT = 0;		// Reset COUNT
								}
							}
							else
							{
								// COUNT lower than HOLD(function setup)
								if(PWM_SINE_COUNT < PWM_SINE_HOLD)
								{
									PWM_SINE_COUNT++;		// Increase COUNT
								}
								else
								{
									PWM_SINE_QUADRANT = 2;	// Select 2 quadrant
									PWM_SINE_COUNT = 0;		// Reset COUNT
								}
				
								// Set OCR0 to 127 + TABLE[VALUE] (max. value)
								OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
							}
							break;
				// Quadrant 2 (90° - 180°)
				case 2	:	// If VALUE greater than 0
							if(PWM_SINE_VALUE > CHAR_MIN)
							{
								// Set OCR0 to 127 + TABLE[VALUE] (max. value)
								OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
				
								// COUNT lower than HOLD(function setup)
								if(PWM_SINE_COUNT < PWM_SINE_HOLD)
								{
									PWM_SINE_COUNT++;		// Increase COUNT
								}
								else
								{
									PWM_SINE_VALUE--;		// Increase TABLE VALUE (next sine value)
									PWM_SINE_COUNT = 0;		// Reset COUNT
								}
							}
							else
							{
								PWM_SINE_QUADRANT = 3;		// Select 3 quadrant
				
								// Set OCR0 to 127 + TABLE[VALUE] (min. value)
								OCR0 = (CHAR_MAX / 2) + PWM_SINE_TABLE[PWM_SINE_VALUE];
							}
							break;
				// Quadrant 3 (180° - 270°)
				case 3	:	// If VALUE lower than (SINE_TABLE_SIZE - 1)
							if(PWM_SINE_VALUE < (sizeof(PWM_SINE_TABLE) - 1))
							{
								// Set OCR0 to 127 - TABLE[VALUE] (min. value)
								OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
				
								// VALUE is not equal 0 AND COUNT lower than HOLD(function setup)
								if((PWM_SINE_VALUE != 0) && (PWM_SINE_COUNT < PWM_SINE_HOLD))
								{
									PWM_SINE_COUNT++;		// Increase COUNT
								}
								else
								{
									PWM_SINE_VALUE++;		// Increase TABLE VALUE (next sine value)
									PWM_SINE_COUNT = 0;		// Reset COUNT
								}
				
							}
							else
							{
								// COUNT lower than HOLD(function setup)
								if(PWM_SINE_COUNT < PWM_SINE_HOLD)
								{
									PWM_SINE_COUNT++;		// Increase COUNT
								}
								else
								{
									PWM_SINE_QUADRANT = 4;	// Select 4 quadrant
									PWM_SINE_COUNT = 0;		// Reset COUNT
								}
				
								// Set OCR0 to 127 - TABLE[VALUE] (min. value)
								OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
							}
							break;
				// Quadrant 4 (270° - 0°)
				case 4	:	// If VALUE greater than 0
							if(PWM_SINE_VALUE > CHAR_MIN)
							{
								// Set OCR0 to 127 - TABLE[VALUE] (max. value)
								OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
				
								// COUNT lower than HOLD(function setup)
								if(PWM_SINE_COUNT < PWM_SINE_HOLD)
								{
									PWM_SINE_COUNT++;		// Increase COUNT
								}
								else
								{
									PWM_SINE_VALUE--;		// Increase TABLE VALUE (next sine value)
									PWM_SINE_COUNT = 0;		// Reset COUNT
								}
				
							}
							else
							{
								PWM_SINE_QUADRANT = 1;		// Select 1 quadrant
				
								// Set OCR0 to 127 - TABLE[VALUE] (min. value)
								OCR0 = (CHAR_MAX / 2) - PWM_SINE_TABLE[PWM_SINE_VALUE];
							}
							break;
				default	:	PWM_SINE_QUADRANT = 1;	// Setup Quadrant 1
							PWM_SINE_VALUE = 0;		// Reset value counter
							PWM_SINE_COUNT = 0;		// Reset hold counter
				break;
			}	
		}
	}
#endif

#ifdef PWM_TOIE

	//	+---------------------------------------------------------------+
	//	|				Timer 0 Overflow interrupt vector				|
	//	+---------------------------------------------------------------+
	ISR(TIMER0_OVF_vect)
	{
		#ifndef PWM_PIN_OC0
		
			// Check if OTHER pin is HIGH
			if(PWM_PIN & (1<<PWM_PIN_OTHER))
				PWM_PORT &= ~(1<<PWM_PIN_OTHER);	// Set OTHER pin LOW
			else
				PWM_PORT |= (1<<PWM_PIN_OTHER);		// Set OTHER pin HIGH
		
		#endif
	}
#endif

//	+---------------------------------------------------------------+
//	|						PWM initialization						|
//	+---------------------------------------------------------------+
void pwm_init(unsigned char prescaler)
{	
	// If there is a special PORT for PWM signal defined 
	#ifndef PWM_PIN_OC0
		PWM_DDR |= (1<<PWM_PIN_OTHER);		// Setup toggle PIN as output
		PWM_PORT &= ~(1<<PWM_PIN_OTHER);	// Set toggle PIN to LOW
	#else
		PWM_DDR |= (1<<PWM_PIN_OC0);		// Setup PIN OC0 as output
	#endif
	
	TCCR0 = (0x07 & prescaler);				// Setup Timer 0 prescaler
}

//	+---------------------------------------------------------------+
//	|							PWM disable							|
//	+---------------------------------------------------------------+
void pwm_disable(void)
{
	// Diable PWM
	TCCR0 &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));	// Diable prescaler (stop timer)
	OCR0 = CHAR_MAX;								// Set OCR0 to max. value (255)
	
	#ifndef PWM_PIN_OC0
		PWM_PORT &= ~(1<<PWM_PIN_OTHER);	// Disable toggle port
		PWM_DDR &= ~(1<<PWM_PIN_OTHER);		// Disable toggle pin
	#else
		PWM_PORT &= ~(1<<PWM_PIN_OC0);		// Disable OC0 port
		PWM_DDR &= ~(1<<PWM_PIN_OC0);		// Disable OC0 pin
	#endif
}

#ifdef PWM_SQUARE

	//	+---------------------------------------------------------------+
	//	|					Setup square generation						|
	//	+---------------------------------------------------------------+
	void pwm_square(unsigned char match)
	{	
		PWM_SIGNAL_MODE = 0;	// Setup signal mode
	
		// If match is 0 (Timer Overflow Mode)
		if(match == 0)
		{
			// Reset counter setup
			TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
		
			#ifdef PWM_PIN_OC0 
				TCCR0 |= (1<<COM00);	// PIN OC0 toggling
			#endif
					
			TIMSK |= (1<<TOIE0);		// Setup Timer overflow interrupt
			TIMSK &= ~(1<<OCIE0);		// Disable Timer compare interrupt
		}
		// Timer Compare Match Mode
		else
		{
			// Reset counter setup
			TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
		
			#ifdef PWM_PIN_OC0 
				TCCR0 |= (1<<WGM01) | (1<<COM00);	// Setup Timer 0 CTC + PIN OC0 toggling
			#else
				TCCR0 |= (1<<WGM01);				// Setup Timer 0 CTC
			#endif
		
			TIMSK |= (1<<OCIE0);		// Setup Timer compare interrupt
			TIMSK &= ~(1<<TOIE0);		// Disable Timer overflow interrupt
			
			OCR0 = match;				// Setup match to OCR0
		}
		sei();	// Enable global interrupts
	}
#endif

#ifdef PWM_LINEAR

	//	+---------------------------------------------------------------+
	//	|				Setup linear signal generation					|
	//	+---------------------------------------------------------------+
	void pwm_linear(unsigned char type, unsigned int step)
	{
		// Switch to signal that should be generated
		switch(type)
		{
			case 1	:	PWM_SIGNAL_MODE = 1;	break;	// Generate rectangle signal
			case 2	:	PWM_SIGNAL_MODE = 2;	break;	// Generate sawtooth signal
			case 3	:	PWM_SIGNAL_MODE = 2;	break;	// Generate triangle signal
			case 4	:	PWM_SIGNAL_MODE = 2;	break;	// Generate ramp signal
			default	:	return;
		}
		
		PWM_RAMP_UP = (step);		// Setup value for increasing OCR0
		PWM_RAMP_DOWN = (step>>8);	// Setup value for decreasing OCR0, zero (0) for rectangle/sawtooth
		
		// Reset counter setup
		TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
		
		#ifdef PWM_PIN_OC0
			TCCR0 |= (1<<WGM00) | (1<<COM01);	// Setup Timer 0 PWM (phase correct) + PIN OC0 toggling
		#else
			TCCR0 |= (1<<WGM00);				// Setup Timer 0 PWM (phase correct)
		#endif
		
		TIMSK |= (1<<OCIE0);		// Setup Timer compare interrupt
		TIMSK &= ~(1<<TOIE0);		// Disable Timer overflow interrupt

		sei();	// Enable global interrupts
	}

#endif

#ifdef PWM_SINE

	//	+---------------------------------------------------------------+
	//	|					Setup sine generation						|
	//	+---------------------------------------------------------------+
	void pwm_sine(unsigned char hold)
	{	
		PWM_SIGNAL_MODE = 3;								// Setup signal mode
		PWM_SINE_HOLD = hold;								// Setup how long the sine value should been hold on PIN
		
		// Reset counter setup
		TCCR0 &= ~((1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01));
	
		#ifdef PWM_PIN_OC0
			TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01);	// Setup Timer 0 Fast PWM + PIN OC0 toggling
		#else
			TCCR0 |= (1<<WGM01) | (1<<WGM00);				// Setup Timer 0 Fast PWM
		#endif
	
		TIMSK |= (1<<OCIE0) | (1<<TOIE0);	// Setup Timer compare interrupt and timer overflow interrupt
		
		sei();	// Enable global interrupts
	}
#endif