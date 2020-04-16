/**********************************************************
* GET MORE INFORMATIONS: see doc "registerTable.xlsx"
***********************************************************/

#ifndef CODEC_ADDR_H_INCLUDED
#define CODEC_ADDR_H_INCLUDED

/**********************************************************
* CODEC REGISTER ADDRESS:
***********************************************************/
#define     WM8731_ADDRESS              0x34              // WM8731 chip address on I2C bus
#define     WM8731_ADDRESS_FPGA         0x35              // WM8731 chip address for FPGA => NOPE THAT'S BULLSHIT !!!
/**
* WHERE IS IT IN THE DATASHEET ? => I'VE FOUND IT :D! PAGE 43
* BE CAREFUL ! THERE ARE 2 ADDRESSES :
* FOR WRITING (THE ONE WE USE)
* FOR READING
**/
#define     WM8731_REG_LLINE_IN         0b00000000        // Left Channel Line Input Volume Control
#define     WM8731_REG_RLINE_IN         0b00000001        // Right Channel Line Input Volume Control
#define     WM8731_REG_LHPHONE_OUT      0b00000010        // Left Channel Headphone Output Volume Control
#define     WM8731_REG_RHPHONE_OUT      0b00000011        // Right Channel Headphone Output Volume Control
#define     WM8731_REG_ANALOG_PATH      0b00000100        // Analog Audio Path Control
#define     WM8731_REG_DIGITAL_PATH     0b00000101        // Digital Audio Path Control
#define     WM8731_REG_PDOWN_CTRL       0b00000110        // Power Down Control Register
#define     WM8731_REG_DIGITAL_IF       0b00000111        // Digital Audio Interface Format
#define     WM8731_REG_SAMPLING_CTRL    0b00001000        // Sampling Control Register
#define     WM8731_REG_ACTIVE_CTRL      0b00001001        // Active Control
#define     WM8731_REG_RESET            0b00001111        // Reset register

/**********************************************************
* CODEC DEFAULT VALUES:
***********************************************************/
#define     WM8731_reg_lline_in         0b010010111
#define     WM8731_reg_rline_in         0b010010111
#define     WM8731_reg_lhphone_out      0b001111001
#define     WM8731_reg_rhphone_out      0b001111001
#define     WM8731_reg_analog_path      0b00001010
#define     WM8731_reg_digital_path     0b00001000
#define     WM8731_reg_pdown_ctrl       0b10011111
#define     WM8731_reg_digital_if       0b00001010
#define     WM8731_reg_sampling_ctrl    0
#define     WM8731_reg_active_ctrl      0
#define     WM8731_reg_reset            0


/**********************************************************
* CODEC REGISTER BITS (to use with "sbiBF & cbiBF"):
***********************************************************/
//  * LLINE_IN *  //
#define     LRINBOTH    8
#define     LINEMUTE    7
#define     LINVOL4     4
#define     LINVOL3     3
#define     LINVOL2     2
#define     LINVOL1     1
#define     LINVOL0     0

//  * RLINE_IN *  //
#define     RLINBOTH    8
#define     RINEMUTE    7
#define     RINVOL4     4
#define     RINVOL3     3
#define     RINVOL2     2
#define     RINVOL1     1
#define     RINVOL0     0

//  * LHPHONE_OUT *  //
#define     LRHPBOTH    8
#define     LZCEN       7
#define     LHPVOL6     6
#define     LHPVOL5     5
#define     LHPVOL4     4
#define     LHPVOL3     3
#define     LHPVOL2     2
#define     LHPVOL1     1
#define     LHPVOL0     0

//  * RHPHONE_OUT *  //
#define     RLHPBOTH    8
#define     RZCEN       7
#define     RHPVOL6     6
#define     RHPVOL5     5
#define     RHPVOL4     4
#define     RHPVOL3     3
#define     RHPVOL2     2
#define     RHPVOL1     1
#define     RHPVOL0     0

//  * ANALOG_PATH *  //
#define     SIDEATT1    7
#define     SIDEATT0    6
#define     SIDETONE    5
#define     DACSEL      4
#define     BYPASS      3
#define     INSEL       2
#define     MUTEMIC     1
#define     MICBOOST    0

//  * DIGITAL_PATH *  //
#define     HPOR        4
#define     DACMU       3
#define     DEEMP1      2
#define     DEEMP0      1
#define     ADCHPD      0

//  * POWER_CTRL *  //
#define		POWEROFF    7
#define		CLKOUTPD	6
#define		OSCPD		5
#define		OUTPD		4
#define		DACPD		3
#define		ADCPD		2
#define		MICPD		1
#define		LINEINPD	0

#define     PW_ON        0
#define     PW_OFF       1

//  * DIGITAL_IF *  //
#define     BCLKINV     7
#define     MS          6
#define     LRSWAP      5
#define     LRP         4
#define     IWL1        3
#define     IWL0        2
#define     FORMAT1     1
#define     FORMAT0     0

//  * SAMPLING_CTRL *  //
#define     CLKIDIV2    7
#define     CLKODIV2    6
#define		SR3			5
#define		SR2			4
#define		SR1			3
#define		SR0			2
#define		BOSR		1
#define		USB_NORM	0

//  * ACTIVE_CTRL *  //
#define		ACTIVE		1


#endif // CODEC_ADDR_H_INCLUDED
