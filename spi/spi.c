/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: spi
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       communication over SPI
 * -------------------------------------
 */

#include "spi.h"

//	+---------------------------------------------------------------+
//	|					SPI initialization							|
//	+---------------------------------------------------------------+
unsigned char spi_init(unsigned char operation, unsigned char direction, unsigned char polarity, unsigned char spiclock)
{	
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//       SPECIAL FUNCTION
	// If during Initialisation SS
	// Pin is LOW, SPI Controller
	// will be configured as Slave.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	SPI_DDR  |= (1<<SPI_SS);	// Setup SCK, MOSI and SS as output
	SPI_PORT |= (1<<SPI_SS);	// Activate pull up resistor at Slave Select
	
	// Double speed setup
	#ifdef SPI2X
		SPSR = (1<<SPI2X);						// Double Speed Mode activated
	#else
		SPSR = 0x00;							// Double Speed Mode deactivated
	#endif
	
	// Master / Slave setup (direction setup)
	switch(operation)
	{
		case 0   : SPCR = 0x00;			break;	// Slave mode
		default	 : SPCR = (1<<MSTR);	break;	// Master mode
	}

	
	// MSB / LSB Direction
	switch(direction)
	{
		case 0   : SPCR &= ~(1<<DORD);	break;	// MSB first
		default	 : SPCR |= (1<<DORD);	break;	// LSB first
	}
	
	// Polarity of SCK and DATA
	switch(polarity)
	{
		case 1   :	SPCR |= (1<<CPHA);					break;	// Clock phase directly
		case 2   :	SPCR |= (1<<CPOL);					break;	// Idle state HIGH
		case 3   :	SPCR |= (1<<CPOL) | (1<<CPHA);		break;	// Idle state HIGH, Clock phase directly
		default	 :	SPCR &= ~((1<<CPOL) | (1<<CPHA));	break;	// Idle state LOW, Clock phase offset
	}
	
	// SPI Clock speed
	switch(spiclock)
	{
		case 1   :	SPCR |= (1<<SPR0);					break;	// Sysclock / 16
		case 2   :	SPCR |= (1<<SPR1);					break;	// Sysclock / 64
		case 3   :	SPCR |= (1<<SPR1) | (1<<SPR0);		break;	// Sysclock / 128
		default	 :	SPCR &= ~((1<<SPR1) | (1<<SPR0));	break;	// Sysclock / 4
	}
	
	// SPI interrupt setup
	#ifdef SPI_SPIE
		SPCR  |= (1<<SPIE);
		sei();
	#endif
	
	SPCR |= (1<<SPE);	// Activate the SPI Controller
	
	SPI_DDR  |= (1<<SPI_SCK) | (1<<SPI_MOSI) | (1<<SPI_MISO) | (1<<SPI_SS);	// Setup SCK, MOSI, MISO and SS as output
	
	// Check if master abort has occurred
	if(!(SPCR & (1<<MSTR)))
		return 0xFF;	// Return master abort
	return 0x00;		// Return SPI control register status
}

//	+---------------------------------------------------------------+
//	|					SPI disable function						|
//	+---------------------------------------------------------------+
void spi_disable(void)
{
	// Disable SPI
	SPCR &= ~(1<<SPE);
	SPI_DDR  &= ~((1<<SPI_SCK) | (1<<SPI_MOSI) | (1<<SPI_MISO) | (1<<SPI_SS));
	SPI_PORT &= ~((1<<SPI_SCK) | (1<<SPI_MOSI) | (1<<SPI_MISO) | (1<<SPI_SS));
	
	#ifdef SPI_SPIE	// Disable SPI interrupt
		SPCR  &= ~(1<<SPIE);
		sei();
	#endif
}

//	+---------------------------------------------------------------+
//	|					SPI Slave Select							|
//	+---------------------------------------------------------------+
void spi_select(unsigned char mode)
{
	switch(mode)
	{
		case 0  : SPI_PORT |=  (1<<SPI_SS);	break;	// Slave Select Off
		default : SPI_PORT &= ~(1<<SPI_SS);	break;	// Slave Select On
	}
}

#ifndef SPI_SPIE
//	+---------------------------------------------------------------+
//	|				SPI transfer / receive character				|
//	+---------------------------------------------------------------+
	unsigned char spi_transfer(unsigned char data) //SPI Tansfer durchführen
	{
		SPDR = data;	// Write data into the SPI Data Register and initiate a transmission
	
		// Wait until transmission is Complete
		while(!(SPSR & (1<<SPIF)))
			asm volatile("NOP");
		
		#ifdef SPI_WCOL_PORT
			#ifdef SPI_WCOL_PIN
				// Write Collision to Collision Port (Sticky) 
				if(SPSR & (1<<WCOL))
					SPI_WCOL_PORT |= (1<<SPI_WCOL_PIN);
			#endif
		#endif
		
		return SPDR;	// Return received data from the bus
	}
#endif