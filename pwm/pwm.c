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

ISR(TIMER0_COMP_vect)
{
	
}

ISR(TIMER0_OVF_vect)
{
	
}

void pwm_init(unsigned char operation, unsigned char prescaler)
{	
	// Available Modes
	// -----------------------------------------------------------
	// 0: Normal PWM(50:50) frequency adjustable through prescaler
	// 1: PWM (xxx:511) frequency through prescaler
	// 2: FastPWM (xxx:255) frequency through prescaler
	// 3: CTC PWM(50:50) frequency adjustable throug OCR register
	// -----------------------------------------------------------
	switch(operation)
	{
		case 1	:	TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<COM00);				break;	// PWM (Phase correct), OC0 toggle (up=1/down=0)
		case 2	:	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<COM00);	break;	// FastPWM, OC0 toggle (up=1/down=0)
		case 3	:	TCCR0 = (1<<WGM01) | (1<<COM00);							break;	// CTC mode, OC0 toggle
		default :	TCCR0 = (1<<COM00);											break;	// Normal, OC0 toggle
	}

	// If there is a special PORT for PWM signal defined 
	#ifdef PWM_DDR
		#ifdef PWM_PORT
			#ifdef PWM_PIN 
				PWM_DDR |= (1<<PWM_PIN);				// Setup special OC0 PIN as output
				PWM_PORT &= ~(1<<PWM_PIN);				// Set special OC0 PIN to LOW
				TCCR0 &= ~((1<<COM01) | (1<<COM00));	// Deactivate PIN OC0
			#endif
		#endif
	#else
		PWM_DDR_OC0 |= (1<<PWM_PIN_OC0);	// Setup PIN OC0 as output
	#endif
	
	switch(prescaler)
	{
		default	:	TCCR0 |= (1<<CS00);
	}
}
