/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Sample for reading/writing data through
 *   twi bus with twi library
 * -----------------------------------------
 */

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Hardware setup
//
//             +-----+
//             |  U  |
// +-----------+  S  +--------------+                          AT24C02
// |     M     |  B  |  +---------+ |                       +-----------+
// |     E     +-----+  | DISPLAY | +---+ -> VCC -- VCC <-  |     E     |
// |     G              +---------+ | P |                   |     E     |
// |     A                          | O |                   |     P     |
// |     C                          | R |                   |     R     |
// |     A                          | T |                   |     O     |
// |     R                          | A |                   |     M     |
// |     D                          | / |                   |           |
// |                                | C | -> PC6 -- SDA <-  |           |
// |                                |   | -> PC7 -- SCL <-  |           |
// |                                +---+ -> GND -- GND <-  |           |
// +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+                       +-----------+ 
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#define F_CPU 12000000UL    // System clock (required for delay)

// SLAVE Address
#define SLAVE_ENABLE        // Enable to enable slave mode on TWI controller
#define SLAVE_ADDR 0x42     // EEPROM memory address

// System libraries
#include <avr/io.h>
#include <util/delay.h>

// User libraries
#include "twi.h"

int main(void)
{
    // Port setup
    DDRC = 0xF0;    // Set PORT(7:4) as output, PORT(1:0) as input
    PORTC = 0x03;   // Enable pullup resistors for SCL/SDA
    
    DDRC = 0x0F;    // Set PORT(3:0) as input
    PORTC = 0x0F;   // Enable pullup resistors for S3:0
    
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!        INFORMATION           !!!
    // !!! If the pullup resistor on    !!!
    // !!! SCL/SDA has a very high      !!!
    // !!! resistance, it could be      !!!
    // !!! necessary to slow down the   !!!
    // !!! TWI clock speed or manually  !!!
    // !!! mount 10k resistors between  !!!
    // !!! SCL -> VCC and SDA -> VCC    !!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    
    #ifndef SLAVE_ENABLE
    
        // Initialize TWI as Master
        twi_init(0x01);
        
        while(1)
        {
            
            // Write PIN status to slave
            twi_start();
            twi_address(SLAVE_ADDR, TWI_WRITE);
            twi_set(((0x0F & PINA)<<4));
            twi_stop();
            _delay_ms(10);
            
            // Read PIN status from slave
            twi_start();
            twi_address(SLAVE_ADDR, TWI_READ);
            twi_get(&PORTC, TWI_ACK);
            twi_stop();
            _delay_ms(10);
        }
    
    #else
    
        // Initialize TWI as Slave
        twi_init(0x00);
        
        while(1)
        {
            switch (twi_slave_start())
            {
                case 0x01:
                    while(!twi_slave_get(&PORTC, TWI_NACK))
                        asm volatile("NOP");
                    while(!twi_slave_stop())
                      asm volatile("NOP");  
                break;
                case 0x02:
                    twi_slave_set(((0x0F & PINA)<<4));
                    _delay_ms(2);
                break;
                default:
                break;
            }
        }
    
    #endif
}

