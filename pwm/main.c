/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Sample for generating pwm signals with
 *   pwm library
 * -----------------------------------------
 */


// PORT settings
#define INPUT 0b00000001	// Set input PORT (PORTA)
#define S0 (1<<0)			// Set input PIN0 (PIN A0)
#define S1 (1<<1)			// Set input PIN1 (PIN A1)
#define S2 (1<<2)			// Set input PIN2 (PIN A2)
#define S3 (1<<3)			// Set input PIN3 (PIN A3)

// Include standard libraries
#include <avr/io.h>

// Include hardware abstraction library
#include "../port/port.h"
#include "../pwm/pwm.h"

int main(void)
{
	// Port setup
	port_init(INPUT, 0x00, 0x0F);	// Initialize PORT1 (PORTA) as INPUT with pullup @ BIT(3:0)

	// PWM Initialization
	pwm_init(0x01);
	
	while (1)
	{	
		// If S0 on Megacard / PA0 on STK500 pressed (not pulled!!!)
		if(pin_read(INPUT, S0, 0) == 0xFF)
			pwm_square(150);					// Setup square signal
		
		// If S1 on Megacard / PA1 on STK500 pressed (not pulled!!!)
		else if(pin_read(INPUT, S1, 0) == 0xFF)
			pwm_linear(1, 20);					// Setup rectangle signal
			
		// If S2 on Megacard / PA2 on STK500 pressed (not pulled!!!)
		else if(pin_read(INPUT, S2, 0) == 0xFF)
			//pwm_linear(2, 2);					// Setup sawtooth signal
			//pwm_linear(2, ((2<<8) | 2));		// Setup triangle signal
			pwm_linear(2, ((4<<8) | 2));		// Setup ramp signal
		
		// If S3 on Megacard / PA3 on STK500 pressed (not pulled!!!)
		else if(pin_read(INPUT, S3, 0) == 0xFF)
			pwm_sine(1);						// Setup sine signal
    }	// End of loop
}	// End of main

