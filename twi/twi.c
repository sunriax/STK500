/* -----------------------------------------
 * SUNriaX Engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Hardware: STK500/Megacard (ATmega16)
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Function file for twi library
 * -----------------------------------------
 */

#include "twi.h"

//	+---------------------------------------------------------------+
//	|					TWI initialization							|
//	+---------------------------------------------------------------+
//  | Parameter:    operation   ->  0x01 = Master mode              |
//  |                               0x00 = Slave mode               |
//  |                                                               |
//  |    Return:    BIT(7:3)    ->  TWS7 - TWS3                     |
//  |               BIT(2)      ->  TWWC                            |
//  |               BIT(1:0)    ->  0b00                            |
//	+---------------------------------------------------------------+
unsigned char twi_init(unsigned char operation)
{
	// Set Slave Address and general Call
	TWAR = ((unsigned char)(((unsigned char)(TWI_ADDRESS))<<1)) | (0x01 & ((unsigned char)(TWI_BROADCAST)));
	
	// Master / Slave setup
	switch(operation)
	{
		case 0   :	// Slave Mode
					TWSR &= ~(0x07);	                    // Setup TWI Prescaler
					TWCR = (1<<TWEA) | (1<<TWEN);			// Enable TWI Bus and Acknowledge to TWI_ADDR or general call
					break;
		default	 :	// Master mode
					TWBR = (unsigned char)(TWI_BITRATE);	// Setup TWI Bitrate
					TWSR = (unsigned char)(TWI_PRESCALE);	// Setup TWI Prescaler
					break;
	}
	
	// TWI interrupt setup
	#ifdef TWI_TWIE
		TWCR  |= (1<<TWIE);
		sei();
	#endif

	// Return message initialization
	return twi_status();
}

//	+---------------------------------------------------------------+
//	|					TWI disable function						|
//	+---------------------------------------------------------------+
void twi_disable(void)
{
	// Disable TWI
	TWCR &= ~((1<<TWEA) | (1<<TWEN) | (1<<TWIE));
	
	#ifdef TWI_TWIE	// Diable TWI interrupt
		TWCR  &= ~(1<<TWIE);
	#endif
}

//	+---------------------------------------------------------------+
//	|						TWI status byte							|
//	+---------------------------------------------------------------+
//  |    Return:    BIT(7:3)    ->  TWS7 - TWS3                     |
//  |               BIT(2)      ->  TWWC                            |
//  |               BIT(1:0)    ->  0b00                            |
//	+---------------------------------------------------------------+
unsigned char twi_status(void)
{
	return (0xF8 & TWSR) | (0x04 & (TWCR>>1));
}

#ifndef TWI_TWIE

    //	+---------------------------------------------------------------+
    //	|					TWI start transmission						|
    //	+---------------------------------------------------------------+
    //  |    Return:    0x00        ->  Start successful                |
    //  |               0xFF        ->  Start failure                   |
    //	+---------------------------------------------------------------+
    unsigned char twi_start(void)
    {
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);	// Start a TWI transmission
							
	    // Check if START done
	    while(!(TWCR & (1<<TWINT)))
		    asm volatile("NOP");
	
	    // Check if an error occurred
	    if(((TWSR & 0xF8) == TWI_STATUS_START) || ((TWSR & 0xF8) == TWI_STATUS_REPEATED_START))
		    return 0x00;	// (Repeated)Start successfully
	    return 0xFF;	// (Repeated)Start failure
    }

    //	+---------------------------------------------------------------+
    //	|					TWI stop transmission						|
    //	+---------------------------------------------------------------+
    void twi_stop(void)
    {
	    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);	// Stop a TWI transmission
    
        while(!(TWCR & (1<<TWSTO)))
            asm volatile("NOP");
    }

    //	+---------------------------------------------------------------+
    //	|				TWI address + read/write data					|
    //	+---------------------------------------------------------------+
    //  | Parameter:    address     ->  Adress (Bit6:0) of slave device |
    //  |               operation   ->  WRITE/READ operation            |
    //  |                                                               |
    //  |    Return:    0x00        ->  Addressing successful           |
    //  |               0x0F        ->  Arbitration lost (multi master) |
    //  |               0xFF        ->  Error occured                   |
    //	+---------------------------------------------------------------+
    unsigned char twi_address(unsigned char address, unsigned char operation)
    {
	    TWDR = (address<<1) | (0x01 & operation);	// Write data to data register
	    TWCR = (1<<TWINT) | (1<<TWEN);				// Transmit address byte + operation
	
	    // Check if transmission done
	    while(!(TWCR & (1<<TWINT)))
		    asm volatile("NOP");
    
	    // ADDRESS + WRITE operation
	    if((operation & 0x01) == TWI_WRITE)
	    {
		    if(((TWSR & 0xF8) == TWI_STATUS_ADDRESS_WRITE_ACK) || ((TWSR & 0xF8) == TWI_STATUS_ADDRESS_WRITE_NACK))
			    return 0x00;
	    }
	    // ADDRESS + READ operation
	    else
	    {
		    if(((TWSR & 0xF8) == TWI_STATUS_ADDRESS_READ_ACK) || ((TWSR & 0xF8) == TWI_STATUS_ADDRESS_READ_NACK))
			    return 0x00;
	    }
        
        // Check if arbitration lost (only multi-master mode)
        if((TWSR & 0xF8) == TWI_STATUS_ARBITRATION_LOST)
            return 0x0F;
        
	    return 0xFF;
    }

    //	+---------------------------------------------------------------+
    //	|					TWI transmit data							|
    //	+---------------------------------------------------------------+
    //  | Parameter:    data        ->  Data to transmit                |
    //  |                                                               |
    //  |    Return:    0x00        ->  Data transmitted successful     |
    //  |               0x0F        ->  Arbitration lost (multi master) |
    //  |               0xFF        ->  Error occured                   |
    //	+---------------------------------------------------------------+
    unsigned char twi_set(unsigned char data)
    {
	    TWDR = data;								// Write data to data register
	    TWCR = (1<<TWINT) | (1<<TWEN);	            // Transmit databyte
	
	    // Check if transmission done
	    while(!(TWCR & (1<<TWINT)))
		    asm volatile("NOP");
	
	    // Check if an error occurred
	    if(((TWSR & 0xF8) == TWI_STATUS_DATA_WRITE_ACK) || ((TWSR & 0xF8) == TWI_STATUS_DATA_WRITE_NACK))
		    return 0x00;
        
        // Check if arbitration lost (only multi-master mode)
        if((TWSR & 0xF8) == TWI_STATUS_ARBITRATION_LOST)
            return 0x0F;
        
	    return 0xFF;
    }

    //	+---------------------------------------------------------------+
    //	|					TWI receive data							|
    //	+---------------------------------------------------------------+
    //  | Parameter:    data        ->  Received data                   |
    //  |               acknowledge ->  ACK/NACK                        |
    //  |                                                               |
    //  |    Return:    0x00        ->  Data received successful        |
    //  |               0x0F        ->  Arbitration lost (multi master) |
    //  |               0xFF        ->  Error occured                   |
    //	+---------------------------------------------------------------+
    unsigned char twi_get(unsigned char *data, unsigned char acknowledge)
    {
	    // Check if ACK should be sent
	    if(acknowledge == TWI_ACK)
		    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);	// Transmit databyte + ACK
	    // Check if NACK should be sent
	    else if(acknowledge == TWI_NACK)
		    TWCR = (1<<TWINT) | (1<<TWEN);				// Transmit databyte + NACK
	    else
		    return 0xFF;
	
	    // Check if transmission done
	    while (!(TWCR & (1<<TWINT)))
		    asm volatile("NOP");
	
	    // Write Data to pointer
	    *data = TWDR;
	
	    // Check if an error occurred
	    if(((TWSR & 0xF8) == TWI_STATUS_DATA_READ_ACK) || ((TWSR & 0xF8) == TWI_STATUS_DATA_READ_NACK))
		    return 0x00;
            
        
        // Check if arbitration lost (only multi-master mode)
        if((TWSR & 0xF8) == TWI_STATUS_ARBITRATION_LOST)
            return 0x0F;
        
	    return 0xFF;
    }
    

    //	+---------------------------------------------------------------+
    //	|					TWI slave start condition   				|
    //	+---------------------------------------------------------------+
    //  |    Return:    0x00        ->  Slave Device is not addressed   |
    //  |               0x01        ->  Master writes data to bus       |
    //  |               0x02        ->  Master reads data from bus      |
    //  |               0xFF        ->  Master initiates a general call |
    //	+---------------------------------------------------------------+
    unsigned char twi_slave_start(void)
    {
        // Check if controller is addressed
        if(TWCR & (1<<TWINT))
        {
            if( ((TWSR & 0xF8) == TWI_SLAVE_ADDRESS_WRITE) ||
                ((TWSR & 0xF8) == TWI_SLAVE_ADDRESS_WRITE_ARBITRATION_LOST)    )
            {
                TWCR |= (1<<TWINT);
                return 0x01;
            }
            else if( ((TWSR & 0xF8) == TWI_SLAVE_ADDRESS_READ) ||
                     ((TWSR & 0xF8) == TWI_SLAVE_ADDRESS_READ_ARBITRATION_LOST)    )
            {
                TWCR |= (1<<TWINT);
                return 0x02;
            }
            else if ( ((TWSR & 0xF8) == TWI_SLAVE_GENERAL_CALL) ||
                      ((TWSR & 0xF8) == TWI_SLAVE_GENERAL_CALL_ARBITRATION_LOST)    )
            {
                TWCR |= (1<<TWINT);
                return 0xFF;
            }
        }
        return 0x00;
    }
    
    //	+---------------------------------------------------------------+
    //	|					TWI receive data							|
    //	+---------------------------------------------------------------+
    //  | Parameter:    data        ->  Received data                   |
    //  |               acknowledge ->  ACK/NACK                        |
    //  |                                                               |
    //  |    Return:    0x00        ->  Data received successful        |
    //  |               0xFF        ->  Error occured                   |
    //	+---------------------------------------------------------------+
    unsigned char twi_slave_get(unsigned char *data, unsigned char acknowledge)
    {
        // Check if ACK should be sent
        if(acknowledge == TWI_ACK)
            TWCR |= (1<<TWEA);
        // Check if NACK should be sent
        else if(acknowledge == TWI_NACK)
            TWCR &= ~(1<<TWEA);
        else
            return 0xFF;
        
        if(TWCR & (1<<TWINT))
        {
            *data = TWDR;
           
            if( (acknowledge == TWI_ACK) &&
                (   ((TWSR & 0xF8) == TWI_SLAVE_DATA_WRITE_ACK) ||
                    ((TWSR & 0xF8) == (TWI_SLAVE_GENERAL_CALL_DATA_WRITE_ACK)) ))
            {
                TWCR |= (1<<TWINT);
                return 0x00;
            }
            else if((acknowledge == TWI_NACK) &&
                    (   ((TWSR & 0xF8) == TWI_SLAVE_DATA_WRITE_NACK) ||
                        ((TWSR & 0xF8) == (TWI_SLAVE_GENERAL_CALL_DATA_WRITE_NACK)) ))
            {
                TWCR |= (1<<TWINT);
                return 0x00;
            }
            return 0xFF;
        }
        return 0xFF;
    }

    //	+---------------------------------------------------------------+
    //	|					TWI receive data							|
    //	+---------------------------------------------------------------+
    //  | Parameter:    data        ->  Received data                   |
    //  |               acknowledge ->  ACK/NACK                        |
    //  |                                                               |
    //  |    Return:    TWI_ACK     ->  Data sent with ACK              |
    //  |               TWI_NACK    ->  Data sent with NACK             |
    //  |               0xFF        ->  Error occured                   |
    //	+---------------------------------------------------------------+
    unsigned char twi_slave_set(unsigned char data)
    {
        TWDR = data;
        
        // Check if transmission done
        while (!(TWCR & (1<<TWINT)))
            asm volatile("NOP");
            
        if((TWSR & 0xF8) == TWI_SLAVE_DATA_READ_ACK)
        {
            TWCR |= (1<<TWINT);
            return TWI_ACK;
        }
        else if((TWSR & 0xF8) == TWI_SLAVE_DATA_READ_NACK)
        {
            TWCR |= (1<<TWINT);
            return TWI_NACK;
        }
        else if((TWSR & 0xF8) == TWI_SLAVE_DATA_READ_LAST)
        {
            // Not implemented
            return 0xFF;
        }
        
        return 0xFF;
    }

    //	+---------------------------------------------------------------+
    //	|			TWI slave stop/repeated start condition   			|
    //	+---------------------------------------------------------------+
    //  |    Return:    0x00        ->  Stop/Repeated start not arrived |
    //  |               0xFF        ->  Transmission complete           |
    //	+---------------------------------------------------------------+
    unsigned char twi_slave_stop(void)
    {
        // Check if controller is addressed
        if(TWCR & (1<<TWINT))
        {
            if((TWSR & 0xF8) == TWI_SLAVE_STOP_OR_REPEATED_START)
            {
                TWCR |= (1<<TWINT) | (1<<TWEA);
                return 0xFF;
            }
            
        }
        return 0x00;
    }

#endif