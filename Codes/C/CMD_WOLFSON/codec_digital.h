#ifndef CODEC_DIGITAL_H_INCLUDED

/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_commande.h"
#include "I2C/my_I2C.h"
// #include <util/delay.h>
#include "codec_spSet.h"

#define CODEC_DIGITAL_H_INCLUDED

/**********************************************************
* FUNCTION PROTOTYPES:
***********************************************************/
void codec_mic_ADC();
void codec_line_ADC();


#endif // CODEC_DIGITAL_H_INCLUDED
