-- TOP LEVEL FILE:
-- There are in this top level file:
-- -) I2C communication between the codec and the FPGA
-- -) PLL to convert a 28.63MHz oscillator clock to 18.432MHz useful clock
-- -) the DSP block (different accoring to the project)

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DSPOB_COM is
	port
	(
		iDSPOB_RST   	  : in std_logic; -- the big reset
		iDSPOB_CLK28 	  : in std_logic; -- the big master oscilltor clock
		
		iDSPOB_SDA   	  : in std_logic; -- input I2C data from the µc 			  => from a gpio
		iDSPOB_SCL   	  : in std_logic; -- input I2C master clock from the µc    => from a gpio
		oDSPOB_SDA   	  : out std_logic; -- output I2C data to the codec 			 
		oDSPOB_SCL       : out std_logic; -- output I2C master clock to the codec 
		
		oDSPOB_WM8731CLK : out std_logic; -- output master clock to control the codec
		iDSPOB_ADCdata   : in std_logic; -- input sampled data from the codec
		oDSPOB_DACdata   : out std_logic; -- output sampled data to the codec
		oDSPOB_BCLK		  : out std_logic; -- output bit clock to control the codec
		oDSPOB_ADCLRC    : out std_logic; -- output ADC left/right clock to control ADC data flow
		oDSPOB_DACLRC    : out std_logic; -- output DAC left/right clock to control DAC data flow

		-- GPIO OUTPUTS:
		oGPIO_MCLK		  : out std_logic;
		oGPIO_BCLK       : out std_logic;
		oGPIO_ADCLRC     : out std_logic;
		oGPIO_DACLRC     : out std_logic;
		oGPIO_ADCdata    : out std_logic;
		oGPIO_DACdata    : out std_logic		
	);
end entity;

--==================================================================================================--
------------------------------------------------------------------------------------------------------
--==================================================================================================--

architecture DSPOBtopLevel of DSPOB_COM is
	-- SIGNALS DESCRIPTION:
	signal sDSPOB_RST 	  : std_logic;
		
	signal sDSPOB_PLLout   : std_logic; -- output of the PLL ; used to match oDSPOB_WM8731CLK and sDSPOB_MCLK
	signal sDSPOB_MCLK     : std_logic;
	
	signal sDSPOB_BCLK     : std_logic;
	signal sDSPOB_ADCLRC   : std_logic;
	signal sDSPOB_DACLRC   : std_logic;
	signal sDSPOB_ADCdata  : std_logic;
	signal sDSPOB_DACdata  : std_logic;
	
	-- COMPONENTS DESCRIPTION:
------------------------------------------------------------------------------------------------------
	-- I2C COMMUNICATION:
	component I2C_COM is
		port
		(
			-- Input ports
			iSDA : in std_logic;  -- E29 IO_A [6]
			iSCL : in std_logic;  -- E27 IO_A [4]

			-- Output ports
			oSDA : out std_logic; -- H18
			oSCL : out std_logic  -- J18
		);
	end component;
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
	-- PLL 28.63Mhz to 18.432MHz:
	component PLL_MFILE is
		PORT
		(
			areset		: IN STD_LOGIC  := '0';
			inclk0		: IN STD_LOGIC  := '0';
			c0		: OUT STD_LOGIC 
		);
	end component;	
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
	-- DSP BLOCK:
	component DSP_BLOCK is
		port
		(
			iDSP_RST  : in std_logic; -- mid brother reset
			iDSP_MCLK : in std_logic; -- master clock to generate all 3 other clocks
			
			iDSP_ADCdata : in std_logic; -- input ADC sampled data from the codec
			oDSP_DACdata : out std_logic; -- output DAC samped data to the codec
			oDSP_BCLK    : out std_logic; -- output bit clock to control data flow
			oDSP_ADCLRC  : out std_logic; -- output ADC left/right clock to control ADC data flow
			oDSP_DACLRC  : out std_logic -- output DAC left/right clock to control DAC data flow	
		);
	end component;
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
	-- GPIO FOR DSP SIGNALS:
	component GPIO_COMP is
		port
		(
			iGPIO_MCLK    : in std_logic;
			
			iGPIO_BCLK    : in std_logic;
			iGPIO_ADCLRC  : in std_logic;
			iGPIO_DACLRC  : in std_logic;
			iGPIO_ADCin   : in std_logic;
			iGPIO_DACout  : in std_logic;
			
			oGPIO_MCLK    : out std_logic;
			
			oGPIO_BCLK    : out std_logic;
			oGPIO_ADCLRC  : out std_logic;
			oGPIO_DACLRC  : out std_logic;
			oGPIO_ADCin   : out std_logic;
			oGPIO_DACout  : out std_logic		
		);
	end component;
------------------------------------------------------------------------------------------------------
	
--==================================================================================================--
------------------------------------------------------------------------------------------------------
--==================================================================================================--
	
begin
	-- PROCESSES DESCRIPTION:
	sDSPOB_RST       <= iDSPOB_RST;
	sDSPOB_MCLK		  <= sDSPOB_PLLout;
	
	oDSPOB_WM8731CLK <= sDSPOB_MCLK;
	oDSPOB_BCLK      <= sDSPOB_BCLK;
	oDSPOB_ADCLRC    <= sDSPOB_ADCLRC;
	oDSPOB_DACLRC    <= sDSPOB_DACLRC;
	sDSPOB_ADCdata   <= iDSPOB_ADCdata;
	oDSPOB_DACdata   <= sDSPOB_DACdata;
		
	-- COMPONENTS DESCRIPTION:
------------------------------------------------------------------------------------------------------
	-- I2C COMMUNICATION:
	I2C_COMinst : I2C_COM port map(iDSPOB_SDA, iDSPOB_SCL, oDSPOB_SDA, oDSPOB_SCL);
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
	-- PLL 28.63Mhz to 18.432MHz:
	PLL_MFILEinst : PLL_MFILE port map(not(sDSPOB_RST), iDSPOB_CLK28, sDSPOB_PLLout);
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
	-- DSP BLOCK:
	DSP_BLOCKinst : DSP_BLOCK port map(sDSPOB_RST, sDSPOB_MCLK, sDSPOB_ADCdata, sDSPOB_DACdata, 
												  sDSPOB_BCLK, sDSPOB_ADCLRC, sDSPOB_DACLRC);
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
	-- GPIO FOR DSP SIGNALS:
	GPIO_COMPinst : GPIO_COMP port map(sDSPOB_MCLK, sDSPOB_BCLK, sDSPOB_ADCLRC, sDSPOB_DACLRC, sDSPOB_ADCdata,
												  sDSPOB_DACdata,
												  
												  oGPIO_MCLK,  oGPIO_BCLK,  oGPIO_ADCLRC,  oGPIO_DACLRC,  oGPIO_ADCdata,
												  oGPIO_DACdata);
------------------------------------------------------------------------------------------------------
end DSPOBtopLevel;