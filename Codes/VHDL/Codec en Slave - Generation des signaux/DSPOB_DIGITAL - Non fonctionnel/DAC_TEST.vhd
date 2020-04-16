library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DAC_TEST is
	generic
	(
		bitSamp : integer := 15
	);
	
	port
	(
		iDACT_RST 	 		: in std_logic;
		
		iDACT_DACLRC 		: in std_logic;
		iDACT_BCLK   		: in std_logic;
		
		iDACT_DAC_LEFTin  : in std_logic_vector(bitSamp downto 0);
		iDACT_DAC_RIGHTin : in std_logic_vector(bitSamp downto 0);
		oDACT_DACout		: out std_logic		
	);
end entity;

-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------

architecture rtl of DAC_TEST is
	-- SIGNALS DESCRIPTION:
	signal sDACdata				  : std_logic;
	signal sDACLRC 				  : std_logic;
	signal sBCLK					  : std_logic;
	
-----------------------------------------------------------------
-----------------------------------------------------------------
-----------------------------------------------------------------	
	
begin
	-- PROCESSES DESCRIPTION:
	sDACLRC	    <= iDACT_DACLRC;
	sBCLK		    <= iDACT_BCLK;
	oDACT_DACout <= sDACdata;
-----------------------------------------------------------------
	-- DAC SHIFT REGISTER:
	process(iDACT_RST,sDACLRC,sBCLK)
	begin
		if(iDACT_RST = '0') then
			sDACdata <= '0';
		else
			if(falling_edge(sBCLK)) then
				-- LEFT CHANNEL:
				if(sDACLRC = '1') then
					sDACdata <= iDACT_DAC_LEFTin(bitSamp);
				-- RIGHT CHANNEL:
				elsif(sDACLRC = '0') then
					sDACdata <= iDACT_DAC_RIGHTin(bitSamp);
				end if;
			end if;
		end if;
	end process;
-----------------------------------------------------------------
end rtl;