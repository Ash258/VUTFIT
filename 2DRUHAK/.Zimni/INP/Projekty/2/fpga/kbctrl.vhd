-- kbctrl.vhd : High-level keyboard controller
-- Copyright (C) 2011 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Zdenek Vasicek <xvasic11 AT stud.fit.vutbr.cz>
--
-- LICENSE TERMS
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions
-- are met:
-- 1. Redistributions of source code must retain the above copyright
--    notice, this list of conditions and the following disclaimer.
-- 2. Redistributions in binary form must reproduce the above copyright
--    notice, this list of conditions and the following disclaimer in
--    the documentation and/or other materials provided with the
--    distribution.
-- 3. All advertising materials mentioning features or use of this software
--    or firmware must display the following acknowledgement:
--
--      This product includes software developed by the University of
--      Technology, Faculty of Information Technology, Brno and its
--      contributors.
--
-- 4. Neither the name of the Company nor the names of its contributors
--    may be used to endorse or promote products derived from this
--    software without specific prior written permission.
--
-- This software or firmware is provided ``as is'', and any express or implied
-- warranties, including, but not limited to, the implied warranties of
-- merchantability and fitness for a particular purpose are disclaimed.
-- In no event shall the company or contributors be liable for any
-- direct, indirect, incidental, special, exemplary, or consequential
-- damages (including, but not limited to, procurement of substitute
-- goods or services; loss of use, data, or profits; or business
-- interruption) however caused and on any theory of liability, whether
-- in contract, strict liability, or tort (including negligence or
-- otherwise) arising in any way out of the use of this software, even
-- if advised of the possibility of such damage.
--
-- $Id$
--
--

library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity kb_controller is
	port (
		RST      : in std_logic;
		CLK      : in std_logic;

		-- interni rozhrani
		DATA     : out std_logic_vector (7 downto 0);
		DATA_REQ : in std_logic;
		DATA_VLD : out std_logic;
		REQ_ACK  : out std_logic;

		--- rozhrani LCD displeje
		KB_IN   : out std_logic_vector(3 downto 0);
		KB_OUT  : in std_logic_vector(3 downto 0)
		);
end kb_controller;


architecture behavioral of kb_controller is

	-- Keyboard 4x4
	component keyboard_controller
		port(
		CLK      : in std_logic;
		RST      : in std_logic;

		DATA_OUT : out std_logic_vector(15 downto 0);
		DATA_VLD : out std_logic;

		KB_KIN   : out std_logic_vector(3 downto 0);
		KB_KOUT  : in  std_logic_vector(3 downto 0)
		);
	end component;

	type t_k2a is array(0 to 15) of std_logic_vector(7 downto 0);
	signal key2ascii : t_k2a := (X"31",X"34",X"37",X"0A",X"32",X"35",X"38",X"30",X"33",X"36",X"39",X"0A",X"41",X"42",X"43",X"44");
																		-- 1,4,7,CR,2,5,8,0,3,6,9,CR,A,B,C,D
	signal key_data : std_logic_vector(15 downto 0);
	signal key_reg : std_logic_vector(15 downto 0) := (others => '0');
	signal key_vld : std_logic;
	signal key_chg : std_logic := '0';
	signal key_dwn : std_logic;

	signal in_data : std_logic_vector(7 downto 0) := (others => '0');
	signal in_vld : std_logic := '0';
	signal in_st : integer range 0 to 8 := 0;

begin
	DATA <= in_data;
	DATA_VLD <= in_vld;

	-- Radic klavesnice, vstupy
	keybrd: entity work.keyboard_controller
	port map(
		CLK			=> CLK,
		RST			=> RST,

		DATA_OUT	=> key_data,
		DATA_VLD	=> key_vld,

		-- Keyboart
		KB_KIN		=> KB_IN,
		KB_KOUT		=> KB_OUT
	);

	process (CLK)
	begin
		if (CLK'event) and (CLK = '1') then
			key_chg <= '0';
			if (key_vld = '1') then
				if (key_data /= key_reg) then
					key_chg <= '1';
					key_reg <= key_data;
				end if;
			end if;
		end if;
	end process;

	key_dwn <= '0' when (key_reg = "0000000000000000") else '1';

	process (CLK)
	begin
		if (CLK'event) and (CLK = '1') then
			in_vld <= '0';
			in_st <= 0;
			REQ_ACK <= '0';

			case in_st is
				when 0 =>
					in_st <= 0;
					if (DATA_REQ = '1') then in_st <= 1; end if;

				when 1 =>
					in_st <= 1;
					REQ_ACK <= '1'; -- pokud procesor ocekava vstup z klavesnice, rozsvitime D4
					if (key_chg = '1') and (key_dwn = '1') then
						in_data <= X"00";
						in_st <= 0;
						for i in 0 to 15 loop
							if (conv_integer(key_reg) = 2**i) then
								in_data <= key2ascii(i);
								in_st <= 2;
							end if;
						end loop;
					end if;

				when 2 =>
					in_st <= 2;
					if (key_chg = '1') and (key_dwn = '0') then
						in_st <= 3;
					end if;

				when 3 =>
					in_vld <= '1';
					in_st <= 3;
					if (DATA_REQ = '0') then in_st <= 0; end if;

				when others => null;
			end case;
		end if;
	end process;
end behavioral;
