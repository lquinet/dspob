/**********************************************************
* NAME OF FILE: codec_commande
* HEADER FILES: -) main: codec_commande.h


* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

***********************************************************/



/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_commande.h"

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: codec_CMD(char address, unsigned int cmd)
* DESCRIPTION: create a frame to send to the codec
* RETURN: none
***********************************************************/
void codec_CMD(char address, unsigned int cmd)
{
    char addr;
    // B[15:9] Are Control Address Bits
    // B[8:0]  Are Control Data Bits
    addr = address << 1;                            // Shift left for one positions
    addr = addr | (getHigh(cmd) & 1);

    I2C_start();                                    // Start I2C2 module
    I2C_write(WM8731_ADDRESS,HARD_ADDR);            // Write Address of WM8731 chip
    I2C_write(addr,SOFT_ADDR);                      // Write register address
    I2C_write(getLow(cmd),WR_DATA);                 // Write command
    I2C_stop();                                     // Stop I2C2 module

}


