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

#include <avr/io.h>

#include "../pwm/pwm.h"


int main(void)
{
	pwm_init(0x03);
	// pwm_square(1);
	// pwm_sawtooth(1);
	// pwm_triangle(1);
	// pwm_ramp(1, 4);
	pwm_sine();
	
	while (1)
	{
	}
}

