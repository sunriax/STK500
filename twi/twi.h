/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Header file for twi library
 * -----------------------------------------
 */

#ifndef TWI_H_
#define TWI_H_

// Definition of TWI parameters

#ifndef F_CPU			// System clock
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
	#define TWI_ADDRESS 0x42
#endif

#ifndef TWI_BROADCAST	// Listen to general calls (0 = false/1 = true)
	#define TWI_BROADCAST 0x00
#endif

#ifndef TWI_ACK			// TWI acknowledge flag
	#define TWI_ACK 0x01
#endif

#ifndef TWI_NACK		// TWI not acknowledge flag
	#define TWI_NACK 0x00
#endif

#ifndef TWI_WRITE		// TWI write command
	#define TWI_WRITE 0x00
#endif

#ifndef TWI_READ		// TWI read command
	#define TWI_READ 0x01
#endif

// ATmega status codes (!!! Do not change !!!)
#define TWI_STATUS_START                0x08
#define TWI_STATUS_REPEATED_START       0x10
#define TWI_STATUS_ADDRESS_WRITE_NACK   0x18
#define TWI_STATUS_ADDRESS_WRITE_ACK    0x20
#define TWI_STATUS_DATA_WRITE_NACK      0x28
#define TWI_STATUS_DATA_WRITE_ACK       0x30
#define TWI_STATUS_ARBITRATION_LOST     0x38
#define TWI_STATUS_ADDRESS_READ_ACK     0x40
#define TWI_STATUS_ADDRESS_READ_NACK    0x48
#define TWI_STATUS_DATA_READ_ACK        0x50
#define TWI_STATUS_DATA_READ_NACK       0x58

#define TWI_SLAVE_ADDRESS_WRITE                     0x60
#define TWI_SLAVE_ADDRESS_WRITE_ARBITRATION_LOST    0x68
#define TWI_SLAVE_GENERAL_CALL                      0x70
#define TWI_SLAVE_GENERAL_CALL_ARBITRATION_LOST     0x78
#define TWI_SLAVE_DATA_WRITE_ACK                    0x80
#define TWI_SLAVE_DATA_WRITE_NACK                   0x88
#define TWI_SLAVE_GENERAL_CALL_DATA_WRITE_ACK       0x90
#define TWI_SLAVE_GENERAL_CALL_DATA_WRITE_NACK      0x98
#define TWI_SLAVE_STOP_OR_REPEATED_START            0xA0

#define TWI_SLAVE_ADDRESS_READ                      0xA8
#define TWI_SLAVE_ADDRESS_READ_ARBITRATION_LOST     0xB0
#define TWI_SLAVE_DATA_READ_ACK                     0xB8
#define TWI_SLAVE_DATA_READ_NACK                    0xC0
#define TWI_SLAVE_DATA_READ_LAST                    0xC8

#define TWI_MISC_NO_RELEVANT_STATE  0xF8
#define TWI_MISC_BUS_ERROR          0x00


// Definition of TWI processing (Enabled = Interrupt/Disabled = Polling)

//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  !!! Interrupts are not included in this library  !!!
//  !!! If interrupts are used, polling will be      !!!
//  !!! disabled                                     !!!
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//#ifndef TWI_TWIE	// TWI Interrupt based processing
//	#define TWI_TWIE
//#endif

#include <avr/io.h>
#include <avr/interrupt.h>

    unsigned char twi_init(unsigned char operation);
    void twi_disable(void);
    unsigned char twi_status(void);

#ifndef TWI_TWIE
    unsigned char twi_start(void);
             void twi_stop(void);
    unsigned char twi_address(unsigned char address, unsigned char operation);
    unsigned char twi_set(unsigned char data);
    unsigned char twi_get(unsigned char *data, unsigned char acknowledge);
    unsigned char twi_slave_start(void);
    unsigned char twi_slave_get(unsigned char *data, unsigned char acknowledge);
    unsigned char twi_slave_set(unsigned char data);
    unsigned char twi_slave_stop(void);
#endif


#endif /* TWI_H_ */