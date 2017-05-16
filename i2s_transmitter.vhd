library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity i2s_transmitter is

	generic(
		AUDIO_LENGTH			: natural
	);

	port(
		-- input ports
		clk_in 						: in std_logic;
		reset_in						: in std_logic;
		bclk_in						: in std_logic;
		daclrc_in					: in std_logic;
		dac_left_reg_in			: in std_logic_vector(AUDIO_LENGTH-1 downto 0);
		dac_right_reg_in			: in std_logic_vector(AUDIO_LENGTH-1 downto 0);
		new_data_2_transmit_in	: in std_logic;
		
		-- output ports
		test_out				: out std_logic := '0';
		led_out				: out std_logic_vector(17 downto 0) := (others => '0');
		dacdat_out			: out std_logic := '0'
	);
end entity;

architecture rtl of i2s_transmitter is

-- Finite Sate Machine
Type state_type is (IDLE, ST0, ST1, ST2, ST3, ST4);
signal fsm	: state_type := IDLE;

-- data registers
signal dac_left_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');
signal dac_right_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');

begin

process (bclk_in, reset_in)
variable cnt: natural:=0;
begin
	if reset_in = '1' then
		fsm <= IDLE;
		dac_left_reg_i <= (others => '0');
		dac_right_reg_i <= (others => '0');
		cnt :=0;
	elsif(falling_edge(bclk_in)) then
		case fsm is

			-- Wait new_data_2_transmit_in to transmit a new sample
			when IDLE =>
				dacdat_out <= '0';
				if new_data_2_transmit_in = '1' then
					-- load data to send through the left and right channel
					dac_left_reg_i	<= dac_left_reg_in;
					dac_right_reg_i <= dac_right_reg_in;
					FSM <= ST0;
					test_out <= '1';
				end if;
				
			-- Wait daclrc_in to be high to be sure to start to transmit at the beginning of the frame
			when ST0 =>
				if daclrc_in = '1' then
					FSM <= ST1;
					test_out <= '0';
				end if;
		
			-- Wait daclrc_in to be low to start to transmit
			when ST1 =>
				if daclrc_in = '0' then
					-- Start to transmit directly because we see the edge after 1 BCLK clock! beacause BCLK falling edge arrives before DACLRC edge
					dac_left_reg_i(AUDIO_LENGTH-1 downto 0) <= dac_left_reg_i(AUDIO_LENGTH-2 downto 0) & '0';
					dacdat_out <= dac_left_reg_i(AUDIO_LENGTH-1);
					cnt := cnt +1;
					
					-- change state
					FSM <= ST2;
					test_out <= '1';
				end if;
				
			-- left channel is transmitting
			when ST2 =>
				dac_left_reg_i(AUDIO_LENGTH-1 downto 0) <= dac_left_reg_i(AUDIO_LENGTH-2 downto 0) & '0';
				dacdat_out <= dac_left_reg_i(AUDIO_LENGTH-1);
				cnt := cnt +1;
				if cnt = AUDIO_LENGTH+1 then -- AUDIO_LENGTH+1 because it's a variable: it's updated directly 
					cnt := 0;
					fsm <= ST3;
					test_out <= '0';
				end if;
				
			-- Wait daclrc_in to be low to start to transmit right channel
			when ST3 =>
				dacdat_out <= '0';
				if daclrc_in = '1' then
					-- Start to transmit directly because we see the edge after 1 BCLK clock! beacause BCLK falling edge arrives before DACLRC edge
					dac_right_reg_i(AUDIO_LENGTH-1 downto 0) <= dac_right_reg_i(AUDIO_LENGTH-2 downto 0) & '0';
					dacdat_out <= dac_right_reg_i(AUDIO_LENGTH-1);
					cnt := cnt +1;
					
					-- change state
					fsm <= ST4;
					test_out <= '1';
				end if;
				
			-- right channel is transmitting
			when ST4 =>
				dac_right_reg_i(AUDIO_LENGTH-1 downto 0) <= dac_right_reg_i(AUDIO_LENGTH-2 downto 0) & '0';
				dacdat_out <= dac_right_reg_i(AUDIO_LENGTH-1);
				cnt := cnt +1;
				if cnt = AUDIO_LENGTH+1 then
					cnt := 0;
					fsm <= IDLE;
					test_out <= '0';
				end if;
		end case;
	end if;
end process;

-- Process that display data on the leds
process (new_data_2_transmit_in, reset_in)
begin
	if reset_in = '1' then
		led_out(17 downto 0) <= (others => '0');
	elsif(rising_edge(new_data_2_transmit_in)) then
		led_out(17 downto 0) <= dac_left_reg_in(AUDIO_LENGTH-1 downto AUDIO_LENGTH-17-1);
	end if;
end process;

---- Process that display data on the leds (retinal persistence = 1/20 s)
--process (daclrc_in)
--constant NUM_SAMPLES: natural:=2400; -- NUM_SAMPLES = 48000/20 = 2400
--variable cnt: std_logic := '1';
--begin
--	if(rising_edge(daclrc_in)) then
		
end rtl;