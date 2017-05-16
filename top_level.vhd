library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity top_level is

	generic(
		AUDIO_LENGTH			: natural:=24
	);

	port(
		-- input ports
		clk_in 				: in  std_logic;
		reset_in				: in std_logic;
		bclk_in				: in std_logic;
		adclrc_in			: in std_logic;
		adcdat_in			: in std_logic;
		daclrc_in			: in std_logic;
		
		-- output ports
		test_out				: out std_logic;
		new_data_2_transmit_out: out std_logic;
		reset_com_out 		: out std_logic;
		led_out				: out std_logic_vector(17 downto 0);
		dacdat_out			: out std_logic
	);
end entity;

architecture rtl of top_level is

-- data registers
signal adc_left_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');
signal adc_right_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');

signal new_data_2_transmit : std_logic;

signal reset_com_i : std_logic;

--************* Components declarations ********************--
component i2s_receiver is

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
		reset_com_out						: out std_logic;
		adc_new_sample_received_out	: out std_logic
	);
end component;

component i2s_transmitter is

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
		dacdat_out			: out std_logic
	);
end component;

begin

	--************* Components instantiation ********************--
	i2s_receiver_comp: i2s_receiver
	generic map(
		AUDIO_LENGTH
	)
	port map(
		-- input ports
		clk_in 				=> clk_in,
		reset_in				=> '0',
		bclk_in				=> bclk_in,
		adclrc_in			=> adclrc_in,
		adcdat_in			=> adcdat_in,

		
		-- output ports
		adc_left_reg_out	=> adc_left_reg_i,
		adc_right_reg_out	=> adc_right_reg_i,
		reset_com_out => reset_com_i,
		adc_new_sample_received_out => new_data_2_transmit
	);
	
	i2s_transmitter_comp: i2s_transmitter
	generic map(
		AUDIO_LENGTH
	)
	port map(
		-- input ports
		clk_in 				=> clk_in,
		reset_in				=> reset_com_i,
		bclk_in				=> bclk_in,
		daclrc_in			=> daclrc_in,
		dac_left_reg_in	=> adc_left_reg_i,
		dac_right_reg_in	=> adc_right_reg_i,
		new_data_2_transmit_in => new_data_2_transmit,
		
		-- output ports
		test_out => test_out,
		led_out => led_out,
		dacdat_out	=> dacdat_out
	);
	
	new_data_2_transmit_out <= new_data_2_transmit;
	reset_com_out <= reset_com_i;
	
	

end rtl;