/**********************************************************
* NAME OF FILE: codec_analogue.c
* HEADER FILES: -) main: codec_analogue.h

* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

***********************************************************/



/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_analogue.h"

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: codec_mic()
* DESCRIPTION: activate the micro input for the codec
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: IWW!
***********************************************************/
/**********************************************************
* REGISTERS USED:
|REGISTER|********************|DESCRIPTION|********************|VARIABLE NAME|
WM8731_REG_LHPHONE_OUT        left output channel              lrhpout
WM8731_REG_RHPHONE_OUT        right output channel             lrhpout
WM8731_REG_ANALOG_PATH        config analog path               analog_p
WM8731_REG_DIGITAL_PATH       config filtering option          digital_p
WM8731_REG_PDOWN_CTRL         power on/off inputs & outputs    power
WM8731_REG_ACTIVE_CTRL        power on/off the DSP part        dsp
***********************************************************/
void codec_mic()
{
    /** VARIABLES DECLARATION **/
    unsigned int lrhpout;
    unsigned char analog_p;
    unsigned char digital_p;
    unsigned char power;
    // unsigned char dsp;

    /** VARIABLES SETUP **/
    lrhpout =   (0<<LRHPBOTH)|
                (1<<LZCEN)|
                (1<<LHPVOL6)| // VOLUME
                (1<<LHPVOL5)| // VOLUME
                (1<<LHPVOL4)| // VOLUME
                (1<<LHPVOL3)| // VOLUME
                (1<<LHPVOL2)| // VOLUME
                (1<<LHPVOL1)| // VOLUME
                (1<<LHPVOL0); // VOLUME

    analog_p =  (0<<SIDEATT1)| // GAIN FOR SIDETONE
                (0<<SIDEATT0)| // GAIN FOR SIDETONE
                (1<<SIDETONE)| // SIDETONE => FOR THE MIC INPUT
                (0<<DACSEL)|   // DAC SELECT FOR THE OUTPUT
                (0<<BYPASS)|   // BYPASS => FOR THE LINE INPUT
                (1<<INSEL)|    // SELECT THE INPUT TO THE ADC
                (0<<MUTEMIC)|  // MUTE THE MIC INPUT
                (0<<MICBOOST); // BOOST FOR THE MIC INPUT

    digital_p = (0<<HPOR)|   // STORE DC VALUE WHEN ADCHPH IS ACTIVE
                (0<<DACMU)|  // MUTE THE DAC OUTPUT
                (0<<DEEMP1)|
                (0<<DEEMP0)|
                (1<<ADCHPD); // ACTIVATE THE OUTPUT FILTER

    // BE CAREFULE FOR THE POWER !!! 0 = ON | 1 = OFF
    power =     (0<<POWEROFF)| // FOR THE WHOLE CODEC
                (1<<CLKOUTPD)| // FOR THE OUTPUT CLOCK
                (1<<OSCPD)|    // FOR THE OUTPUT OSC
                (0<<OUTPD)|    // FOR THE OUTPUT
                (1<<DACPD)|    // FOR THE DAC
                (1<<ADCPD)|    // FOR THE ADC
                (0<<MICPD)|    // FOR THE MIC INPUT
                (1<<LINEINPD); // FOR THE LINE INPUT

    // dsp =       (0<<ACTIVE); // ACTIVE OR NOT THE DSP PART

    /** COMMUNICATION **/
    I2C_init();
    codec_CMD(WM8731_REG_LLINE_IN,WM8731_reg_lline_in); // DEFAULT VALUES
    codec_CMD(WM8731_REG_RLINE_IN,WM8731_reg_rline_in); // DEFAULT VALUES
    codec_CMD(WM8731_REG_ACTIVE_CTRL,0);
    codec_CMD(WM8731_REG_LHPHONE_OUT,lrhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,lrhpout);
    codec_CMD(WM8731_REG_ANALOG_PATH,analog_p);
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital_p);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power);
    codec_CMD(WM8731_REG_DIGITAL_IF,WM8731_reg_digital_if); // DEFAULT VALUES
    codec_CMD(WM8731_REG_SAMPLING_CTRL,WM8731_reg_sampling_ctrl); // DEFAULT VALUES

}

/**********************************************************
* NAME: codec_line()
* DESCRIPTION: activate the line input for the codec
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: IWW!
***********************************************************/
/**********************************************************
* REGISTERS USED:
|REGISTER|********************|DESCRIPTION|********************|VARIABLE NAME|
WM8731_REG_LLINE_IN           left input channel               lrline
WM8731_REG_RLINE_IN           left input channel               lrline
WM8731_REG_LHPHONE_OUT        left output channel              lrhpout
WM8731_REG_RHPHONE_OUT        right output channel             lrhpout
WM8731_REG_ANALOG_PATH        config analog path               analog_p
WM8731_REG_DIGITAL_PATH       config filtering option          digital_p
WM8731_REG_PDOWN_CTRL         power on/off inputs & outputs    power
WM8731_REG_ACTIVE_CTRL        power on/off the DSP part        dsp
***********************************************************/
void codec_line()
{
    /** VARIABLES DECLARATION **/
    unsigned int lrline;
    unsigned int lrhpout;
    unsigned char analog_p;
    unsigned char digital_p;
    unsigned char power;
    // unsigned char dsp;

    /** VARIABLES SETUP **/
    lrline =    (0<<LRINBOTH)|
                (0<<LINEMUTE)| // MUTE LINE INPUT
                (1<<LINVOL4)|  // VOLUME
                (0<<LINVOL3)|  // VOLUME
                (1<<LINVOL2)|  // VOLUME
                (1<<LINVOL1)|  // VOLUME
                (1<<LINVOL0);  // VOLUME

    lrhpout =   (0<<LRHPBOTH)|
                (1<<LZCEN)|
                (1<<LHPVOL6)| // VOLUME
                (1<<LHPVOL5)| // VOLUME
                (1<<LHPVOL4)| // VOLUME
                (1<<LHPVOL3)| // VOLUME
                (0<<LHPVOL2)| // VOLUME
                (0<<LHPVOL1)| // VOLUME
                (1<<LHPVOL0); // VOLUME

    analog_p =  (0<<SIDEATT1)| // GAIN FOR SIDETONE
                (0<<SIDEATT0)| // GAIN FOR SIDETONE
                (0<<SIDETONE)| // SIDETONE => FOR THE MIC INPUT
                (0<<DACSEL)|   // DAC SELECT FOR THE OUTPUT
                (1<<BYPASS)|   // BYPASS => FOR THE LINE INPUT
                (0<<INSEL)|    // SELECT THE INPUT TO THE ADC
                (0<<MUTEMIC)|  // MUTE THE MIC INPUT
                (0<<MICBOOST); // BOOST FOR THE MIC INPUT

    digital_p = (0<<HPOR)|   // STORE DC VALUE WHEN ADCHPH IS ACTIVE
                (0<<DACMU)|  // MUTE THE DAC OUTPUT
                (0<<DEEMP1)|
                (0<<DEEMP0)|
                (1<<ADCHPD); // ACTIVATE THE OUTPUT FILTER

    // BE CAREFULE FOR THE POWER !!! 0 = ON | 1 = OFF
    power =     (0<<POWEROFF)| // FOR THE WHOLE CODEC
                (1<<CLKOUTPD)| // FOR THE OUTPUT CLOCK
                (1<<OSCPD)|    // FOR THE OUTPUT OSC
                (0<<OUTPD)|    // FOR THE OUTPUT
                (1<<DACPD)|    // FOR THE DAC
                (1<<ADCPD)|    // FOR THE ADC
                (1<<MICPD)|    // FOR THE MIC INPUT
                (0<<LINEINPD); // FOR THE LINE INPUT

    // dsp =       (0<<ACTIVE); // ACTIVE OR NOT THE DSP PART

    /** COMMUNICATION **/
    I2C_init();
    codec_CMD(WM8731_REG_ACTIVE_CTRL,0);
    codec_CMD(WM8731_REG_LLINE_IN,lrline);
    codec_CMD(WM8731_REG_RLINE_IN,lrline);
    codec_CMD(WM8731_REG_LHPHONE_OUT,lrhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,lrhpout);
    codec_CMD(WM8731_REG_ANALOG_PATH,analog_p);
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital_p);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power);
    codec_CMD(WM8731_REG_DIGITAL_IF,WM8731_reg_digital_if); // DEFAULT VALUES
    codec_CMD(WM8731_REG_SAMPLING_CTRL,WM8731_reg_sampling_ctrl); // DEFAULT VALUES

}
