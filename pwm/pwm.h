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

// PWM special PIN definition
/*
#ifndef PWM_DDR
	#define PWM_DDR DDRB
#endif

#ifndef PWM_PORT
	#define PWM_PORT PORTB
#endif

#ifndef PWM_PIN
	#define PWM_PIN PB0
#endif
*/

// PWM standard PIN definition
#ifndef PWM_DDR_OC0
	#define PWM_DDR_OC0 DDRB
#endif

#ifndef PWM_PIN_OC0
	#define PWM_PIN_OC0 PB3
#endif




#ifndef PWM_SINE_SAMPLES	// Quarter (1/4 curve) sine samples 
	#define PWM_SINE_SAMPLES 32
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#endif /* PWM_H_ */