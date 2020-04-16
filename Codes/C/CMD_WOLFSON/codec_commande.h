#ifndef CODEC_COMMANDE_H_INCLUDED

/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "I2C/my_I2C.h"
#include "codec_registers.h"
#include "macro.h"

#define CODEC_COMMANDE_H_INCLUDED

/**********************************************************
* FUNCTION PROTOTYPES:
***********************************************************/
void codec_CMD(char address, unsigned int cmd);


#endif // CODEC_COMMANDE_H_INCLUDED
