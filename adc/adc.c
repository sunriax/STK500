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

#include "adc.h"

void adc_init(void)
{
	// Setup ADC parameters
	ADMUX = (((0x03 & ADC_REF)<<6) | ((0x01 & ADC_DATA_SHIFT)<<5) | ((0x03 & ADC_CHANNEL_MODE)<<3));
	
	// Setup ADC clock prescaler
	// F_ADC = F_CPU / ADC_PRESCALER
	ADCSRA = ((0x07 & ADC_PRESCALER));
	
	// Setup trigger source
	#if ADC_MODE == 0x01
		ADCSRA |= (1<<ADEN) | (1<<ADSC);
		SFIOR = ((0x07 & ADC_TRIGGER_SOURCE)<<5)
	#endif
	
	// Check if ADC interrupt handler is active
	#ifdef ADC_ADIE
		ADCSRA |= (1<<ADIE);
		sei();
	#endif
}

void adc_channel(unsigned char channel)
{
	ADMUX = (ADMUX & ~(0x07)) | (0x07 & channel);	// Select ADC Channel
}

void adc_stop(void)
{
	ADCSRA &= ~(1<<ADEN);
}

#ifndef ADC_ADIE

	unsigned int adc_read(void)
	{
		#if ADC_MODE == 0x01
			
			while(!(ADCSRA & (1<<ADIF)))
				asm volatile("NOP");
			
			ADCSRA |= (1<<ADIF);
			
			unsigned char ADC_LOW = ADCL;
			unsigned char ADC_HIGH = ADCH;
			
			return ((ADC_HIGH<<8) | ADC_LOW);
		
		#else
			
			// Start single converstion
			ADCSRA |= (1<<ADEN) | (1<<ADSC);
			
			while(ADCSRA & (1<<ADSC))
				asm volatile("NOP");
			
			unsigned char ADC_LOW = ADCL;
			unsigned char ADC_HIGH = ADCH;
			
			return ((ADC_HIGH<<8) | ADC_LOW);
			
		#endif
	}

#endif



