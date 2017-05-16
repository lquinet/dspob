-- echo_effect component
-- echo effect: 

library ieee;
use ieee.std_logic_1164.all;
use IEEE.numeric_std.all;

entity echo_effect is

	generic(
		Audio_length			: integer;
		NUM_SAMPLES				: integer	-- Number of samples that compose the delay
	);

	port 
	(
		-- input ports
		clk_in 			: in  std_logic;
		reset_echo_in		: in  std_logic;
		--iADCLRC_rise	: in std_logic;
		--iADCLRC_fall	: in std_logic;
		adc_left_reg_in	: in std_logic_vector(Audio_length-1 downto 0);
		adc_right_reg_in	: in std_logic_vector(Audio_length-1 downto 0);
		adc_new_sample_received_in : in  std_logic;
		
		-- output ports
		left_channel_out	: out std_logic_vector(Audio_length-1 downto 0);
		right_channel_out	: out std_logic_vector(Audio_length-1 downto 0);
		test_out				: out std_logic := '0'-- test signal
	);

end entity;

architecture rtl of echo_effect is

	signal left_Channel	: unsigned(Audio_length-1 downto 0);
	signal right_Channel	: unsigned(Audio_length-1 downto 0);
	
	--signal add_cnt: natural:=0;
	
	-- Finite Sate Machine
	type state_type is (IDLE, ST0, ST1, ST2);
	signal FSM	: state_type := IDLE;
	
	-- RAM signals
	signal data			: STD_LOGIC_VECTOR (63 DOWNTO 0);
	signal rdaddress	: STD_LOGIC_VECTOR (12 DOWNTO 0);
	signal wraddress	: STD_LOGIC_VECTOR (12 DOWNTO 0);
	signal wren			: STD_LOGIC  := '0';
	signal q				: STD_LOGIC_VECTOR (63 DOWNTO 0);
	
	COMPONENT dual_port_ram IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (63 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (12 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (12 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (63 DOWNTO 0)
	);
	END COMPONENT;
	
begin

	-- Components instantiation --
	dual_port_ram_comp: dual_port_ram port map(
		clk_in,
		data	,
		rdaddress,
		wraddress,
		wren,
		q	
	);
	
	
	-- delay the data by 8192 samples --
	process(clk_in, reset_echo_in)
	variable add_cnt: unsigned(12 downto 0) := (others => '0');
	begin
		if (reset_echo_in = '1') then
			add_cnt := (others => '0');
			left_channel_out <= adc_left_reg_in;
			right_channel_out <= adc_right_reg_in;
		elsif rising_edge(clk_in) then
			case FSM is
				when IDLE =>
					if adc_new_sample_received_in = '1' Then
						wren <= '1';
						wraddress <= std_logic_vector(add_cnt);
						rdaddress <= std_logic_vector(add_cnt+1);
						data <= "0000000000000000" & adc_right_reg_in & adc_left_reg_in;
						
						test_out <= '1';
						
						-- Set the next state
						FSM <= ST0;
					end if;
				when ST0 =>
						
						-- increment address counter
						if (add_cnt < NUM_SAMPLES) then
							add_cnt := add_cnt +1;
						else
							add_cnt := (others => '0');
						end if;
						
						-- Set the next state
						FSM <= ST1;
				when ST1 =>
						-- Stop the writing
						wren <= '0';
						
						-- Read the data
						left_channel_out <= std_logic_vector(unsigned(q(Audio_length-1 downto 0)));
						right_channel_out <= std_logic_vector(unsigned(q(Audio_length*2-1 downto Audio_length)));
						
						test_out <= '0';
						
						-- Set the next state
						FSM <= ST2;
						
				when ST2 =>
						if adc_new_sample_received_in = '0' Then
							-- Set the next state
							FSM <= IDLE;
						end if;
			end case;
		end if;
	end process;
	

--			if iADCLRC_fall = '1' then
--				we_a <= '1';
--				we_b <= '1';
--				data_a <= iAdc_lpo_reg;
--				data_b <= iAdc_rpo_reg;
--				addr_a <= add_cnt;
--				addr_b <= add_cnt+1;
--				oLeft_Channel <= std_logic_vector(unsigned(q_a)/4);
--				oRight_Channel <= std_logic_vector(unsigned(q_b)/4);
--				-- increment address counter
--				if (add_cnt < 2**ADDR_WIDTH - 1) then
--					add_cnt <= add_cnt +2;
--				else
--					add_cnt <= 0;
--				end if;
--			end if;
	
	
--	-- delay the data by 50000 samples --
--	process(iCLK_50, iReset_echo)
--	begin
--		if (iReset_echo = '0') then
--			oLeft_Channel <= (others=>'0');
--			oRight_Channel <= (others=>'0');
--		elsif rising_edge(iCLK_50) then
--			if iADCLRC_fall = '1' then
--				-- Load the data in the first sample
--				delay_RAM(0) <= (unsigned(iAdc_lpo_reg), unsigned(iAdc_rpo_reg));
--				-- shift the samples
--				delay_RAM((NUM_SAMPLES-1) downto 1) <= delay_RAM((NUM_SAMPLES-2) downto 0);
--				-- put the last sample out
--				delay_out <= delay_RAM(NUM_SAMPLES-1);
--			end if;
--		end if;
--	end process;
--	
--	oLeft_Channel <= std_logic_vector(unsigned(iAdc_lpo_reg) + delay_out.leftChannel/4);
--	oRight_Channel <= std_logic_vector(unsigned(iAdc_rpo_reg) + delay_out.rightChannel/4);
	
end rtl;