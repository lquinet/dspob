/**********************************************************
* NAME OF FILE: codec_fileTest.c
* HEADER FILES: -) main: codec_fileTest.h

* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

***********************************************************/



/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "codec_fileTest.h"

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: codec_bypass()
* DESCRIPTION: bypass
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: IT WORKS WELL!
***********************************************************/
void codec_bypass()
{
    unsigned int LRlinein       = 0b010010111;       // line in left & right
    // this command is useless ; LINEIN inputs are not used !
    // just set the MICIN input with the analog register
    unsigned int LRhpout        = 0b011111111;       // hp left & right
    unsigned char analogue      = 0b00100010;        // analogue path
    unsigned char digital       = 0b00000001;        // digital path
    unsigned char power         = 0b01101100;        // disable power down

    I2C_init();
    codec_CMD(WM8731_REG_LLINE_IN,LRlinein); // useless
    codec_CMD(WM8731_REG_RLINE_IN,LRlinein); // useless
    codec_CMD(WM8731_REG_LHPHONE_OUT,LRhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,LRhpout);
    // the 2 outputs are set with +6dB (due to the -6dB in "SIDETONE")
    codec_CMD(WM8731_REG_ANALOG_PATH,analogue); // set the MICIN input
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power); // disable power down, MICIN and OUTPD
    codec_CMD(WM8731_REG_DIGITAL_IF,WM8731_reg_digital_if);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,WM8731_reg_sampling_ctrl);
    codec_CMD(WM8731_REG_ACTIVE_CTRL,0);

}

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: codec_linein_bypass()
* DESCRIPTION: bypass with line in
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: TESTING
***********************************************************/
void codec_linein_bypass()
{
    unsigned int LRlinein       = 0b010010111;       // line in left & right

    unsigned int LRhpout        = 0b011111001;       // hp left & right
    unsigned char analogue      = 0b00001000;        // analogue path
    // sidetone set off
    // bypass set on
    // mic input set off
    unsigned char digital       = 0b00000001;        // digital path
    unsigned char power         = 0b01101110;        // disable power down
    // mic input power set off

    I2C_init();
    codec_CMD(WM8731_REG_LLINE_IN,LRlinein); // useless
    codec_CMD(WM8731_REG_RLINE_IN,LRlinein); // useless
    codec_CMD(WM8731_REG_LHPHONE_OUT,LRhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,LRhpout);
    // the 2 outputs are set with +6dB (due to the -6dB in "SIDETONE")
    codec_CMD(WM8731_REG_ANALOG_PATH,analogue); // set the MICIN input
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power); // disable power down, MICIN and OUTPD
    codec_CMD(WM8731_REG_DIGITAL_IF,WM8731_reg_digital_if);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,WM8731_reg_sampling_ctrl);
    codec_CMD(WM8731_REG_ACTIVE_CTRL,0);

}

/**********************************************************
* NAME: codec_test2()
* DESCRIPTION: test2 ;  this function was used to test
* some options of the codec and to understand them
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: TESTING
***********************************************************/
void codec_test2()
{
    unsigned int Llinein        = 0b010010111;       // line in left
    unsigned int Rlinein        = 0b010010111;       // line in right
    /******************************************
    * these registers are useless
    ******************************************/

    unsigned int Lhpout         = 0b011110000;       // hp left
    unsigned int Rhpout         = 0b011110000;       // hp right
    unsigned char analogue      = 0b00100010;        // anal path
    unsigned char digital       = 0b00000001;        // digital path
    unsigned char power         = 0b01101100;        // disable power down

    I2C_init();
    codec_CMD(WM8731_REG_LLINE_IN,Llinein);
    codec_CMD(WM8731_REG_RLINE_IN,Rlinein);
    codec_CMD(WM8731_REG_LHPHONE_OUT,Lhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,Rhpout);
    codec_CMD(WM8731_REG_ANALOG_PATH,analogue);
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power);
    codec_CMD(WM8731_REG_DIGITAL_IF,WM8731_reg_digital_if);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,WM8731_reg_sampling_ctrl);

}

/**********************************************************
* NAME: codec_ADCDAC()
* DESCRIPTION: tests of ADC-DAC path
* RETURN: none
***********************************************************/
/**********************************************************
* STATE: TESTING
***********************************************************/
void codec_ADCDAC()
{

    unsigned int RLhpout        = 0b011111001;
    unsigned char analog        = 0b00010100;
    unsigned char digital       = 0b00000001;
    unsigned char power         = 0b01000001;
    unsigned char digital_if1   = 0b01011010;
    // unsigned char digital_if2   = 0b01000000;
    // unsigned char sampling8       = 0b00001100;
    unsigned char sampling48      = 0b00000000;
    // unsigned char sampling48div      = 0b11000000;
    // unsigned char sampling96      = 0b00011100;

    // many variables to test the output with different configurations


    I2C_init();
    codec_CMD(WM8731_REG_LHPHONE_OUT,RLhpout);
    codec_CMD(WM8731_REG_RHPHONE_OUT,RLhpout);
    codec_CMD(WM8731_REG_ANALOG_PATH,analog);
    codec_CMD(WM8731_REG_DIGITAL_PATH,digital);
    codec_CMD(WM8731_REG_PDOWN_CTRL,power);
    codec_CMD(WM8731_REG_DIGITAL_IF,digital_if1);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,sampling48);
    codec_CMD(WM8731_REG_ACTIVE_CTRL,ACTIVE); // active the DSP part even if it doesn't exist !



}


/**********************************************************
* NAME: codec_default()
* DESCRIPTION: set all default option
* RETURN: none
***********************************************************/
void codec_default()
{
    I2C_init();
    codec_CMD(WM8731_REG_RESET,WM8731_reg_reset);
    codec_CMD(WM8731_REG_LLINE_IN,WM8731_reg_lline_in);
    codec_CMD(WM8731_REG_RLINE_IN,WM8731_reg_rline_in);
    codec_CMD(WM8731_REG_LHPHONE_OUT,WM8731_reg_lhphone_out);
    codec_CMD(WM8731_REG_RHPHONE_OUT,WM8731_reg_rhphone_out);
    codec_CMD(WM8731_REG_ANALOG_PATH,WM8731_reg_analog_path);
    codec_CMD(WM8731_REG_DIGITAL_PATH,WM8731_reg_digital_path);
    codec_CMD(WM8731_REG_PDOWN_CTRL,WM8731_reg_pdown_ctrl);
    codec_CMD(WM8731_REG_DIGITAL_IF,WM8731_reg_digital_if);
    codec_CMD(WM8731_REG_SAMPLING_CTRL,WM8731_reg_sampling_ctrl);
    codec_CMD(WM8731_REG_ACTIVE_CTRL,WM8731_reg_active_ctrl);

}
