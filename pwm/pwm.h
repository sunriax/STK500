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

#ifndef PWM_H_
#define PWM_H_


// PWM PIN defintion

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! If PWM_PIN_OC0 is defined it is       !!!
// !!! necessary that DDR/PORT/PIN registers !!!
// !!! have been configured for OC0 pin      !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifndef PWM_DDR
	#define PWM_DDR DDRB
#endif

#ifndef PWM_PORT
	#define PWM_PORT PORTB
#endif

// PWM special PIN definition
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! If PWM_PIN_OC0 is defined the special !!!
// !!! pin is ignored and will not work      !!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// #ifndef PWM_PIN
//	#define PWM_PIN PINB
//#endif

// #ifndef PWM_PIN_OTHER
//	#define PWM_PIN_OTHER PB4
// #endif

// PWM standard PIN definition
#ifndef PWM_PIN_OC0		// Setup PIN OC0
	#define PWM_PIN_OC0 PB3
#endif

#ifndef PWM_SQUARE		// Enable PWM square function
	#define PWM_SQUARE
#endif

#ifndef PWM_SAWTOOTH	// Enable PWM square function
	#define PWM_SAWTOOTH
#endif

#ifndef PWM_TRIANGLE	// Enable PWM square function
	#define PWM_TRIANGLE
#endif

#ifndef PWM_RAMP		// Enable PWM square function
	#define PWM_RAMP
#endif

#ifndef PWM_SINE		// Enable PWM square function
	#define PWM_SINE
#endif

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

#ifdef PWM_SAWTOOTH
	void pwm_sawtooth(unsigned char increase);
#endif

#ifdef PWM_TRIANGLE
	void pwm_triangle(unsigned char step);
#endif

#ifdef PWM_RAMP
	void pwm_ramp(unsigned char increase, unsigned char decrease);
#endif

#ifdef PWM_SAWTOOTH
	void pwm_sine(void);
#endif

#endif /* PWM_H_ */