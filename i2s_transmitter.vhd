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
		dacdat_out			: out std_logic
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
				end if;
				
			-- Wait daclrc_in to be high to be sure to start to transmit at the beginning of the frame
			when ST0 =>
				if daclrc_in = '1' then
					FSM <= ST1;
				end if;
		
			-- Wait daclrc_in to be low to start to transmit
			when ST1 =>
				if daclrc_in = '0' then
					FSM <= ST2;
				end if;
				
			-- Send left channel
			when ST2 =>
				dac_left_reg_i(AUDIO_LENGTH-1 downto 0) <= dac_left_reg_i(AUDIO_LENGTH-2 downto 0) & '0';
				dacdat_out <= dac_left_reg_i(AUDIO_LENGTH-1);
				cnt := cnt +1;
				if cnt = AUDIO_LENGTH+1 then -- AUDIO_LENGTH+1 because it's a variable: it's updated directly 
					cnt := 0;
					fsm <= ST3;
				end if;
				
			-- Wait daclrc_in to be low to start to transmit right channel
			when ST3 =>
				dacdat_out <= '0';
				if daclrc_in = '1' then
					fsm <= ST4;
				end if;
				
			-- Send right channel
			when ST4 =>
				dac_right_reg_i(AUDIO_LENGTH-1 downto 0) <= dac_right_reg_i(AUDIO_LENGTH-2 downto 0) & '0';
				dacdat_out <= dac_right_reg_i(AUDIO_LENGTH-1);
				cnt := cnt +1;
				if cnt = AUDIO_LENGTH+1 then
					cnt := 0;
					fsm <= IDLE;
				end if;
		end case;
	end if;
end process;

end rtl;