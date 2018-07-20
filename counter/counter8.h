/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * www.github.com/sunriax
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16
 * -------------------------------------
 * Name: counter8
 * Ver.: 1.0 Release
 * Type: Library
 * Text: Routines for initializing and
 *       run 8 bit counters
 * -------------------------------------
 */

#ifndef COUNTER8_H_
#define COUNTER8_H_

// ATmega 8/16 (8 Bit) Timer 0 definitions
#ifndef COUNTER0_OC_DDR		// Define DDR of OC
		#define COUNTER0_OC_DDR DDRB
	#ifndef COUNTER0_OC_P		// Define OC pin
		#define COUNTER0_OC_P PB3
	#endif
#endif

// If another PIN than the OC pin should be used for toggle
// define _OTHER_ DDR, PORT, PIN, P
// #ifdef COUNTER0_OTHER_OC_DDR
//		#define COUNTER0_OTHER_OC_DDR DDRX
//	#ifdef COUNTER0_OTHER_OC_PORT
//			#define COUNTER0_OTHER_OC_PORT PORTX
//		#ifdef COUNTER0_OTHER_OC_PIN
//				#define COUNTER0_OTHER_OC_PIN PINX
//			#ifdef COUNTER0_OTHER_OC_P
//				#define COUNTER0_OTHER_OC_P PX
//			#endif
//		#endif
//	#endif
// #endif

// ATmega 8/16 (8 Bit) Timer 2 definitions
#ifndef COUNTER2_OC_DDR		// Define DDR of OC
		#define COUNTER2_OC_DDR DDRD
	#ifndef COUNTER2_OC_P		// Define OC pin
		#define COUNTER2_OC_P PD7
	#endif
#endif

// If another PIN than the OC pin should be used for toggle
// define _OTHER_ DDR, PORT, PIN, P
// #ifdef COUNTER2_OTHER_OC_DDR
//		#define COUNTER2_OTHER_OC_DDR DDRX
//	#ifdef COUNTER2_OTHER_OC_PORT
//			#define COUNTER2_OTHER_OC_PORT PORTX
//		#ifdef COUNTER2_OTHER_OC_PIN
//				#define COUNTER2_OTHER_OC_PIN PINX
//			#ifdef COUNTER2_OTHER_OC_P
//				#define COUNTER2_OTHER_OC_P PX
//			#endif
//		#endif
//	#endif
// #endif

#endif /* COUNTER8_H_ */