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
#ifndef PWM_PIN_OC0
	#define PWM_PIN_OC0 PB3
#endif

#ifndef PWM_SINE_SAMPLES	// Quarter (1/4 curve) sine samples 
	#define PWM_SINE_SAMPLES 90
#endif

#ifndef PWM_OCIE			// Compare match interrupt enable
	#define PWM_OCIE
#endif

#ifndef PWM_TOIE			// Overflow interrupt enable
	#define PWM_TOIE
#endif

#include <limits.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>

         void pwm_init(unsigned char prescaler);
         void pwm_disable(void);
         void pwm_square(unsigned char match);
         void pwm_sawtooth(unsigned char increase);
         void pwm_triangle(unsigned char step);
         void pwm_ramp(unsigned char increase, unsigned char decrease);
unsigned char pwm_sine_table(unsigned char *table, unsigned char length);
         void pwm_sine(unsigned char *table, unsigned char size);

volatile unsigned char PWM_SIGNAL_MODE;
volatile unsigned char PWM_SAWTOOTH_INCREASE;
volatile unsigned char PWM_TRIANGLE_STEP;
volatile unsigned char PWM_RAMP_UP;
volatile unsigned char PWM_RAMP_DOWN;

#endif /* PWM_H_ */