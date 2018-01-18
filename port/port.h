/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: port
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing port
 *       and logic
 * -------------------------------------
 */

#ifndef PORT_H_
#define PORT_H_

#include <avr/io.h>

unsigned char port_init(unsigned char port, unsigned char direction, unsigned char pullup);
unsigned char port_disable(unsigned char port);
unsigned char port_write(unsigned char port, unsigned char data, unsigned char logic);
unsigned char pin_read(unsigned char pin, unsigned char bit, unsigned char logic);
unsigned char pin_status(unsigned char pin);

#endif /* PORT_H_ */