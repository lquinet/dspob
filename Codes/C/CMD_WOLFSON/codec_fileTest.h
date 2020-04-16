#ifndef CODEC_FILETEST_H_INCLUDED

/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_commande.h"
#include "I2C/my_I2C.h"
// #include <util/delay.h>


#define CODEC_FILETEST_H_INCLUDED

/**********************************************************
* FUNCTION PROTOTYPES:
***********************************************************/
void codec_bypass();
void codec_linein_bypass();
void codec_test2();
void codec_ADCDAC();
void codec_default();


#endif // CODEC_FILETEST_H_INCLUDED
