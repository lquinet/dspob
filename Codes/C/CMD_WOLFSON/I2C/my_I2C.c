/**********************************************************
* NAME OF FILE: my_I2C.c
* HEADER FILES: -) main: my_I2C.h
                -) package: options_I2C.h

* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

    1) I2C_init()
    2) I2C_start()
    3) I2C_write(physical address of memory)

        Physical (hard) address is set by you in software.

    4) I2C_write(software address of memory)

        /!\ Sometimes it will have high and low addresses.
            Macros have been set for this in macro.h file.

    5) I2C_write(data)
    6) I2C_stop()

***********************************************************/



/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "my_I2C.h"


/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: I2C_init()
* DESCRIPTION: set values for initializing the I2C
* RETURN: none
***********************************************************/
void I2C_init() // maybe to change !
{
    // registre de bit rate:
	TWBR = 17; // TWBR*precaler = 17 pour avoir 20kHz en SCL

	// registre de contrôle:
	// TWINT TWEA TWSTA TWSTO TWWC TWEN – TWIE
	TWCR = 0b00000000; // tout les bits à 0 pour le moment

	// registre de statut:
	// TWS7 TWS6 TWS5 TWS4 TWS3 – TWPS1 TWPS0
	// prescaler à 1
	TWSR = 0b00000000;

}

/**********************************************************
* NAME: I2C_start()
* DESCRIPTION: start the I2C transmission
* RETURN: none
***********************************************************/
void I2C_start()
{
    TWCR = START_CONDITION; // start condition
    while (!(TWCR & (1<<TWINT)))    // check if interrupt
    {

    }
    if((TWSR & TW_NO_INFO) != TW_START) // check if error
    {
        ERROR_TRANSMISSION();
    }
}

/**********************************************************
* NAME: I2C_write(unsigned char data, enum OPTIONS op)
* DESCRIPTION: write data in the memory
* RETURN: none
***********************************************************/
void I2C_write(unsigned char data, enum OPTIONS op)
{
    TWDR = data;    // data in TWDR
    TWCR =  WRITE_CONDITION;   // write condition
    while (!(TWCR & (1<<TWINT)))    // check if interrupt
    {

    }
    // error implementation:
    switch(op)
    {
    case HARD_ADDR:
        if((TWSR & TW_NO_INFO) != TW_MR_SLA_ACK)    // slave acknowledge
        {
            ERROR_TRANSMISSION();
        }
        break;

    case SOFT_ADDR:
        if((TWSR & TW_NO_INFO) != TW_MR_DATA_ACK)   // softwares addresses are considered as datas
        {
            ERROR_TRANSMISSION();
        }
        break;

    case WR_DATA:
        if((TWSR & TW_NO_INFO) != TW_MR_DATA_ACK)   // data acknowledge
        {
            ERROR_TRANSMISSION();
        }
        break;

    default:
        ERROR_TRANSMISSION();
    }

}

/**********************************************************
* NAME: I2C_stop()
* DESCRIPTION: stop the I2C transmission
* RETURN: none
***********************************************************/
void I2C_stop()
{
    TWCR = STOP_CONDITION;  // stop condition

}

/**********************************************************
* NAME: ERROR_TRANSMISSION()
* DESCRIPTION: to change
* RETURN: to change
***********************************************************/
void ERROR_TRANSMISSION()
{
    // insert your code here
    // i.e. LCD, USART or diodes

}



