library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity i2s_receiver is

	generic(
		AUDIO_LENGTH			: natural
	);

	port(
		-- input ports
		clk_in 				: in  std_logic;
		reset_in				: in std_logic;
		bclk_in				: in std_logic;
		adclrc_in			: in std_logic;
		adcdat_in			: in std_logic;

		
		-- output ports
		adc_left_reg_out					: out std_logic_vector(AUDIO_LENGTH-1 downto 0);
		adc_right_reg_out					: out std_logic_vector(AUDIO_LENGTH-1 downto 0);
		adc_new_sample_received_out	: out std_logic := '0'
	);
end entity;

architecture rtl of i2s_receiver is

-- Finite Sate Machine
Type state_type is (IDLE, ST0, ST1, ST2, ST3);
signal fsm	: state_type := IDLE;

-- data registers
signal adc_left_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');
signal adc_right_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');

begin

process (bclk_in, reset_in)
variable cnt: natural:=0;
begin
	if reset_in = '1' then
		fsm <= IDLE;
		cnt :=0;
	elsif(rising_edge(bclk_in)) then
		case fsm is
			
			-- Wait adclrc_in to be high to be sure to start to transmit at the beginning of the frame
			when IDLE =>
				if adclrc_in = '1' then
					FSM <= ST0;
				end if;
				
			-- Wait adclrc_in to be low to start to transmit
			when ST0 =>
				adc_left_reg_out <= adc_left_reg_i; 	-- output the left channel received
				adc_right_reg_out <= adc_right_reg_i;	-- output the right channel received
				adc_new_sample_received_out <= '1';
				if adclrc_in = '0' then
					adc_new_sample_received_out <= '0';
					FSM <= ST1;
				end if;
			
			-- left channel is transmitting
			when ST1 => 
				adc_left_reg_i(AUDIO_LENGTH-1 downto 0) <= adc_left_reg_i(AUDIO_LENGTH-2 downto 0) & adcdat_in;
				cnt := cnt +1;
				if cnt = AUDIO_LENGTH then
					cnt := 0;
					fsm <= ST2;
				end if;
				
			-- Wait adclrc_in to be low to start to transmit right channel
			when ST2 =>
				if adclrc_in = '1' then
					fsm <= ST3;
				end if;
			
			-- right channel is transmitting
			when ST3 =>
				adc_right_reg_i(AUDIO_LENGTH-1 downto 0) <= adc_right_reg_i(AUDIO_LENGTH-2 downto 0) & adcdat_in;
				cnt := cnt +1;
				if cnt = AUDIO_LENGTH then
					cnt := 0;
					fsm <= IDLE;
				end if;
		end case;
	end if;
end process;

end rtl;