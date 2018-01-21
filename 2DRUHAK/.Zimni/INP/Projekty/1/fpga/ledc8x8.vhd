-- Copyright (C) 2017 Brno University of Technology,
--                    Faculty of Information Technology
-- @Author: Jakub Čábera <xcaber00@stud.fit.vutbr.cz>

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity ledc8x8 is
	port ( -- Sem doplňte popis rozhraní obvodu.
		RESET, SMCLK	: in std_logic;								-- viz. Obr. 2
		-- ROW, LED		: out std_logic_vector (7 downto 0)			-- viz. Obr. 2 Pokud to je takto, tak je otočený displej o 180°
		ROW, LED		: out std_logic_vector (0 to 7)			-- viz. Obr. 2
	);
end ledc8x8;

architecture main of ledc8x8 is
	-- Sem doplňte definice vnitřních signálů.
	signal ce_cnt, leds, rows	: std_logic_vector(7 downto 0);
	signal ce					: std_logic;

begin
	-- Sem doplňte popis obvodu. Doporučení: Používejte základní obvodové prvky
	-- (multiplexory, registry, decodery,...), jejich funkce popisujte pomocí
	-- procesu VHDL a propojení těchto prvků, tj. komunikaci mezi procesy,
	-- realizujte pomocí vnitřních signálů deklarovaných výše.
	-- DODRŽUJTE ZÁSADY PSANÍ SYNTETIZOVATELNÉHO VHDL KÓDU OBVODOVÝCH PRVKŮ,
	-- JEŽ JSOU PROBÍRÁNY ZEJMÉNA NA ÚVODNÍCH CVIČENÍ INP A SHRNUTY NA WEBU:
	-- http://merlin.fit.vutbr.cz/FITkit/docs/navody/synth_templates.html.
	-- Nezapoměňte také doplnit mapování signálů rohtraní na piny FPGA
	-- v souboru ledc8x8.ucf.

	-- Čítač pro snížení frekvence SMCLK 1->256
	generator: process(SMCLK, RESET)
	begin
		if RESET = '1' then											-- Asynchronní reset
			ce_cnt <= "00000000";
		-- elsif (SMCLK'event) and (SMCLK = '1') then
		elsif rising_edge(SMCLK) then								-- Nástupná hrana
			ce_cnt <= ce_cnt + 1;
		end if;
	end process generator;

	-- Možná může být v generátor procesu (TODO: Inspect)
	ce <= '1' when ce_cnt = "11111111" else '0';						-- ce <= '1' when ce_cnt = X"FF" else '0';

	-- Rotační čítač
	rot_cnt: process(RESET, ce, SMCLK)
	begin
		if RESET = '1' then											-- Asynchronní reset
			rows <= "10000000";
		elsif rising_edge(SMCLK) and (ce = '1') then				-- Nástupná hrana
			rows <= rows(0) & rows(7 downto 1);						-- Konkatenace na posunutí jednotky
		end if;
	end process rot_cnt;

	-- Dekodér
	decoder: process(rows)
	begin
		case rows is
			when "10000000" => leds <= "11101001";					-- | "00010110";	|   * ** |   0 00 |
			when "01000000" => leds <= "11100110";					-- | "00011001";	|   **  *|   00  0|
			when "00100000" => leds <= "11100110";					-- | "00011001";	|   **  *|   00  0|
			when "00010000" => leds <= "11100111";					-- | "00011000";	|   **   |   00   |
			when "00001000" => leds <= "11100111";					-- | "00011000";	|   **   |   00   |
			when "00000100" => leds <= "01100110";					-- | "10011001";	|*  **  *|0  00  0|
			when "00000010" => leds <= "01100110";					-- | "10011001";	|*  **  *|0  00  0|
			when "00000001" => leds <= "10001001";					-- | "01110110";	| **  ** | 00  00 |
			when others		=> leds <= "11111111";
		end case;
	end process decoder;

	-- Rozsvícení řádků
	ROW <= rows;
	LED <= leds;
end main;
