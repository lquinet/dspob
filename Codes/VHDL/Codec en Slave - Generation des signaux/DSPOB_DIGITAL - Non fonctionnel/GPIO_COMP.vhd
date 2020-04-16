library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity GPIO_COMP is
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
end entity;

------------------------------------------------------------
--========================================================--
------------------------------------------------------------

architecture rtl of GPIO_COMP is
	begin
		-- PROCESSES DESCRIPTION:
		oGPIO_MCLK   <= iGPIO_MCLK;
		oGPIO_BCLK   <= iGPIO_BCLK;
		oGPIO_ADCLRC <= iGPIO_ADCLRC;
		oGPIO_DACLRC <= iGPIO_DACLRC;
		oGPIO_ADCin  <= iGPIO_ADCin;
		oGPIO_DACout <= iGPIO_DACout;
end rtl;
