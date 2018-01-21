-- cpu.vhd: Simple 8-bit CPU (BrainLove interpreter)
-- Copyright (C) 2017 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Jakub Čábera <xcaber00@stud.fit.vutbr.cz>
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity cpu is
	port (
		CLK			: in std_logic;							-- Hodinový signál
		RESET		: in std_logic;							-- Asynchronní reset procesoru
		EN			: in std_logic;							-- Povolení činnosti procesoru

		-- Synchronní paměť ROM
		CODE_ADDR	: out std_logic_vector(11 downto 0);	-- Adresa do paměti
		CODE_DATA	: in  std_logic_vector(7 downto 0);		-- CODE_DATA <- rom[CODE_ADDR] pokud CODE_EN='1'
		CODE_EN		: out std_logic;						-- Povolení činosti

		-- Synchronní paměť RAM
		DATA_ADDR	: out std_logic_vector(9 downto 0);		-- Adresa do paměti
		DATA_WDATA	: out std_logic_vector(7 downto 0);		-- mem[DATA_ADDR] <- DATA_WDATA pokud DATA_EN='1'
		DATA_RDATA	: in  std_logic_vector(7 downto 0);		-- DATA_RDATA <- ram[DATA_ADDR] pokud DATA_EN='1'
		DATA_RDWR	: out std_logic;						-- Čtení z paměti (DATA_RDWR='0') / zápis do paměti (DATA_RDWR='1')
		DATA_EN		: out std_logic;						-- Povolení činnosti

		-- Vstupní port
		IN_DATA		: in  std_logic_vector(7 downto 0);		-- IN_DATA obsahuje stisknutý znak klávesnice pokud IN_VLD='1' a IN_REQ='1'
		IN_VLD		: in  std_logic;						-- Data platná pokud IN_VLD='1'
		IN_REQ		: out std_logic;						-- Požadavek na vstup dat z klávesnice

		-- Výstupní port
		OUT_DATA	: out std_logic_vector(7 downto 0);		-- Zapisovaná data
		OUT_BUSY	: in  std_logic;						-- Pokud OUT_BUSY='1', LCD je zaneprázdněn, nelze zapisovat,  OUT_WE musí být '0'
		OUT_WE		: out std_logic							-- LCD <- OUT_DATA pokud OUT_WE='1' a OUT_BUSY='0'
	);
end cpu;

-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of cpu is
	-- Zde dopište potřebné deklarace signálů

	-- Instrukce pro dekodér
	type instruction_type is (
		ins_pointer_inc,	-- | >		| 0x3E | Inkrementace hodnoty ukazatele														| ptr+=1;			|
		ins_pointer_dec,	-- | <		| 0x3C | Dekrementace hodnoty ukazatele														| ptr-=1;			|
		ins_value_inc,		-- | +		| 0x2B | Inkrementace hodnoty aktuální buňky												| *ptr+=1;			|
		ins_value_dec,		-- | -		| 0x2D | Dekrementace hodnoty aktuální buňky												| *ptr-=1;			|
		ins_while_start,	-- | [		| 0x5B | Je-li hodnota aktuální buňku nulová, skoč za další `]` jinak následující znak		| while (*ptr) {	|
		ins_while_break,	-- | ~		| 0x7E | Ukončí právě prováděnou smyčku while												| 	break;			|
		ins_while_end,		-- | ]		| 0x5D | Je-li hodnota aktuální buňku nenulová, skoč za další `[` jinak následující znak	| }					|
		ins_putchar,		-- | .		| 0x2E | Vytiskne hodnotu aktuální buňky													| putchar(*ptr);	|
		ins_getchar,		-- | ,		| 0x2C | Načti hodnotu a ulož ji do aktuální buňky											| *ptr = getchar();	|
		ins_halt,			-- | null	| 0x00 | Zastav vykonávání programu															| return;			|
		ins_nope			-- Jakýkoliv jiný znak
	);
	signal instruction : instruction_type;

	-- Stavy automatu
	type fsm_state is (
		state_idle, state_fetch,
		state_decode,
		state_p_inc,
		state_p_dec,
		state_v_inc, state_v_inc_do,
		state_v_dec, state_v_dec_do,
		state_get,
		state_put,
		state_while_start1, state_while_start2, state_while_start3, state_while_start4,
		state_while_break1, state_while_break2, state_while_break3,
		state_while_end1, state_while_end2, state_while_end3, state_while_end4, state_while_end5,
		state_halt,
		state_nope
	);
	signal present_state, next_state : fsm_state;

	signal pc_data			: std_logic_vector(11 downto 0);
	signal pc_inc, pc_dec	: std_logic;

	signal ptr_data			: std_logic_vector(9 downto 0);
	signal ptr_inc, ptr_dec	: std_logic;

	signal cnt_data			: std_logic_vector(7 downto 0);
	signal cnt_inc, cnt_dec	: std_logic;

	-- signal selection		: std_logic;
	signal selection2		: std_logic_vector(1 downto 0);

-- ----------------------------------------------------------------------------
--                      Components
-- ----------------------------------------------------------------------------
begin
	-- Zde dopište vlastní VHDL kód

	-- -----------------------------------------
	--          Registr PC / Programovový čítač
	-- -----------------------------------------
	PC_proc: process (RESET, CLK)
	begin
		if (RESET = '1') then
			pc_data <= (others => '0');
		elsif rising_edge(CLK) then
			if (pc_inc = '1') then		pc_data <= pc_data + 1;
			elsif (pc_dec = '1') then	pc_data <= pc_data - 1;
			end if;
		end if;
	end process PC_proc;

	-- -----------------------------------------
	--          Registr PTR
	-- -----------------------------------------
	PTR_proc: process (RESET, CLK)
	begin
		if (RESET = '1') then
			ptr_data <= (others => '0');
		elsif rising_edge(CLK) then
			if (ptr_inc = '1') then		ptr_data <= ptr_data + 1;
			elsif (ptr_dec = '1') then	ptr_data <= ptr_data - 1;
			end if;
		end if;
	end process PTR_proc;

	-- -----------------------------------------
	--          Registr CNT
	-- -----------------------------------------
	CNT_proc: process (RESET, CLK)
	begin
		if (RESET = '1') then
			cnt_data <= (others => '0');
		elsif rising_edge(CLK) then
			if (cnt_inc = '1') then		cnt_data <= cnt_data + 1;
			elsif (cnt_dec = '1') then	cnt_data <= cnt_data - 1;
			end if;
		end if;
	end process CNT_proc;

	-- -----------------------------------------
	--          Dekodér instrukcí
	-- -----------------------------------------
	decoder_proc: process (CODE_DATA)
	begin
		case (CODE_DATA) is
			when X"3E"	=> instruction <= ins_pointer_inc;	-- >
			when X"3C"	=> instruction <= ins_pointer_dec;	-- <
			when X"2B"	=> instruction <= ins_value_inc;	-- +
			when X"2D"	=> instruction <= ins_value_dec;	-- -
			when X"5B"	=> instruction <= ins_while_start;	-- [
			when X"7E"	=> instruction <= ins_while_break;	-- ~
			when X"5D"	=> instruction <= ins_while_end;	-- ]
			when X"2E"	=> instruction <= ins_putchar;		-- .
			when X"2C"	=> instruction <= ins_getchar;		-- ,
			when X"00"	=> instruction <= ins_halt;			-- null
			when others	=> instruction <= ins_nope;			-- other
		end case;
	end process decoder_proc;

	-- -----------------------------------------
	--          Multiplexor 1
	-- -----------------------------------------
	-- multiplexor1_proc: process(CLK, selection, ptr_data, pc_data)
	-- begin
	-- 	case selection is
	-- 		when '0'	=> DATA_ADDR <= ptr_data;
	-- 		when '1'	=> CODE_ADDR <= pc_data;
	-- 		when others => --(others => '0')
	-- 	end case;
	-- end process multiplexor1_proc;
	DATA_ADDR <= ptr_data;
	CODE_ADDR <= pc_data;

	-- -----------------------------------------
	--          Multiplexor 2
	-- -----------------------------------------
	multiplexor2_proc: process(CLK, selection2, DATA_RDATA, IN_DATA)
	begin
		case selection2 is
			when "00"	=> DATA_WDATA <= IN_DATA;
			when "01"	=> DATA_WDATA <= DATA_RDATA + "00000001"; -- X"01" -- 1
			when "10"	=> DATA_WDATA <= DATA_RDATA - "00000001"; -- X"01" -- 1
			when "11"	=> DATA_WDATA <= X"00";
			when others => --(others => '0')
		end case;
	end process multiplexor2_proc;

	-- -----------------------------------------
	--          Konečný automat - aktuální stav
	-- -----------------------------------------
	fsm_present_state_proc: process(RESET, CLK)
	begin
		if (RESET = '1') then present_state <= state_idle;
		elsif rising_edge(CLK) and (EN = '1') then	present_state <= next_state;
		end if;
	end process fsm_present_state_proc;

	-- -----------------------------------------
	--          Konečný automat - další stav
	-- -----------------------------------------
	fsm_next_state_proc : process(CLK, RESET, EN, CODE_DATA, IN_VLD, IN_DATA, DATA_RDATA, OUT_BUSY, present_state,
								  instruction, cnt_data, selection2)
	begin
		next_state	<= state_idle;
		CODE_EN		<= '1';
		DATA_EN		<= '0';
		DATA_RDWR	<= '0';
		IN_REQ		<= '0';
		OUT_WE		<= '0';
		pc_inc		<= '0';
		pc_dec		<= '0';
		ptr_inc		<= '0';
		ptr_dec		<= '0';
		cnt_inc		<= '0';
		cnt_dec		<= '0';
		selection2	<= "00";

		case present_state is
			-- IDLE
			when state_idle => next_state <= state_fetch;

			-- FETCH
			when state_fetch =>				-- Načítání instrukcí
				next_state	<= state_decode;
				CODE_EN		<= '1';

			-- DECODE
			when state_decode =>
				case instruction is
					when ins_pointer_inc	=>	next_state <= state_p_inc;
					when ins_pointer_dec	=>	next_state <= state_p_dec;
					when ins_value_inc		=>	next_state <= state_v_inc;
					when ins_value_dec		=>	next_state <= state_v_dec;
					when ins_while_start	=>	next_state <= state_while_start1;
					when ins_while_break	=>	next_state <= state_while_break1;
					when ins_while_end		=>	next_state <= state_while_end1;
					when ins_putchar		=>	next_state <= state_put;
					when ins_getchar		=>	next_state <= state_get;
					when ins_halt 			=>	next_state <= state_halt;
					when others 			=>	next_state <= state_nope;
				end case;

			-- POINTER_INC | >
			when state_p_inc =>
				next_state	<= state_fetch;
				ptr_inc		<= '1';			-- Next cell in memory
				pc_inc		<= '1';			-- Next instruction

			-- POINTER_DEC | <
			when state_p_dec =>
				next_state	<= state_fetch;
				ptr_dec		<= '1';
				pc_inc		<= '1';

			-- VALUE_INC | +
			when state_v_inc =>
				next_state	<= state_v_inc_do;
				DATA_RDWR	<= '0';			-- Čtení
				DATA_EN		<= '1';
			when state_v_inc_do =>			-- Nelze číst a zapisovat v 1 stavu
				next_state	<= state_fetch;
				DATA_EN		<= '1';
				DATA_RDWR	<= '1';			-- Lets write
				pc_inc		<= '1';
				selection2	<= "01";

			-- VALUE_DEC | -
			when state_v_dec =>
				next_state	<= state_v_dec_do;
				DATA_RDWR	<= '0';
				DATA_EN		<= '1';
			when state_v_dec_do =>
				next_state	<= state_fetch;
				DATA_RDWR	<= '1';
				DATA_EN		<= '1';
				pc_inc		<= '1';
				selection2	<= "10";

			-- PUTCHAR | .
			when state_put =>
				if(OUT_BUSY = '1') then
					next_state	<= state_put;
				else -- Jakmile je OUT_BUSY=0, inicializuje se OUT_DATA zapisovanou ASCII hodnotou a současně na jeden hodinový takt OUT_WE na 1
					next_state	<= state_fetch;
					OUT_DATA	<= DATA_RDATA;
					DATA_RDWR	<= '0';
					OUT_WE		<= '1';
					pc_inc		<= '1';
				end if;

			-- GETCHAR | ,
			when state_get =>
				next_state	<= state_get;
				IN_REQ		<= '1';		-- Při požadavku na data procesor nastaví IN_REQ na 1, čeká tak dlouho, dokud IN_VLD (input valid) není roven 1.
				if (IN_VLD = '1') then
					next_state	<= state_fetch;
					DATA_EN		<= '1';
					DATA_RDWR	<= '1';
					pc_inc		<= '1';
					IN_REQ		<= '0'; -- Jamile se tak stane, může přečíst IN_DATA, který obsahuje ASCII hodnotu stisknuté klávesy a deaktivoat IN_REQ.
					selection2	<= "00";
				end if;

			-- WHILE_START | [
			when state_while_start1 =>
				next_state	<= state_while_start2;
				pc_inc		<= '1';
				DATA_EN		<= '1';
				DATA_RDWR	<= '0';
			when state_while_start2 =>
				if (DATA_RDATA = "00000000") then
					next_state <= state_while_start3;
				else
					next_state <= state_fetch;			-- Cannot use state_while_start3 when (DATA_RDATA = "00000000") else state_fetch; 😭
				end if;
			when state_while_start3 =>
				if (cnt_data = "00000000") then
					next_state	<= state_fetch;
					cnt_inc		<= '1';
				else
					next_state	<= state_while_start4;
					CODE_EN		<= '1';
				end if;
			when state_while_start4 =>
				next_state	<= state_while_start3;
				pc_inc		<= '1';
				if (instruction = ins_while_start) then
					cnt_inc	<= '1';
				else
					cnt_dec	<= '1';
				end if;

			-- WHILE_BREAK | ~
			when state_while_break1 =>
				next_state	<= state_while_break2;
				pc_inc		<= '1';
				cnt_inc		<= '1';
			when state_while_break2 =>
				if (cnt_data /= "00000000") then
					CODE_EN		<= '1';
					next_state	<= state_while_break3;
				else
					next_state	<= state_fetch;
				end if;
			when state_while_break3 =>
				next_state	<= state_while_break2;
				pc_inc		<= '1';
				if (instruction = ins_while_start) then	cnt_inc <= '1';
				elsif (instruction = ins_while_end) then	cnt_dec <= '1';
				end if;

			-- WHILE_END | ]
			when state_while_end1 =>
				next_state	<= state_while_end2;
				DATA_RDWR	<= '0';
				DATA_EN		<= '1';
			when state_while_end2 =>
				if (DATA_RDATA = "00000000") then
					next_state	<= state_fetch;
					pc_inc		<= '1';
				else
					next_state	<= state_while_end3;
					cnt_inc		<= '1';
					pc_dec		<= '1';
				end if;
			when state_while_end3 =>
				if (cnt_data = "00000000") then
					next_state	<= state_fetch;
				else
					next_state	<= state_while_end4;
					CODE_EN		<= '1';
				end if;
			when state_while_end4 =>
				next_state	<= state_while_end5;
				if (instruction = ins_while_start) then		cnt_dec	<= '1';
				elsif (instruction = ins_while_end) then	cnt_inc	<= '1';
				end if;
			when state_while_end5 =>
				next_state	<= state_while_end3;
				if (cnt_data = "00000000") then pc_inc <= '1';
				else pc_dec	<= '1';
				end if;

			-- HALT | null
			when state_halt => next_state <= state_halt;

			-- NOPE
			when state_nope =>
				next_state	<= state_fetch;
				pc_inc		<= '1';

			-- OTHERS
			when others => null;
		end case;
	end process fsm_next_state_proc;
end behavioral;
