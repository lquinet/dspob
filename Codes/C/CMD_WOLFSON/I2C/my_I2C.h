#ifndef I2C_H_INCLUDED

/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include <util/twi.h>   // for protection codes
#include "options_I2C.h"    // for writing options

#define I2C_H_INCLUDED

/**********************************************************
* FUNCTION PROTOTYPES:
***********************************************************/
void I2C_init();
void I2C_start();
void I2C_write(unsigned char data, enum OPTIONS op);
void I2C_stop();
void ERROR_TRANSMISSION();

/**********************************************************
* MISC:
***********************************************************/
/**********************************************************
* TWCR REGISTER:
TWINT   TWEA    TWSTA   TWSTO   TWWC    TWEN    –   TWIE
***********************************************************/
// START: TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
#define START_CONDITION     0b10100100
// STOP: TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
#define STOP_CONDITION      0b10010100
// WRITE: TWCR = (1<<TWINT)|(1<<TWEN);
#define WRITE_CONDITION     0b10000100


#endif // I2C_H_INCLUDED
