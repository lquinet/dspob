-- MID LEVEL DSP BLOCK FILE:
-- There are in this file:
-- -) clock block to generate BCLK, ADCLRC, DACLRC
-- -) depending of the project, ADC receiver and DAC transmitter
 
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DSP_BLOCK is
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
end entity;

--=================================================================================================--
-----------------------------------------------------------------------------------------------------
--=================================================================================================--

architecture DSPmidLevel of DSP_BLOCK is
	-- SIGNALS DESCRIPTION:
	signal sDSP_RST    : std_logic;
	
	signal sDSP_BCLK   : std_logic;
	signal sDSP_ADCLRC : std_logic;
	signal sDSP_DACLRC : std_logic;
	
	-- COMPONENTS DESCRIPTION:
-----------------------------------------------------------------------------------------------------
	-- DSP GENERATE CLOCK:
	component DSP_CLK is
		port
		(
			iDSPC_RST    : in std_logic;
			iDSPC_MCLK   : in std_logic;
			oDSPC_BCLK 	 : out std_logic;
			oDSPC_ADCLRC : out std_logic;
			oDSPC_DACLRC : out std_logic
		);
	end component;
-----------------------------------------------------------------------------------------------------

--=================================================================================================--
-----------------------------------------------------------------------------------------------------
--=================================================================================================--	
	
begin
	-- PROCESSES DESCRIPTION:
	sDSP_RST    <= iDSP_RST;
	
	oDSP_BCLK   <= sDSP_BCLK;
	oDSP_ADCLRC <= sDSP_ADCLRC;
	oDSP_DACLRC <= sDSP_DACLRC;
	
	oDSP_DACdata <= iDSP_ADCdata; -- YOLO STRAT DU SAMURAI !!!
	
	-- COMPONENTS DESCRIPTION:
----------------------------------------------------------------------------------------------------
	-- DSP GENERATE CLOCK:
	DSP_CLKinst : DSP_CLK port map(sDSP_RST, iDSP_MCLK, sDSP_BCLK, sDSP_ADCLRC, sDSP_DACLRC);
-----------------------------------------------------------------------------------------------------
	
end architecture;