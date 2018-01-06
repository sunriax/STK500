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
 *       generateing a pwm signal
 * -------------------------------------
 */

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../pwm/pwm.h"

int main(void)
{
	// Port setup
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! Actual there is no abstraction for the PORT setup !!!
	// !!! It will be integrated in future developments      !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DDRA = 0x00;	// Set PORTA as input
	PORTA = 0x0F;	// Set PULLUPs at PORTA(3:0)

	// PWM Initialization
	pwm_init(0x01);
	
	while (1)
	{	
		// If S0 on Megacard / PA0 on STK500 pressed (not pulled!!!)
		if(!(PINA & (1<<PA0)))
			pwm_square(150);					// Setup square signal
		
		// If S1 on Megacard / PA1 on STK500 pressed (not pulled!!!)
		else if(!(PINA & (1<<PA1)))
			pwm_linear(1, 20);					// Setup rectangle signal
			
		// If S2 on Megacard / PA2 on STK500 pressed (not pulled!!!)
		else if(!(PINA & (1<<PA2)))
			//pwm_linear(2, 2);					// Setup sawtooth signal
			//pwm_linear(2, ((2<<8) | 2));		// Setup triangle signal
			pwm_linear(2, ((4<<8) | 2));		// Setup ramp signal
			
		
		// If S3 on Megacard / PA3 on STK500 pressed (not pulled!!!)
		else if(!(PINA & (1<<PA3)))
			pwm_sine(1);						// Setup sine signal
    }	// End of loop
}	// End of main

