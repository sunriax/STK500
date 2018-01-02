/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: twi
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       communication over TWI
 * -------------------------------------
 */

#ifndef TWI_H_
#define TWI_H_

// Definition of TWI parameters

#ifndef F_CPU			// Systemclock
	#define F_CPU 12000000UL
#endif

#ifndef F_TWI			// TWI clock
	#define F_TWI 100000UL
#endif	

#ifndef TWI_PRESCALE	// TWI TWSR register prescaler (0-3)
	#define TWI_PRESCALE 0
#endif

#ifndef TWI_BITRATE		// Bitrate register
	#ifdef TWI_PRESCALE
		#define TWI_BITRATE ((F_CPU/F_TWI) - 16UL) / (2 * (1<<TWI_PRESCALE) * (1<<TWI_PRESCALE))
	#endif
#endif

#ifndef TWI_ADDRESS		// Slave address of the controller
	#define TWI_ADDRESS 0xEA
#endif

#ifndef TWI_BROADCAST	// Listen to general calls (0 = false/1 = true)
	#define TWI_BROADCAST 0x00
#endif

#ifndef TWI_ACK			// TWI acknowledge flag
	#define TWI_ACK 0x01
#endif

#ifndef TWI_NACK		// TWI not acknowledge flag
	#define TWI_NACK 0x01
#endif

#ifndef TWI_WRITE		// TWI write command
	#define TWI_WRITE 0x00
#endif

#ifndef TWI_READ		// TWI read command
	#define TWI_READ 0x01
#endif

// ATmega status codes (!!! Do not change !!!)
#define TWI_STATUS_START 0x08
#define TWI_STATUS_REPEATED_START 0x10
#define TWI_STATUS_ADDRESS_WRITE_NACK 0x18
#define TWI_STATUS_ADDRESS_WRITE_ACK 0x20
#define TWI_STATUS_DATA_WRITE_NACK 0x28
#define TWI_STATUS_DATA_WRITE_ACK 0x30
#define TWI_STATUS_ADDRESS_READ_NACK 0x38
#define TWI_STATUS_ADDRESS_READ_ACK 0x40
#define TWI_STATUS_DATA_READ_NACK 0x48
#define TWI_STATUS_DATA_READ_ACK 0x50

// Definition of TWI processing (Enabled = Interrupt/Disabled = Polling)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ! Interrupts are not included in this library !
// ! If interrupts are used, disable the polling !
// ! by uncommenting the next lines              !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//#ifndef TWI_TWIE	// TWI Interrupt based processing
//	#define TWI_TWIE
//#endif

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char twi_init(unsigned char operation);
         void twi_disable(void);
unsigned char twi_status(void);
unsigned char twi_start(void);
         void twi_stop(void);
unsigned char twi_address(unsigned char address);
unsigned char twi_get(unsigned char *data);

#endif /* TWI_H_ */