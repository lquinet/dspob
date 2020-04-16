library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity DSP_CLK is
	generic
	(
		-- TO GENERATE BCLK:
		midBclkCnt   : integer := 6;
		maxBclkCnt   : integer := 12;
		-- TO GENERATE LRC:
		midLrcCnt    : integer := 16;
		maxLrcCnt    : integer := 32
	);
	
	port
	(
		iDSPC_RST    : in std_logic;
		iDSPC_MCLK   : in std_logic;
		oDSPC_BCLK 	 : out std_logic;
		oDSPC_ADCLRC : out std_logic;
		oDSPC_DACLRC : out std_logic
	);
end entity;

---------------------------------------------------------------------------------
---------------------------------------------------------------------------------
---------------------------------------------------------------------------------

architecture rtl of DSP_CLK is
	-- SIGNALS DESCRIPTION:
	signal sBCLK	  : std_logic; -- internal bit clock
	signal sLRC      : std_logic; -- internal left-right clock
	
	signal sBCLK_CNT : integer range 0 to 255;
	signal sLRC_CNT  : integer range 0 to 255;
	
begin
	-- PROCESSES DESCRIPTION:
---------------------------------------------------------------------------------
	-- GENERATE BCLK: PROCESS TESTED V
	process(iDSPC_RST,iDSPC_MCLK)		
	begin
		if(iDSPC_RST = '0') then
			sBCLK_CNT <= 0;
			sBCLK		 <= '0';
		else
			if(rising_edge(iDSPC_MCLK)) then
				if(sBCLK_CNT < midBclkCnt) then
					sBCLK     <= '0';
					sBCLK_CNT <= sBCLK_CNT+1;
				elsif(sBCLK_CNT >= midBclkCnt and sBCLK_CNT < maxBclkCnt) then
					sBCLK     <= '1';
					sBCLK_CNT <= sBCLK_CNT+1;
					if(sBCLK_CNT = maxBclkCnt-1) then
						sBCLK_CNT <=  0;
					end if;
				end if;
			end if;
		end if;
	end process;
	oDSPC_BCLK <= sBCLK;
---------------------------------------------------------------------------------
---------------------------------------------------------------------------------
	-- GENERATE ADC & DAC CLOCK: PROCESS TESTED V
	process(iDSPC_RST,sBCLK)
	begin
		if(iDSPC_RST = '0') then
			sLRC_CNT <= 0;
			sLRC     <= '0';	
		else
			if(falling_edge(sBCLK)) then
				-- LEFT CHANNEL:
				if(sLRC_CNT < midLrcCnt) then
					sLRC     <= '1';
					sLRC_CNT <= sLRC_CNT+1;
				-- RIGHT CHANNEL:
				elsif(sLRC_CNT >= midLrcCnt and sLRC_CNT < maxLrcCnt) then
					sLRC 		<= '0';
					sLRC_CNT <= sLRC_CNT+1;
					if(sLRC_CNT = maxLrcCnt-1) then
						sLRC_CNT <= 0;
					end if;
				end if;
			end if;			
		end if;
	end process;
	oDSPC_ADCLRC <= sLRC;
	oDSPC_DACLRC <= sLRC;
--------------------------------------------------------------------------------- 
end rtl;