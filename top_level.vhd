library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity top_level is

	generic(
		AUDIO_LENGTH			: natural :=24;
		NUM_SAMPLES				: natural :=8192	-- Number of samples that compose the delay
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
		test_out				: out std_logic_vector(1 downto 0);
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

signal echo_left_ch_i	: std_logic_vector(Audio_length-1 downto 0);
signal echo_right_ch_i	: std_logic_vector(Audio_length-1 downto 0);

signal new_data_2_transmit : std_logic;

signal reset_com_i : std_logic;

--************* Components declarations ********************--
-- i2s_receiver
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

-- i2s_transmitter
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

-- echo_effect
component echo_effect is

	generic(
		Audio_length			: integer;
		NUM_SAMPLES				: integer	-- Number of samples that compose the delay
	);

	port 
	(
		-- input ports
		clk_in 			: in  std_logic;
		reset_echo_in		: in  std_logic;
		adc_left_reg_in	: in std_logic_vector(Audio_length-1 downto 0);
		adc_right_reg_in	: in std_logic_vector(Audio_length-1 downto 0);
		adc_new_sample_received_in : in  std_logic;
		
		-- output ports
		left_channel_out	: out std_logic_vector(Audio_length-1 downto 0);
		right_channel_out	: out std_logic_vector(Audio_length-1 downto 0);
		test_out				: out std_logic := '0'-- test signal
	);

end component;


begin

	--************* Components instantiation ********************--
	-- i2s_receiver
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
	
	-- i2s_transmitter
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
		dac_left_reg_in	=> echo_left_ch_i,
		dac_right_reg_in	=> echo_right_ch_i,
		new_data_2_transmit_in => new_data_2_transmit,
		
		-- output ports
		test_out => test_out(0),
		led_out => led_out,
		dacdat_out	=> dacdat_out
	);
	
	echo_effect_com : echo_effect
	generic map(
		AUDIO_LENGTH	=> AUDIO_LENGTH,
		NUM_SAMPLES		=> NUM_SAMPLES	-- Number of samples that compose the delay
	)

	port map
	(
		-- input ports
		clk_in 				=> clk_in,
		reset_echo_in 		=> reset_com_i,
		adc_left_reg_in 	=> adc_left_reg_i,
		adc_right_reg_in	=> adc_right_reg_i,
		adc_new_sample_received_in => new_data_2_transmit,
		
		-- output ports
		left_channel_out	=> echo_left_ch_i,
		right_channel_out	=> echo_right_ch_i,
		test_out				=> test_out(1)
	);
	
	
	new_data_2_transmit_out <= new_data_2_transmit;
	reset_com_out <= reset_com_i;
	
	

end rtl;