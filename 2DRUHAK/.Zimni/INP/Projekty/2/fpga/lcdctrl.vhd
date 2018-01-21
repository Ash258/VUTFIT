-- lcdctrl.vhd : High-level LCD controller with BUSY
-- Copyright (C) 2011/2012 Brno University of Technology,
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

entity lcd_controller is
	generic (
		CMDLEN  : integer := 10*10000; -- doba trvani prikazu (1 ms @ 20MHz ~ 10000)
		LCD2x16 : boolean := False -- radic pro 2x16 nebo 1x16 LCD displej
	);
	port (
		RST      : in std_logic;
		CLK      : in std_logic;

		-- interni rozhrani
		DATA_IN  : in std_logic_vector (7 downto 0);
		WRITE_EN : in std_logic;
		BUSY     : out std_logic;

		--- rozhrani LCD displeje
		DISPLAY_RS   : out   std_logic;
		DISPLAY_DATA : inout std_logic_vector(7 downto 0);
		DISPLAY_RW   : out   std_logic;
		DISPLAY_EN   : out   std_logic := '1'
	);
end lcd_controller;

architecture behavioral of lcd_controller is
	type FSMState is (init, init0, init1, init2, init3, idle, w0, w1, w2, w3, wa0, wa1, wa2, wa3);

	function lcdaddrbits(islcd2x16: boolean) return integer is
	begin
		-- pragma translate off
		-- pro simulaci vzdy 1 radkovy displej
		return 4;
		-- pragma translate on
		if (islcd2x16) then return 5; end if;
		return 4;
	end function;

	function lcdhas2rows(islcd2x16: boolean) return boolean is
	begin
		-- pragma translate off
		-- pro simulaci vzdy 1 radkovy displej
		return false;
		-- pragma translate on
		return (islcd2x16);
	end function;

	signal pstate : FSMState := init; -- FSM present state
	signal nstate : FSMState; -- FSM next state
	signal addr_reg : std_logic_vector(lcdaddrbits(LCD2x16)-1 downto 0) := (others => '0');
	signal addr_inc : std_logic;
	signal data_reg : std_logic_vector(7 downto 0);
	signal init_data : std_logic_vector(8 downto 0);
	signal datareg_en : std_logic;
	signal data_sel : std_logic_vector(1 downto 0);
	signal t_cnt : integer range 0 to CMDLEN-1 := 0;
	signal t_lst : std_logic := '0';
	signal t_en : std_logic;

	constant INIT_ITEMS : integer := 5 + 8*2;
	signal init_cnt : integer range 0 to INIT_ITEMS-1;
	signal init_inc : std_logic;
	signal init_lst : std_logic;
	signal addr_data : std_logic_vector(7 downto 0);

begin
	DISPLAY_RS <= '1' when (data_sel="11") else -- write char
				 init_data(8);

	init_data <= "000111000" when (init_cnt=0) else  -- Set Function
				"000000001" when (init_cnt=1) else  -- Clear Display
				"000000010" when (init_cnt=2) else  -- Cursor Home
				"000001100" when (init_cnt=3) else  -- Display on/off Control
				"000000110" when (init_cnt=4) else  -- Entry Mode Set
				"001010000" when (init_cnt=5) else  -- Own character #0x02, #0x0A
				"100000001" when (init_cnt=6) else
				"001010001" when (init_cnt=7) else
				"100000001" when (init_cnt=8) else
				"001010010" when (init_cnt=9) else
				"100000001" when (init_cnt=10) else
				"001010011" when (init_cnt=11) else
				"100000101" when (init_cnt=12) else
				"001010100" when (init_cnt=13) else
				"100001001" when (init_cnt=14) else
				"001010101" when (init_cnt=15) else
				"100011111" when (init_cnt=16) else
				"001010110" when (init_cnt=17) else
				"100001000" when (init_cnt=18) else
				"001010111" when (init_cnt=19) else
				"100000100" when (init_cnt=20) else
				"000000000";

	DISPLAY_DATA <= init_data(7 downto 0) when (data_sel="01") else
					addr_data when (data_sel="10") else -- set addr
					data_reg when (data_sel="11") else -- write char
					(others => 'Z');

	addr_data <= "1" & addr_reg(4) & "00"  & addr_reg(3 downto 0) when lcdhas2rows(LCD2x16) else -- LCD 2x16 (FITkit 2.x)
				"1" & addr_reg(3) & "000" & addr_reg(2 downto 0); -- LCD 1x16 (FITkit 1.x)

	process (RST, CLK)
	begin
		if (RST = '1') then
			t_cnt <= 0;
		elsif (CLK'event) and (CLK = '1') then
			if (t_en = '1') then
				t_lst <= '0';
				if (t_cnt /= (CMDLEN-1)) then
					t_cnt <= t_cnt + 1;
				else
					t_cnt <= 0;
					t_lst <= '1';
				end if;
			end if;
		end if;
	end process;

	-- data register
	process(CLK, RST)
	begin
		if (RST = '1') then
			data_reg <= (others => '0');
			addr_reg <= (others => '0');
			init_cnt <= 0;
		elsif (CLK='1') and (CLK'event) then
			if (WRITE_EN='1') and (datareg_en='1') then
				data_reg <= DATA_IN;
			end if;
			if (addr_inc = '1') then
				addr_reg <= addr_reg + 1;
			end if;
			if (init_inc = '1') then
				init_cnt <= init_cnt + 1;
			end if;
		end if;
	end process;
	init_lst <= '1' when init_cnt = (INIT_ITEMS - 1) else '0';


	-- FSM present state
	process(CLK, RST)
	begin
		if (RST = '1') then
			pstate <= init;
		elsif (CLK='1') and (CLK'event) then
			pstate <= nstate;
		end if;
	end process;

	-- FSM next state logic, output logic
	process(pstate, WRITE_EN, t_lst, init_lst)
	begin
		nstate <= init;
		DISPLAY_RW <= '0';
		DISPLAY_EN <= '0';
		data_sel <= "00";
		datareg_en <= '0';
		BUSY <= '1';
		t_en <= '1';
		addr_inc <= '0';
		init_inc <= '0';

		case pstate is
			when init =>
				nstate <= init0;

			-- Display Init
			when init0 =>
				nstate <= init0;
				if (t_lst = '1') then nstate <= init1; end if;
				data_sel <= "01";

			when init1 =>
				nstate <= init1;
				if (t_lst = '1') then
					nstate <= init2;
				end if;
				data_sel <= "01";
				DISPLAY_EN <= '1';

			when init2 =>
				nstate <= init2;
				if (t_lst = '1') then
					nstate <= init3;
				end if;

				data_sel <= "01";

			when init3 =>
				nstate <= init3;
				if (t_lst = '1') then
					init_inc <= '1';
					if (init_lst = '1') then
						nstate <= idle;
					else
						nstate <= init0;
					end if;
				end if;
				data_sel <= "01";

			-- Idle
			when idle =>
				BUSY <= '0';
				t_en <= '0';
				datareg_en <= '1';
				nstate <= idle;
				if (WRITE_EN = '1') then
					nstate <= wa0;
				end if;

			-- Write address
			when wa0 =>
				nstate <= wa0;
				if (t_lst = '1') then
				   nstate <= wa1;
				end if;

			data_sel <= "10";

			when wa1 =>
				nstate <= wa1;
				if (t_lst = '1') then
				   nstate <= wa2;
				end if;

				data_sel <= "10";
				DISPLAY_EN <= '1';

			when wa2 =>
				nstate <= wa2;
				if (t_lst = '1') then
					nstate <= wa3;
				end if;

				data_sel <= "10";

			when wa3 =>
				nstate <= wa3;
				if (t_lst = '1') then
					nstate <= w0;
					addr_inc <= '1';
				end if;

				data_sel <= "10";

			-- Write character
			when w0 =>
				nstate <= w0;
				if (t_lst = '1') then
					nstate <= w1;
				end if;

				data_sel <= "11";

			when w1 =>
				nstate <= w1;
				if (t_lst = '1') then
					nstate <= w2;
				end if;
				data_sel <= "11";
				DISPLAY_EN <= '1';

			when w2 =>
				nstate <= w2;
				if (t_lst = '1') then
					nstate <= w3;
				end if;
				data_sel <= "11";

			when w3 =>
				nstate <= w3;
				if (t_lst = '1') then
					nstate <= idle;
				end if;
				data_sel <= "11";
		end case;
	end process;
end behavioral;
