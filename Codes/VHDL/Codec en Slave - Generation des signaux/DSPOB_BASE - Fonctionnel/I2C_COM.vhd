library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity I2C_COM is
	port
	(
		-- Input ports
		iSDA : in std_logic;  -- E29 IO_A [6]
		iSCL : in std_logic;  -- E27 IO_A [4]

		-- Output ports
		oSDA : out std_logic; -- H18
		oSCL : out std_logic  -- J18
	);
end entity;

architecture rtl of I2C_COM is
begin
	oSDA <= iSDA;
	oSCL <= iSCL;

end rtl;

