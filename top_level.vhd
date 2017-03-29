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
		dacdat_out			: out std_logic
	);
end entity;

architecture rtl of top_level is

-- data registers
signal adc_left_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');
signal adc_right_reg_i 	: std_logic_vector(AUDIO_LENGTH-1 downto 0) := (others => '0');


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
		adc_left_reg_out	: out std_logic_vector(AUDIO_LENGTH-1 downto 0);
		adc_right_reg_out	: out std_logic_vector(AUDIO_LENGTH-1 downto 0)
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
		reset_in				=> reset_in,
		bclk_in				=> bclk_in,
		adclrc_in			=> adclrc_in,
		adcdat_in			=> adcdat_in,

		
		-- output ports
		adc_left_reg_out	=> adc_left_reg_i,
		adc_right_reg_out	=> adc_right_reg_i
	);

end rtl;