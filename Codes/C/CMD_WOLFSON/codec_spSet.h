#ifndef CODEC_SPSET_H_INCLUDED

/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_registers.h"
#include "macro.h"
#include "options_spSet.h"

#define CODEC_SPSET_H_INCLUDED
/**********************************************************
* FUNCTION PROTOTYPES:
***********************************************************/
/** DSP COMMUNICATION **/
void set_format_DSP(unsigned char *digital_if);
void set_format_I2S(unsigned char *digital_if);
void set_format_MSBLJ(unsigned char *digital_if);
void set_format_MSBRJ(unsigned char *digital_if);
void set_format(unsigned char *digital_if, enum OPTIONS_DSP_SETUP opDSP);

/** DATA BIT LENGTH **/
void set_data_16bits(unsigned char *digital_if);
void set_data_20bits(unsigned char *digital_if);
void set_data_24bits(unsigned char *digital_if);
void set_data_32bits(unsigned char *digital_if);
void set_data(unsigned char *digital_if, enum OPTIONS_DATA_BIT opDATA);

/** FREQUENCY SAMPLE **/
void set_fs_8(unsigned char *sampling);
void set_fs_32(unsigned char *sampling);
void set_fs_441(unsigned char *sampling);
void set_fs_48(unsigned char *sampling);
void set_fs_882(unsigned char *sampling);
void set_fs_96(unsigned char *sampling);
void set_fs(unsigned char *sampling, enum OPTIONS_FS opFS);




#endif // CODEC_SPSET_H_INCLUDED
