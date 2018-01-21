-- top.vhd : TOP level entity, Brainlove microcontroller
-- Copyright (C) 2017 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Zdenek Vasicek
--

library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.std_logic_ARITH.ALL;
use IEEE.std_logic_UNSIGNED.ALL;

architecture main of tlv_bare_ifc is
	-- displej
	signal lcd_data  : std_logic_vector(7 downto 0);
	signal lcd_we, lcd_busy    : std_logic;

	signal rom_addr : std_logic_vector(11 downto 0);
	signal rom_dout : std_logic_vector(7 downto 0);
	signal rom_en   : std_logic;

	signal ram_addr: std_logic_vector(9 downto 0);
	signal ram_rdata: std_logic_vector(7 downto 0);
	signal ram_wdata: std_logic_vector(7 downto 0);
	signal ram_rdwr: std_logic;
	signal ram_en   : std_logic;

	signal in_data : std_logic_vector(7 downto 0);
	signal in_req : std_logic;
	signal kb_ack : std_logic;
	signal in_vld : std_logic := '0';

	signal timer : integer range 0 to 20000;
	signal cpu_rst : std_logic;
	signal cpu_en : std_logic := '0';

	component cpu is
		port (
			RESET : in std_logic;
			CLK   : in std_logic;
			EN    : in std_logic;

			-- ROM mem
			CODE_ADDR : out std_logic_vector(11 downto 0);
			CODE_DATA : in std_logic_vector(7 downto 0);
			CODE_EN   : out std_logic;

			-- RAM mem
			DATA_ADDR  : out std_logic_vector(9 downto 0);
			DATA_WDATA : out std_logic_vector(7 downto 0);
			DATA_RDATA : in std_logic_vector(7 downto 0);
			DATA_RDWR  : out std_logic;
			DATA_EN    : out std_logic;

			-- INPUT
			IN_DATA   : in std_logic_vector(7 downto 0);
			IN_VLD    : in std_logic;
			IN_REQ    : out std_logic;

			-- OUTPUT
			OUT_DATA : out  std_logic_vector(7 downto 0);
			OUT_BUSY : in std_logic;
			OUT_WE   : out std_logic
		);
	end component;

begin
	-- ================================================
	-- Procesor
	-- ================================================
	bfcpu: cpu
	port map(
		--Ridici signaly
		RESET => cpu_rst, -- Reset
		CLK   => CLK,   -- Hodiny
		EN    => cpu_en,   -- povoleni cinnosti

		--ROM
		CODE_ADDR => rom_addr,
		CODE_DATA => rom_dout,
		CODE_EN   => rom_en,

		--RAM
		DATA_ADDR => ram_addr,
		DATA_RDATA => ram_rdata,
		DATA_WDATA => ram_wdata,
		DATA_RDWR => ram_rdwr,
		DATA_EN   => ram_en,

		--INPUT
		IN_DATA   => in_data,
		IN_VLD    => in_vld,
		IN_REQ    => in_req,

		--OUTPUT
		OUT_DATA  => lcd_data,
		OUT_BUSY  => lcd_busy,
		OUT_WE    => lcd_we
	);

	-- ================================================
	-- Pamet programu
	-- ================================================
	rom_mem: entity work.rom
	generic map (
		-- Inicializace obsahu pameti ROM (pamet programu obsahujici kod v jazyce BrainFuck),
		-- odkomentovat vzdy pouze jeden radek nastavujici generickou promennou INIT

		-- Vyuziti programu pro overeni cinnosti:
		--  [1] - overeni vystupu
		--  [2], [5] - overeni jednoduche while smycky a vystupu
		--  [3] - overeni vstupu a vystupu
		--  [4] - overeni vstupu a vystupu, vlozene komentare
		--  [6], [7], [8] - overeni korektni funkce vnorenych smycek, vstupu a vystupu
		--- [9] - overeni instrukce ~

		-- [1] Vypis textu ABCDEFGHIJKL na displej
		-- INIT => "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+.+.+.+.+.+.+.+.+.+.+++++++++++++.+." & nul

		-- [2] Vypis textu na displej
		-- INIT => "++++++++++[>+++++++>+++>+++++<<<-]>+++.+++++.++.>>-----.+++++.--.+.++++++.----------.<<++++++++++++++++++++++++++++++++.++.---.-----.>>+++++." & nul

		-- [3] Vypis znaku stisknutych na klavesnici na displej (vypise se max. 10 znaku, pote se program ukonci)
		-- INIT => "++++++++++[>,.<-] 10x opakovat nacteni znaku a zapis na display" & nul

		-- [4] Vypis znaku stisknutych na klavesnici na displej (vypisuje se dokud neni stisknuta klavesa * nebo # (tzn. konec radku))
		-- INIT => "+[->,[>+>+<<-] nacteni vstupu do bunky 1 kopirovani nactene hodnoty do bunky 2 a 3 +>---------- odecteni 10 od bunky 2 [>.<[-]<<+>>>[-]<  pokud byla hodnota bunky 2 rozdilna od 0 vypis na display znulovani bunky 2 znulovani bunky 3]<<]" & nul

		-- [5] Vypis druhych mocnin od 0 do 10000
		-- INIT => "++++[>+++++<-]>[<+++++>-]+<+[    >[>+>+<<-]++>>[<<+>>-]>>>[-]++>[-]+    >>>+[[-]++++++>>>]<<<[[<++++++++<++>>-]+<.<[>----<-]<]    <<[>>>>>[>>>[-]+++++++++<[>-<-]+++++++++>[-[<->-]+[<<<]]<[>+<-]>]<<-]<<-]" & nul

		-- [6] Vypis prvocisel (vypis prvocisel na displej az do maxima zadaneho na klavesnici; postup: zadat cislo, potvrdit klavesou #)
		-- INIT => "+[->,----------[<+>-------------------------------------->[>+>+<<-]>>[<<+>>-]<>>>+++++++++[<<<[>+>+<<-]>>[<<+>>-]<[<<+>>-]>>-]<<<[-]<<[>+<-]]<]>>[<<+>>-]<<>+<-[>+[>+>+<<-]>>[<<+>>-]<>+<-->>>>>>>>+<<<<<<<<[>+<-<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<<<>[>>+>+<<<-]>>>[<<<+>>>-]<<<<>>>[>+>+<<-]>>[<<+>>-]<<<[>>>>>+<<<[>+>+<<-]>>[<<+>>-]<[>>[-]<<-]>>[<<<<[>+>+<<-]>>[<<+>>-]<>>>-]<<<-<<-]+>>[<<[-]>>-]<<>[-]<[>>>>>>[-]<<<<<<-]<<>>[-]>[-]<<<]>>>>>>>>[-<<<<<<<[-]<<[>>+>+<<<-]>>>[<<<+>>>-]<<<>>[>+<-]>[[>+>+<<-]>>[<<+>>-]<>+++++++++<[>>>+<<[>+>[-]<<-]>[<+>-]>[<<++++++++++>>-]<<-<-]+++++++++>[<->-]<[>+<-]<[>+<-]<[>+<-]>>>[<<<+>>>-]<>+++++++++<[>>>+<<[>+>[-]<<-]>[<+>-]>[<<++++++++++>>>+<-]<<-<-]>>>>[<<<<+>>>>-]<<<<>[-]<<+>]<[[>+<-]+++++++[<+++++++>-]<-><.[-]>>[<<+>>-]<<-]>++++[<++++++++>-]<.[-]>>>>>>>]<<<<<<<<>[-]<[-]<<-]++++++++++.[-]" & nul

		-- [7] Faktorizace cisla (rozklad cisla zadaneho na klavesnici na prvocisla a zobrazeni na displej; postup: zadat cislo, potvrdit klavesou #; overeni viz http://www.numberempire.com/numberfactorizer.php)
		-- INIT => ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>-<<<<<<<<<+[-[>>>>>>>>>>][-]<<<<<<<<<<[[->>>>>>>>>>+<<<<<<<<<<]<<<<<<<<<<]>>>>>>>>>>,----------]>>>>>>>>>>[------------------------------------->>>>>>>>>->]<[+>[>>>>>>>>>+>]<-<<<<<<<<<<]-[>++++++++++++++++++++++++++++++++++++++++++++++++.------------------------------------------------<<<<<<<<<<<]++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.--------------------------.[-]>>>>>>>>>>>>++<<<<+[[-]>>[>>>>[-]>[-]>[-]>[-]>[-]>[-]<<<<<<<[->>>+>+<<<<]>>>>>>>>]<<<<<<<<<<[>>>>>>[-<<<<+>>>>]<<<<<<<<<<<<<<<<]>>>>>>>>>>[>[->>>+>>+<<<<<]>>>>>>>>>]<<<<<<<<<<[>>>>>>[-<<<<<+>>>>>]<<<<<<<<<<<<<<<<]>>>>>>>>>>[>>>[-]>>>[-]>[-]>>>]<<<<<<<<<<[<<<<<<<<<<]>>>>>>>>>[-]>>>>>>>+<<<<<<<<[+]+[->>[>>>>>>[->++<]>>>>]<<<<<<<<<<[>>>>>>>>[-]>[-]<<<<[->>>++<<<]<<<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>>[->+<[->+<[->+<[->+<[->+<[->+<[->+<[->+<[->+<[->--------->>>>>>>>>+<<<<<<<<<<[->+<]]]]]]]]]]]>>]<<<<<<<<<<[>>>>>>>>>[-<+<<<+>>>>]<<<<<<<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>[-<+>[-<+>[-<+>[-<+>[-<+>[-<+>[-<+>[-<+>[-<+>[-<--------->>>>>>>>>>>+<<<<<<<<<<[-<+>]]]]]]]]]]]>>>]<<<<<<<<<<[>>>>[->>>+>>+<<<<<]<<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>[-<<<+>>>]>>>]<<<<<<<<<<[>>>>>>>>[->-<]>[<<<<<<<<<[<[-]>>>>>>>>>>[-<<<<<<<<<<+>>>>>>>>>>]<<<<<<<<<<<<<<<<<<<]>>>>>>>>>>>>>>>>>>>]<<<<<<<<<<<<<<<<<<<]>>>>>>>>>[+[+[+[+[+[+[+[+[+[+[[-]<+>]]]]]]]]]]]<]>>>>>>>>[<<<<<<[>>>>>>>>[-]>[-]<<<<<[->>>+>+<<<<]>>>>>>]<<<<<<<<<<[>>>>>>>>[-<<<<+>>>>]<<<[->>>+>+<<<<]<<<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>>>[-<<<<+>>>>]>]<<<<<<<<<<[>>>>>>>>[-<->]<<<<<<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>[->+<[->+<[->+<[->+<[->+<[->+<[->+<[->+<[->+<[->+<[++++++++++[+>-<]>>>>>>>>>>-<<<<<<<<<<]]]]]]]]]]]>>>]>>>>>>>+[[-]<<<<<<<<<<<<<<<<<[>>>>[-]>>>>[-<<<<+>>>>]<<[->>+<<]<<<<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>>[->+<<<+>>]>>]<<<<<<<<<<[>>>[->>>>>>+<<<<<<]<<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<+>>>>>>[-<<<<<<--------->>>>>>>>>>>>>>>>+<<<<<<<<<<[-<<<<<<+>>>>>>]]]]]]]]]]]>]>>>>>>>]<<<<<<<<<<<<<<<<<[<<<<<<<<<<]>>>>>>>>>>[>>>>>>>>[-]<<[->+<]<[->>>+<<<]>>>>>]<<<<<<<<<<[+>>>>>>>[-<<<<<<<+>>>>>>>[-<<<<<<<->>>>>>+>[-<<<<<<<+>>>>>>>[-<<<<<<<->>>>>>+>[-<<<<<<<+>>>>>>>[-<<<<<<<->>>>>>+>[-<<<<<<<+>>>>>>>[-<<<<<<<->>>>>>+>[-<<<<<<<+>>>>>>>]]]]]]]]]<<<<<<<[->>>>>>>+<<<<<<<]-<<<<<<<<<<]>>>>>>>[-<<<<<<<<<<<+>>>>>>>>>>>]>>>[>>>>>>>[-<<<<<<<<<<<+++++>>>>>>>>>>>]>>>]<<<<<<<<<<[+>>>>>>>>[-<<<<<<<<+>>>>>>>>[-<<<<<<<<->>>>>+>>>[-<<<<<<<<+>>>>>>>>[-<<<<<<<<->>>>>+>>>[-<<<<<<<<+>>>>>>>>[-<<<<<<<<->>>>>+>>>[-<<<<<<<<+>>>>>>>>[-<<<<<<<<->>>>>+>>>[-<<<<<<<<+>>>>>>>>]]]]]]]]]<<<<<<<<[->>>>>>>>+<<<<<<<<]-<<<<<<<<<<]>>>>>>>>[-<<<<<<<<<<<<<+>>>>>>>>>>>>>]>>[>>>>>>>>[-<<<<<<<<<<<<<+++++>>>>>>>>>>>>>]>>]<<<<<<<<<<[<<<<<<<<<<]>>>>>>>>>>>>>>>>]<<<<<<[>>>[->>>>+>+<<<<<]>>>>>>>]<<<<<<<<<<[>>>>>>>[-<<<<+>>>>]<<<<<[->>>>>+>>+<<<<<<<]<<<<<<<<<<<<]>>>>>>>>>>[>>>>>>>[-<<<<<+>>>>>]>>>]<<<<<<<<<<[>>>>>>>>>[-<->]<[<<<<<<<<[<<[-]>>>>>>>>>>[-<<<<<<<<<<+>>>>>>>>>>]<<<<<<<<<<<<<<<<<<]>>>>>>>>>>>>>>>>>>]<<<<<<<<<<<<<<<<<<]>>>>>>>>[>-<[+[+[+[+[+[+[+[+[+[[-]>+<]]]]]]]]]]]>+[[-]<[-]+>>>>+>>>>>>>>[>>>>>>>>>>]<<<<<<<<<<[<<<<<<[<<<<[<<<<<<<<<<]>>>>+<<<<<<<<<<]<<<<]>>>>>>>>>>>>>>>>>>>>[>>>>>>>>>>]<<<<<<<<<<[<<<<<<<<<<]>>>>-[[+]>>>>>>>>-<<[>[-]>>[-<<+>>]>>>>>>>]<<<<<<<<<<[+>>[>>>>>>>>+>>]<<-<<<<<<<<<<]-[>>++++++++++++++++++++++++++++++++++++++++++++++++.------------------------------------------------<<<<<<<<<<<<]++++++++++++++++++++++++++++++++.[-]>>>>]>>>>>>[>>[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>+<<<<<[->>>>>--------->>>>>+<<<<<<<<<<[->>>>>+<<<<<]]]]]]]]]]]>>>>>>>>]<<<<<<<<<<[>>>>>>>[-<<<<<+>>>>>]<<<<<<<<<<<<<<<<<]>>>>>>>>>]<]>>[>>>>>>>>>>]<<<<<<<<<<[+>[>>>>>>>>>+>]<-<<<<<<<<<<]-[>++++++++++++++++++++++++++++++++++++++++++++++++.<<<<<<<<<<<]++++++++++." & nul

		-- [8] Prevod binarniho cisla na ASCII (ocekava na klavesnici zadat 8-bitove binarni cislo, tj. stisk osmi klaves 0 / 1, pote vypise ASCII znak)
		-- INIT => ">,[>>>++++++++[<[<++>-]<+[>+<-]<-[-[-<]>]>[-<]<,>>>-]<.[-]<<]"

		-- [9] Vypis textu ABCD na displej, vyuziti instrukce ~
		-- INIT => "+[++++++++++++++~++++]++++++++++++++++++++++++++++++++++++++++++++[++++++~-----------------------------].+.+.+." & nul

		-- [10] Výpis mého loginu
		-- INIT => "+++++ +++++[> +++++ +++++ ++ > +++++ << - ] >-+. ---------------------. --. +. +++. +++++++++++++. > --.." & nul

		-- [11] Výpis sračky z hodnocení
		INIT => "[........]noLCD[.........]" & nul

	)
	port map (
		CLK => CLK,
		EN => rom_en,
		ADDR => rom_addr,
		DATA => rom_dout
	);

	-- ================================================
	-- Pamet dat
	-- ================================================
	ram_mem: entity work.ram
	port map(
		CLK   => CLK,
		-- RAM
		ADDR  => ram_addr,
		RDATA => ram_rdata,
		WDATA => ram_wdata,
		EN    => ram_en,
		RDWR  => ram_rdwr
	);

	-- ================================================
	-- Radic LCD displeje
	-- ================================================
	lcd_u : entity work.lcd_controller
	generic map (
		-- pragma translate off
		-- Pouze pro ucely simulace se zkrati trvani prikazu zapisu na displej.
		-- Pri synteze se pouzije vychozi hodnota nastavena v radici lcd_controller.
		CMDLEN => 1000,
		-- pragma translate on

		-- Pro FITkit s dvouradkovym displejem nastavit na True, jinak False
		-- Pro ucely simulace je tato promenna ignorovana, nebot simulacni model je napsan pouze pro jednoradkovy displej
		LCD2x16 => True
	)
	port map(
		CLK         => CLK,
		RST         => cpu_rst,

		-- user interface
		DATA_IN     => lcd_data,
		WRITE_EN    => lcd_we,
		BUSY        => lcd_busy,

		-- lcd interface
		DISPLAY_RS    => LRS,
		DISPLAY_RW    => LRW,
		DISPLAY_EN    => LE,
		DISPLAY_DATA  => LD
	);

	-- ================================================
	-- Radic klavesnice
	-- ================================================
	kb_u : entity work.kb_controller
	port map(
		CLK         => CLK,
		RST         => RESET,

		-- user interface
		DATA        => in_data,
		DATA_VLD    => in_vld,
		DATA_REQ    => in_req,
		REQ_ACK     => kb_ack,

		-- lcd interface
		KB_IN    => KIN,
		KB_OUT    => KOUT
	);

	--pokud se ceka na stisk tlacitka, rozsvitit diodu D4
	LEDF <= not kb_ack;


	-- ================================================
	-- Osetreni nulovani a povoleni cinnosti
	-- ================================================
	-- Protoze pamet nelze inicializovat na nuly,
	-- nesmime dovolit vicenasobny reset procesoru

	process (RESET, CLK)
	begin
		if (RESET = '1') then
			timer <= 0;
		elsif (CLK'event) and (CLK = '1') then
			if (timer = 20000) then -- po cca 1ms po resetu povolime cinnost CPU
				cpu_en <= '1';
			else
				timer <= timer + 1;
			end if;
		end if;
	end process;

	cpu_rst <= RESET when cpu_en = '0' else '0';

end main;
