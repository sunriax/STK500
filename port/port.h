/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Header file for port library
 * -----------------------------------------
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