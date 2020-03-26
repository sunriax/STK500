/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Header file for pwm library
 * -----------------------------------------
 */

/* !!! Calculation of the signal frequencies can be found at the pwm.md file !!! */

#ifndef PWM_H_
#define PWM_H_

// PWM PIN definition

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! If PWM_PIN_OC0 is defined it is       !!!
// !!! necessary that DDR/PORT/PIN registers !!!
// !!! have been configured for OC0 pin      !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifndef PWM_DDR				// Direction register for OC0 / OTHER pin
	#define PWM_DDR DDRB
#endif

#ifndef PWM_PORT			// Port for PWM setup
	#define PWM_PORT PORTB
#endif

// PWM special PIN definition
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! If PWM_PIN_OC0 is defined the special !!!
// !!! pin is ignored and will not work      !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// #ifndef PWM_PIN			// Pin for PWM setup
//	#define PWM_PIN PINB
//#endif

// #ifndef PWM_PIN_OTHER	// When PIN_OC0 is disabled this pin has to be defined!
//	#define PWM_PIN_OTHER PB4
// #endif

// PWM standard PIN definition
#ifndef PWM_PIN_OC0			// Setup PIN OC0 this overwrites PIN_OTHER
	#define PWM_PIN_OC0 PB3
#endif

// PWM signal definition
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! Signals that are not used should be   !!!
// !!! disabled permanently by uncommenting  !!!
// !!! the directives.                       !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef PWM_SQUARE		// Enable PWM square function
	#define PWM_SQUARE
#endif

#ifndef PWM_LINEAR		// Enable PWM linear functions
	#define PWM_LINEAR
#endif

#ifndef PWM_SINE		// Enable PWM square function
	#define PWM_SINE
#endif

// Definition of PWM processing (Enabled = Interrupt/Disabled = Polling)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! Polling is not supported in this library  !!!
// !!! All signals are generated with interrupts !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef PWM_OCIE		// Compare match interrupt enable
	#define PWM_OCIE
#endif

#ifndef PWM_TOIE		// Overflow interrupt enable
	#define PWM_TOIE
#endif

#include <limits.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void pwm_init(unsigned char prescaler);
void pwm_disable(void);

#ifdef PWM_SQUARE
	void pwm_square(unsigned char match);
#endif

#ifdef PWM_LINEAR
	void pwm_linear(unsigned char type, unsigned int step);
#endif

#ifdef PWM_SINE
	void pwm_sine(unsigned char hold);
#endif

#endif /* PWM_H_ */