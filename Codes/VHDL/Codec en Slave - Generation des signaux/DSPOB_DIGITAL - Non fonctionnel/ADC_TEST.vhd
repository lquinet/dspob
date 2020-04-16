library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ADC_TEST is 
	generic
	(
		bitSamp : integer := 15
	);
	
	port
	(
		iADCT_RST          : in std_logic;
		
		iADCT_ADCLRC       : in std_logic;
		iADCT_BCLK	       : in std_logic;
		
		iADCT_ADCin        : in std_logic;
		oADCT_ADC_LEFTout  : out std_logic_vector(bitSamp downto 0);
		oADCT_ADC_RIGHTout : out std_logic_vector(bitSamp downto 0)
	);
end entity;

-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------

architecture rtl of ADC_TEST is
	-- SIGNALS DESCRIPTION:
	signal sADC_LEFT, sADC_RIGHT : std_logic_vector(bitSamp downto 0);
	signal sADCLRC					  : std_logic;
	signal sBCLK					  : std_logic;
	
-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------
	
begin	
	-- PROCESSES DESCRIPTION:
	sADCLRC 				 <= iADCT_ADCLRC;
	sBCLK   				 <= iADCT_BCLK;
	oADCT_ADC_LEFTout  <= sADC_LEFT;
	oADCT_ADC_RIGHTout <= sADC_RIGHT;
-----------------------------------------------------------------
	-- ADC SHIFT REGISTER:
	process(iADCT_RST,sADCLRC,sBCLK)
	begin
		if(iADCT_RST = '0') then
			sADC_LEFT  <= x"0000";
			sADC_RIGHT <= x"0000";
		else
			if(rising_edge(sBCLK)) then
				-- LEFT CHANNEL:
				if(sADCLRC = '1') then
					sADC_LEFT(0) 					 <= iADCT_ADCin;
					sADC_LEFT(bitSamp downto 1) <= sADC_LEFT(bitSamp-1 downto 0);					
				-- RIGHT CHANNEL:
				elsif(sADCLRC = '0') then
					sADC_RIGHT(0) 					  <= iADCT_ADCin;
					sADC_RIGHT(bitSamp downto 1) <= sADC_RIGHT(bitSamp-1 downto 0);					
				end if;
			end if;
		end if;
	end process;
	
		
-----------------------------------------------------------------
end rtl;