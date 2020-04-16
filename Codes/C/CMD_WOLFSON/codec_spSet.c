/**********************************************************
* NAME OF FILE: codec_spSet.c
* HEADER FILES: -) main: codec_spSet.h
                -) package :  options_spSet

* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

***********************************************************/



/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_spSet.h"

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: set_format_DSP(unsigned char *digital_if)
* DESCRIPTION: set the DSP to DSP mode
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_format_DSP(unsigned char *digital_if)
{
    sbiBF(*digital_if,FORMAT1);
    sbiBF(*digital_if,FORMAT0);
}

/**********************************************************
* NAME: set_format_I2S(unsigned char *digital_if)
* DESCRIPTION: set the DSP to I2S mode
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_format_I2S(unsigned char *digital_if)
{
    sbiBF(*digital_if,FORMAT1);
    cbiBF(*digital_if,FORMAT0);
}

/**********************************************************
* NAME: set_format_MSBLJ(unsigned char *digital_if)
* DESCRIPTION: set the DSP to MSB Left Justified
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_format_MSBLJ(unsigned char *digital_if)
{
    cbiBF(*digital_if,FORMAT1);
    sbiBF(*digital_if,FORMAT0);
}

/**********************************************************
* NAME: set_format_MSBRJ(unsigned char *digital_if)
* DESCRIPTION: set the DSP to MSB Right Justified
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_format_MSBRJ(unsigned char *digital_if)
{
    cbiBF(*digital_if,FORMAT1);
    cbiBF(*digital_if,FORMAT0);
}

/**********************************************************
* NAME: set_format(unsigned char *digital_if, enum OPTIONS_DSP_SETUP opDSP)
* DESCRIPTION: set the DSP to DSP mode
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_format(unsigned char *digital_if, enum OPTIONS_DSP_SETUP opDSP)
{
    switch(opDSP)
    {
    case DSP:
        set_format_DSP(digital_if);
        break;

    case I2S:
        set_format_I2S(digital_if);
        break;

    case MSBLJ:
        set_format_MSBLJ(digital_if);
        break;

    case MSBRJ:
        set_format_MSBRJ(digital_if);
        break;
    }
}

/**********************************************************
* NAME: set_data_16bits(unsigned char * digital_if)
* DESCRIPTION: set data bit length to 16 bits
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_data_16bits(unsigned char *digital_if)
{
    cbiBF(*digital_if,IWL1);
    cbiBF(*digital_if,IWL0);
}

/**********************************************************
* NAME: set_data_20bits(unsigned char * digital_if)
* DESCRIPTION: set data bit length to 20 bits
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_data_20bits(unsigned char *digital_if)
{
    cbiBF(*digital_if,IWL1);
    sbiBF(*digital_if,IWL0);
}

/**********************************************************
* NAME: set_data_24bits(unsigned char * digital_if)
* DESCRIPTION: set data bit length to 24 bits
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_data_24bits(unsigned char *digital_if)
{
    sbiBF(*digital_if,IWL1);
    cbiBF(*digital_if,IWL0);
}

/**********************************************************
* NAME: set_data_32bits(unsigned char * digital_if)
* DESCRIPTION: set data bit length to 32 bits
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_data_32bits(unsigned char *digital_if)
{
    sbiBF(*digital_if,IWL1);
    sbiBF(*digital_if,IWL0);
}

/**********************************************************
* NAME: set_data(unsigned char *digital_if, enum OPTIONS_DATA_BIT opDATA)
* DESCRIPTION: set data bit length
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_data(unsigned char *digital_if, enum OPTIONS_DATA_BIT opDATA)
{
    switch(opDATA)
    {
    case BIT16:
        set_data_16bits(digital_if);
        break;

    case BIT20:
        set_data_20bits(digital_if);
        break;

    case BIT24:
        set_data_24bits(digital_if);
        break;

    case BIT32:
        set_data_32bits(digital_if);
        break;
    }

}

/**********************************************************
* NAME: set_fs_8(unsigned char *sampling)
* DESCRIPTION: set ADC & DAC frequency sample to 8kHz
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs_8(unsigned char *sampling)
{
    cbiBF(*sampling,SR3);
    cbiBF(*sampling,SR2);
    sbiBF(*sampling,SR1);
    sbiBF(*sampling,SR0);
}

/**********************************************************
* NAME: set_fs_32(unsigned char *sampling)
* DESCRIPTION: set ADC & DAC frequency sample to 32kHz
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs_32(unsigned char *sampling)
{
    cbiBF(*sampling,SR3);
    sbiBF(*sampling,SR2);
    sbiBF(*sampling,SR1);
    cbiBF(*sampling,SR0);
}

/**********************************************************
* NAME: set_fs_441(unsigned char *sampling)
* DESCRIPTION: set ADC & DAC frequency sample to 44.1kHz
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs_441(unsigned char *sampling)
{
    sbiBF(*sampling,SR3);
    cbiBF(*sampling,SR2);
    cbiBF(*sampling,SR1);
    cbiBF(*sampling,SR0);
}

/**********************************************************
* NAME: set_fs_48(unsigned char *sampling)
* DESCRIPTION: set ADC & DAC frequency sample to 48kHz
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs_48(unsigned char *sampling)
{
    cbiBF(*sampling,SR3);
    cbiBF(*sampling,SR2);
    cbiBF(*sampling,SR1);
    cbiBF(*sampling,SR0);
}

/**********************************************************
* NAME: set_fs_882(unsigned char *sampling)
* DESCRIPTION: set ADC & DAC frequency sample to 88.2kHz
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs_882(unsigned char *sampling)
{
    sbiBF(*sampling,SR3);
    sbiBF(*sampling,SR2);
    sbiBF(*sampling,SR1);
    sbiBF(*sampling,SR0);
}

/**********************************************************
* NAME: set_fs_96(unsigned char *sampling)
* DESCRIPTION: set ADC & DAC frequency sample to 96kHz
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs_96(unsigned char *sampling)
{
    cbiBF(*sampling,SR3);
    sbiBF(*sampling,SR2);
    sbiBF(*sampling,SR1);
    sbiBF(*sampling,SR0);
}

/**********************************************************
* NAME: set_fs_96(unsigned char *sampling, enum OPTIONS_FS opFS)
* DESCRIPTION: set ADC & DAC frequency sample
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: CLEAN
***********************************************************/
void set_fs(unsigned char *sampling, enum OPTIONS_FS opFS)
{
    switch(opFS)
    {
    case FS8:
        set_fs_8(sampling);
        break;

    case FS32:
        set_fs_32(sampling);
        break;

    case FS441:
        set_fs_441(sampling);
        break;

    case FS48:
        set_fs_48(sampling);
        break;

    case FS882:
        set_fs_882(sampling);
        break;

    case FS96:
        set_fs_96(sampling);
        break;
    }
}



