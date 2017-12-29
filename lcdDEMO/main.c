/* -------------------------------------
 * SUNriaX Project
 * www.sunriax.at
 * -------------------------------------
 * Hardware: Megacard/STK500
 * Platform: ATmega8/16/32
 * -------------------------------------
 * Name: lcdDEMO
 * Ver.: 1.0 Debug
 * Type: Executable
 * Text: Demo application for LCD
 *       display characters
 * -------------------------------------
 */

// Include standard libraries
#include <avr/io.h>
#include <stdlib.h>

// Include hardware abstraction library
#include "../lcd/lcd.h"

int main(void)
{	
	// Self defined pattern for LCD CGRAM 64 byte / 8 = 8 Characters
	// Size of LCD display character 5 * 8 bit
	// Byte 0:	*****
	// Byte 1:	*****
	// Byte 2:	*****
	// Byte 3:	*****
	// Byte 4:	*****
	// Byte 5:	*****
	// Byte 6:	*****
	// Byte 7:	*****
	
	// Bell character
	unsigned char pattern_bell[] =	{
									0b00100,
									0b01110,
									0b01110,
									0b01110,
									0b11111,
									0b00000,
									0b00100,
									0b00000
									};

	unsigned char pattern_S[] =	{ 0b11111, 0b11001, 0b11000, 0b11111, 0b00011, 0b00011, 0b10011, 0b11111 };	// special S character
	unsigned char pattern_U[] =	{ 0b10001, 0b11011, 0b11011, 0b11011, 0b11011, 0b11011, 0b11011, 0b11111 };	// special U character
	unsigned char pattern_N[] =	{ 0b11001, 0b11001, 0b11001, 0b10101, 0b10101, 0b10011, 0b10011, 0b10011 };	// special N character
	unsigned char pattern_r[] =	{ 0b00000, 0b00000, 0b11110, 0b11111, 0b11000, 0b11000, 0b11000, 0b11000 };	// special r character
	unsigned char pattern_i[] =	{ 0b01110, 0b00000, 0b01110, 0b01110, 0b01110, 0b01110, 0b01110, 0b01110 };	// special i character
	unsigned char pattern_a[] =	{ 0b00000, 0b00000, 0b01111, 0b11111, 0b11001, 0b11001, 0b11111, 0b01111 };	// special a character
	unsigned char pattern_X[] =	{ 0b11011, 0b01110, 0b00100, 0b01110, 0b11011, 0b00000, 0b00000, 0b00000 };	// special X character
	
	// LCD display initialisation
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!! For special configuration edit lcd.h !!!
	// !!! Further information can be found in  !!!
	// !!! the WIKI or Github repository        !!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	lcd_init();
	
	// Save self defined patterns to CGRAM
	lcd_pattern(LCD_CGADDR_CHAR0, pattern_bell);
	lcd_pattern(LCD_CGADDR_CHAR1, pattern_S);
	lcd_pattern(LCD_CGADDR_CHAR2, pattern_U);
	lcd_pattern(LCD_CGADDR_CHAR3, pattern_N);
	lcd_pattern(LCD_CGADDR_CHAR4, pattern_r);
	lcd_pattern(LCD_CGADDR_CHAR5, pattern_i);
	lcd_pattern(LCD_CGADDR_CHAR6, pattern_a);
	lcd_pattern(LCD_CGADDR_CHAR7, pattern_X);
	
	// Write data to first Line
	lcd_home();								// Set cursor to home position
	lcd_char('N');							// Write single character to LCD display
	lcd_string((unsigned char*)("UM:"));	// Write string to LCD display
	lcd_ul2ascii(12, 10, 4);				// Write unsigned long to LCD display (4 fields reserved)
	//lcd_sl2ascii(-12, 10, 0);				// Write signed long to LCD display (no field reserved)
	//lcd_d2ascii(2.22, 4, 2);				// Write double to LCD display 
	
	// Write data to second Line
	lcd_cursor(0, 1);						// Set cursor to second line
	lcd_char(LCD_CGADDR_CHAR0);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR1);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR2);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR3);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR4);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR5);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR6);				// Write self defined pattern to LCD display
	lcd_char(LCD_CGADDR_CHAR7);				// Write self defined pattern to LCD display
	
	// Endless loop
    while (1) 
    {

    }	// End of loop
}	// End of main

