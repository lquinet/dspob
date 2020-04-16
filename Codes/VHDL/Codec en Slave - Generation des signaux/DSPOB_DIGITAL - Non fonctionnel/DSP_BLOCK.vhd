-- MID LEVEL DSP BLOCK FILE:
-- There are in this file:
-- -) clock block to generate BCLK, ADCLRC, DACLRC
-- -) depending of the project, ADC receiver and DAC transmitter
 
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DSP_BLOCK is
	generic
	(
		bitSamp : integer := 15
	);
	
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
	signal sDSP_RST    	 : std_logic;
	
	signal sDSP_BCLK   	 : std_logic;
	signal sDSP_ADCLRC 	 : std_logic;
	signal sDSP_DACLRC 	 : std_logic;
	
	signal sDSP_LEFTdata  : std_logic_vector(bitSamp downto 0);
	signal sDSP_RIGHTdata : std_logic_vector(bitSamp downto 0);
	
	
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
-----------------------------------------------------------------------------------------------------
   -- ADC RECEIVER:
	component ADC_TEST is
		port
		(
			iADCT_RST          : in std_logic;
			
			iADCT_ADCLRC       : in std_logic;
			iADCT_BCLK	       : in std_logic;
			
			iADCT_ADCin        : in std_logic;
			oADCT_ADC_LEFTout  : out std_logic_vector(bitSamp downto 0);
			oADCT_ADC_RIGHTout : out std_logic_vector(bitSamp downto 0)
		);
	end component;
-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------
	-- DAC TRANSMITTER:
	component DAC_TEST is
		port
		(
			iDACT_RST 	 		: in std_logic;
			
			iDACT_DACLRC 		: in std_logic;
			iDACT_BCLK   		: in std_logic;
			
			iDACT_DAC_LEFTin  : in std_logic_vector(bitSamp downto 0);
			iDACT_DAC_RIGHTin : in std_logic_vector(bitSamp downto 0);
			oDACT_DACout		: out std_logic		
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
		
	-- COMPONENTS DESCRIPTION:
----------------------------------------------------------------------------------------------------
	-- DSP GENERATE CLOCK:
	DSP_CLKinst : DSP_CLK port map(sDSP_RST, iDSP_MCLK, sDSP_BCLK, sDSP_ADCLRC, sDSP_DACLRC);
-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------
   -- ADC RECEIVER:
	ADC_TESTinst : ADC_TEST port map(sDSP_RST, sDSP_ADCLRC, sDSP_BCLK, iDSP_ADCdata, 
											   sDSP_LEFTdata, sDSP_RIGHTdata);
-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------
	-- DAC TRANSMITTER:
	DAC_TESTinst : DAC_TEST port map(sDSP_RST, sDSP_DACLRC, sDSP_BCLK,
												sDSP_LEFTdata, sDSP_RIGHTdata, oDSP_DACdata);
-----------------------------------------------------------------------------------------------------
	
end architecture;