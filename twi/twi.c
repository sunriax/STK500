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

#include "twi.h"

//	+---------------------------------------------------------------+
//	|					TWI initialization							|
//	+---------------------------------------------------------------+
unsigned char twi_init(unsigned char operation)
{
	// Set Slave Address and general Call
	TWAR = ((unsigned char)(((unsigned char)(TWI_ADDRESS))<<1)) | (0x01 & ((unsigned char)(TWI_BROADCAST)));
	
	// Master / Slave setup
	switch(operation)
	{
		case 1   :	// Master mode
					TWBR = (unsigned char)(TWI_BITRATE);	// Setup TWI Bitrate
					TWSR = (unsigned char)(TWI_PRESCALE);	// Setup TWI Prescaler
					break;
		default	 :	// Slave Mode
					TWBR = (unsigned char)(TWI_BITRATE);	// Setup TWI Bitrate
					TWSR = (unsigned char)(TWI_PRESCALE);	// Setup TWI Prescaler
					TWCR = (1<<TWEA) | (1<<TWEN);			// Enable TWI Bus and Acknowledge to TWI_ADDR or general call
					break;
	}
	
	// TWI interrupt setup
	#ifdef TWI_TWIE
		TWCR  |= (1<<TWIE);
		sei();
	#endif

	// Return message initialization
	// Bit(7:3) TWS7 - TWS3
	// Bit(2:2) TWWC
	return twi_status();
}

//	+---------------------------------------------------------------+
//	|					I2C start transmission						|
//	+---------------------------------------------------------------+
unsigned char twi_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	// Start a TWI transmission
							
	// Check if START done
	while(!(TWCR & (1<<TWINT)))
		asm volatile("NOP");
	
	// Check if an error occured
	if(((TWSR & 0xF8) != TWI_STATUS_START) || ((TWSR & 0xF8) != TWI_STATUS_REPEATED_START))
		return 0xFF;	// Start failure
	return 0x00;		// Start successfully
}

//	+---------------------------------------------------------------+
//	|					TWI stop transmission						|
//	+---------------------------------------------------------------+
void twi_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);	// Stop a TWI transmission
}

unsigned char twi_status(void)
{
	// Return message initialization
	// Bit(7:3) TWS7 - TWS3
	// Bit(2:2) TWWC
	return (0xF8 & TWSR) | (0x02 & (TWCR>>1));
}

//	+---------------------------------------------------------------+
//	|				TWI address + read/write data					|
//	+---------------------------------------------------------------+
unsigned char twi_address(unsigned char address)
{
	TWDR = address;					// Write data to data register
	TWCR = (1<<TWINT) | (1<<TWEN);	// Transmit addressbyte
	
	// Check if transmission done
	while(!(TWCR & (1<<TWINT)))
		asm volatile("NOP");
	
	// ADDRESS + WRITE operation
	if((address & 0x01) == TWI_WRITE)
	{
		if(((TWSR & 0xF8) != TWI_STATUS_ADDRESS_WRITE_ACK) || ((TWSR & 0xF8) != TWI_STATUS_ADDRESS_WRITE_NACK))
			return 0xFF;
	}
	// ADDRESS + READ operation
	else
	{
		if(((TWSR & 0xF8) != TWI_STATUS_ADDRESS_READ_ACK) || ((TWSR & 0xF8) != TWI_STATUS_ADDRESS_READ_NACK))
			return 0xFF;
	}
	return 0x00;
}

//	+---------------------------------------------------------------+
//	|					TWI transmit data							|
//	+---------------------------------------------------------------+
unsigned char twi_set(unsigned char data)
{
	TWDR = data;					// Write data to data register
	TWCR = (1<<TWINT) | (1<<TWEN);	// Transmit databyte
	
	// Check if transmission done
	while(!(TWCR & (1<<TWINT)))
		asm volatile("NOP");
	
	// Check if an error occurred
	if(((TWSR & 0xF8) != TWI_STATUS_DATA_WRITE_ACK) || ((TWSR & 0xF8) != TWI_STATUS_DATA_WRITE_NACK))
		return 0xFF;
	return 0x00;
}

//	+---------------------------------------------------------------+
//	|					TWI receive data							|
//	+---------------------------------------------------------------+
unsigned char twi_get(unsigned char *data)
{
	// Check if ACK should be sent
	if(*data == TWI_ACK)
		TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	// Check if NACK should be sent
	else if(*data == TWI_NACK)
		TWCR = (1<<TWINT) | (1<<TWEN);
	else
		return 0xFF;
	
	// Check if transmission done
	while (!(TWCR & (1<<TWINT)))
		asm volatile("NOP");
	
	// Write Data to pointer
	*data = TWDR;
	
	// Check if an error occurred
	if(((TWSR & 0xF8) != TWI_STATUS_DATA_READ_ACK) || ((TWSR & 0xF8) != TWI_STATUS_DATA_READ_NACK))
		return 0xFF;
	return 0x00;
}

