-- rom.vhd : ROM memory
-- Copyright (C) 2016 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Zdenek Vasicek <vasicek AT fit.vutbr.cz>
--
library ieee;
use ieee.std_logic_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.std_logic_arith.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity rom is
	generic (
		INIT  : string := ""
	);
	port (
		CLK   : in std_logic; -- clock

		EN    : in  std_logic;
		ADDR  : in std_logic_vector(11 downto 0); -- address
		DATA  : out std_logic_vector(7 downto 0) -- data
	);
end rom;

-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of rom is
	type t_ram is array (0 to 2**12-1) of std_logic_vector(7 downto 0);

	function str2vec(arg: string; size: integer) return t_ram is
		variable result: t_ram := (others => (others => '0'));
	begin
		for i in arg'range loop
			result(i-1) := conv_std_logic_vector(character'pos(arg(i)), 8);
		end loop;
		return result;
	end;

	constant mem: t_ram := str2vec(INIT, 2*2048);
	signal dout : std_logic_vector(7 downto 0) := (others => '0');

begin
	process (CLK)
	begin
		if (CLK'event) and (CLK = '1') then
			if (EN = '1') then
				dout <= mem(conv_integer(ADDR));
			end if;
		end if;
	end process;

	DATA <= dout;
end behavioral;
