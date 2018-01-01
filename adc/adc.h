/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: adc
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       reading data from A/D Converter
 * -------------------------------------
 */ 

#ifndef ADC_H_
#define ADC_H_

// Definition of ADC parameters

#ifndef ADC_REF				// ADC reference voltage
	// 0x00 -> AREF Pin
	// 0x01 -> AVCC
	// 0x02 -> -
	// 0x03 -> 2.56V 
	#define ADC_REF 0x01
#endif

#ifndef ADC_CHANNEL_MODE	// ADC channel mode
	// 0x00 -> 8 unipolar channels
	// 0x01 -> 2 differential channels with amplification
	// 0x02 -> 7 differential channels through ADC1 (negativ)
	// 0x03 -> 5 differential channels through ADC2 (negativ)
	#define ADC_CHANNEL_MODE 0x00
#endif

#ifndef ADC_MODE			// ADC running mode
	// 0x00 Single transformation
	// 0x01 Permanent transformation
	#define ADC_MODE 0x00
#endif

#ifndef ADC_DATA_SHIFT		// ADC data register position
	// 0x00 -> right
	// 0x01 -> left
	#define ADC_DATA_SHIFT 0x00
#endif

#ifndef ADC_PRESCALER		// ADC prescaler settings
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! The prescaler settings should be setup   !!!
	// !!! to a value that the ADC clock is between !!!
	// !!! 50 - 200 kHz (for fully 10 bit mode)     !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//
	// 0x00 -> F_CPU / 2
	// 0x01 -> F_CPU / 2
	// 0x02 -> F_CPU / 4
	// 0x03 -> F_CPU / 8
	// 0x04 -> F_CPU / 16
	// 0x05 -> F_CPU / 32
	// 0x06 -> F_CPU / 64
	// 0x07 -> F_CPU / 128
	#define ADC_PRESCALER 0x05
#endif

#ifndef ADC_TRIGGER_SOURCE	// ADC trigger source setting
	// 0x00 -> Free running mode
	// 0x01 -> Analog comparator
	// 0x02 -> External Interrupt (0)
	// 0x03 -> Timer 0 compare
	// 0x04 -> Timer 0 overflow
	// 0x05 -> Timer 1 compare B
	// 0x06 -> Timer 1 overflow
	// 0x07 -> Timer 1 capture
	#define ADC_TRIGGER_SOURCE 0x00
#endif

// Definition of ADC processing (Enabled = Interrupt/Disabled = Polling)

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ! Interrupts are not included in this library !
// ! If interrupts are used, disable the polling !
// ! by uncommenting the next lines              !
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// #ifndef ADC_ADIE
//	#define ADC_ADIE
// #endif

#include <avr/io.h>

void adc_init(void);
void adc_channel(unsigned char channel);
void adc_stop(void);
unsigned int adc_read(void);

#endif /* ADC_H_ */