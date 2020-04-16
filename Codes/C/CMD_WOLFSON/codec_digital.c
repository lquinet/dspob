/**********************************************************
* NAME OF FILE: codec_digital.c
* HEADER FILES: -) main: codec_digital.h

* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

***********************************************************/



/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_digital.h"

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: codec_mic_ADC()
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
WM8731_REG_DIGITAL_IF         config digital path              digital_if
WM8731_REG_SAMPLING_CTRL      config sampling options          sampling
WM8731_REG_ACTIVE_CTRL        power on/off the DSP part        dsp
***********************************************************/
void codec_mic_ADC()
{
    /** VARIABLES DECLARATION **/
    unsigned int lrhpout;
    unsigned char analog_p;
    unsigned char digital_p;
    unsigned char power;
    unsigned char digital_if;
    unsigned char sampling;
    // unsigned char dsp;

    /** VARIABLES SETUP **/
    lrhpout =    (0<<LRHPBOTH)|
                 (0<<LZCEN)|
                 (1<<LHPVOL6)| // VOLUME
                 (1<<LHPVOL5)| // VOLUME
                 (1<<LHPVOL4)| // VOLUME
                 (1<<LHPVOL3)| // VOLUME
                 (1<<LHPVOL2)| // VOLUME
                 (1<<LHPVOL1)| // VOLUME
                 (1<<LHPVOL0); // VOLUME

    analog_p =   (0<<SIDEATT1)| // GAIN FOR SIDETONE
                 (0<<SIDEATT0)| // GAIN FOR SIDETONE
                 (0<<SIDETONE)| // SIDETONE => FOR THE MIC INPUT
                 (1<<DACSEL)|   // DAC SELECT FOR THE OUTPUT
                 (0<<BYPASS)|   // BYPASS => FOR THE LINE INPUT
                 (1<<INSEL)|    // SELECT THE INPUT TO THE ADC
                 (0<<MUTEMIC)|  // MUTE THE MIC INPUT
                 (0<<MICBOOST); // BOOST FOR THE MIC INPUT

    digital_p =  (0<<HPOR)|   // STORE DC VALUE WHEN ADCHPH IS ACTIVE
                 (0<<DACMU)|  // MUTE THE DAC OUTPUT
                 (1<<DEEMP1)|
                 (1<<DEEMP0)|
                 (0<<ADCHPD); // ACTIVATE THE OUTPUT FILTER

    // BE CAREFULE FOR THE POWER !!! 0 = ON | 1 = OFF
    power =      (0<<POWEROFF)| // FOR THE WHOLE CODEC
                 (0<<CLKOUTPD)| // FOR THE OUTPUT CLOCK
                 (0<<OSCPD)|    // FOR THE OUTPUT OSC
                 (0<<OUTPD)|    // FOR THE OUTPUT
                 (0<<DACPD)|    // FOR THE DAC
                 (0<<ADCPD)|    // FOR THE ADC
                 (0<<MICPD)|    // FOR THE MIC INPUT
                 (0<<LINEINPD); // FOR THE LINE INPUT

    digital_if = (0<<BCLKINV)| // INVERT BCLK
                 (0<<MS)|      /** SLAVE OR MASTER MODE => in slave mode for now ! **/
                 (0<<LRSWAP)|  // SWAP ADC & DAC LRC COMMUNICATION
                 (0<<LRP)|     // COMMUNICATION OPTIONS => WITH FORMAT BITS
                 (0<<IWL1)|    // BITS SAMPLING
                 (0<<IWL0)|    // BITS SAMPLING
                 (0<<FORMAT1)| // COMMUNICATION TYPE
                 (1<<FORMAT0); // COMMUNICATION TYPE

    sampling =   (0<<CLKODIV2)| // DIVIDE CLOCK OUT Acc2 CLOCK CORE
                 (0<<CLKIDIV2)| // DIVIDE CLOCK CORE Acc2 MASTER CLOCK
                 (0<<SR3)|      // SELECT FREQUENCY SAMPLE
                 (0<<SR2)|      // SELECT FREQUENCY SAMPLE
                 (0<<SR1)|      // SELECT FREQUENCY SAMPLE
                 (0<<SR0)|      // SELECT FREQUENCY SAMPLE
                 (1<<BOSR)|
                 (0<<USB_NORM); // NORMAL OR USB MODE

    // dsp =        (0<<ACTIVE); // ACTIVE OR NOT THE DSP PART

    /** COMMUNICATION **/
    I2C_init();
    codec_CMD(WM8731_REG_ACTIVE_CTRL,0);
    codec_CMD(WM8731_REG_LHPHONE_OUT,lrhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,lrhpout);
    codec_CMD(WM8731_REG_ANALOG_PATH,analog_p);
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital_p);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power);
    codec_CMD(WM8731_REG_DIGITAL_IF,digital_if);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,sampling);
    codec_CMD(WM8731_REG_ACTIVE_CTRL,1);

}

/**********************************************************
* NAME: codec_line_ADC()
* DESCRIPTION: activate the micro input for the codec
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
WM8731_REG_DIGITAL_IF         config digital path              digital_if
WM8731_REG_SAMPLING_CTRL      config sampling options          sampling
WM8731_REG_ACTIVE_CTRL        power on/off the DSP part        dsp
***********************************************************/
void codec_line_ADC()
{
    /** VARIABLES DECLARATION **/
    unsigned int lrline;
    unsigned int lrhpout;
    unsigned char analog_p;
    unsigned char digital_p;
    unsigned char power;
    unsigned char digital_if;
    unsigned char sampling;
    // unsigned char dsp;

    /** VARIABLES SETUP **/
    lrline =    (0<<LRINBOTH)|
                (0<<LINEMUTE)| // MUTE LINE INPUT
                (1<<LINVOL4)|  // VOLUME
                (0<<LINVOL3)|  // VOLUME
                (1<<LINVOL2)|  // VOLUME
                (1<<LINVOL1)|  // VOLUME
                (1<<LINVOL0);  // VOLUME

    lrhpout =    (0<<LRHPBOTH)|
                 (0<<LZCEN)|
                 (1<<LHPVOL6)| // VOLUME
                 (1<<LHPVOL5)| // VOLUME
                 (1<<LHPVOL4)| // VOLUME
                 (1<<LHPVOL3)| // VOLUME
                 (0<<LHPVOL2)| // VOLUME
                 (0<<LHPVOL1)| // VOLUME
                 (1<<LHPVOL0); // VOLUME

    analog_p =   (0<<SIDEATT1)| // GAIN FOR SIDETONE
                 (0<<SIDEATT0)| // GAIN FOR SIDETONE
                 (0<<SIDETONE)| // SIDETONE => FOR THE MIC INPUT
                 (1<<DACSEL)|   // DAC SELECT FOR THE OUTPUT
                 (0<<BYPASS)|   // BYPASS => FOR THE LINE INPUT
                 (0<<INSEL)|    // SELECT THE INPUT TO THE ADC
                 (0<<MUTEMIC)|  // MUTE THE MIC INPUT
                 (0<<MICBOOST); // BOOST FOR THE MIC INPUT

    digital_p =  (0<<HPOR)|   // STORE DC VALUE WHEN ADCHPH IS ACTIVE
                 (0<<DACMU)|  // MUTE THE DAC OUTPUT
                 (1<<DEEMP1)|
                 (1<<DEEMP0)|
                 (0<<ADCHPD); // ACTIVATE THE OUTPUT FILTER

    // BE CAREFULE FOR THE POWER !!! 0 = ON | 1 = OFF
    power =      (0<<POWEROFF)| // FOR THE WHOLE CODEC
                 (0<<CLKOUTPD)| // FOR THE OUTPUT CLOCK
                 (0<<OSCPD)|    // FOR THE OUTPUT OSC
                 (0<<OUTPD)|    // FOR THE OUTPUT
                 (0<<DACPD)|    // FOR THE DAC
                 (0<<ADCPD)|    // FOR THE ADC
                 (0<<MICPD)|    // FOR THE MIC INPUT
                 (0<<LINEINPD); // FOR THE LINE INPUT

    digital_if = (0<<BCLKINV)| // INVERT BCLK
                 (0<<MS)|      /** SLAVE OR MASTER MODE => in slave mode for now ! **/
                 (0<<LRSWAP)|  // SWAP ADC & DAC LRC COMMUNICATION
                 (0<<LRP)|     // COMMUNICATION OPTIONS => WITH FORMAT BITS
                 (0<<IWL1)|    // BITS SAMPLING
                 (0<<IWL0)|    // BITS SAMPLING
                 (0<<FORMAT1)| // COMMUNICATION TYPE
                 (1<<FORMAT0); // COMMUNICATION TYPE

    sampling =   (0<<CLKODIV2)| // DIVIDE CLOCK OUT Acc2 CLOCK CORE
                 (0<<CLKIDIV2)| // DIVIDE CLOCK CORE Acc2 MASTER CLOCK
                 (0<<SR3)|      // SELECT FREQUENCY SAMPLE
                 (0<<SR2)|      // SELECT FREQUENCY SAMPLE
                 (0<<SR1)|      // SELECT FREQUENCY SAMPLE
                 (0<<SR0)|      // SELECT FREQUENCY SAMPLE
                 (1<<BOSR)|
                 (0<<USB_NORM); // NORMAL OR USB MODE

    // dsp =        (0<<ACTIVE); // ACTIVE OR NOT THE DSP PART

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
    codec_CMD(WM8731_REG_DIGITAL_IF,digital_if);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,sampling);
    codec_CMD(WM8731_REG_ACTIVE_CTRL,1);


}

