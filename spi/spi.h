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

#ifndef SPI_H_
#define SPI_H_

// Definition of SPI parameters

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
// When device is configured as
// Slave the Systemclock has to
// be 4 times higher then the
// SPI clock fcpu > 4 * fspi
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef SPI2X		// Double Speed mode
	#define SPI2X
#endif

#ifndef SPI_DDR		// Port direction register
	#define SPI_DDR DDRB
#endif

#ifndef SPI_PORT	// Port where SPI interface 
	#define SPI_PORT PORTB
#endif

#ifndef SPI_SS		// Slave Select Pin
	#define SPI_SS PB4
#endif

#ifndef SPI_MOSI	// Master Out Slave in Pin
	#define SPI_MOSI PB5
#endif

#ifndef SPI_MISO	// Master In Slave Out
	#define SPI_MISO PB6
#endif

#ifndef SPI_SCK		// Clock Pin
	#define SPI_SCK PB7
#endif

//#ifndef SPI_WCOL_PORT	// Output for write fault
//		#define SPI_WCOL_PORT PORTB	
//	#ifndef SPI_WCOL_PIN
//		#define SPI_WCOL_PIN PB3
//	#endif
//#endif

// Definition of SPI processing (Enabled = Interrupt/Disabled = Polling)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ! Interrupts are not included in this library !
// ! If interrupts are used, disable the polling !
// ! by uncommenting the next lines              !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//#ifndef SPI_SPIE	// SPI Interrupt based processing
//	#define SPI_SPIE
//#endif

#include <avr/io.h>

unsigned char spi_init(unsigned char operation, unsigned char direction, unsigned char polarity, unsigned char spiclock);
         void spi_select(unsigned char mode);
unsigned char spi_transfer(unsigned char data);

#endif /* SPI_H_ */