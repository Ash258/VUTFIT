-- fsm.vhd: Finite State Machine
-- Author(s): Jakub Čábera <xcaber00@stud.fit.vutbr.cz>
--

library ieee;
use ieee.std_logic_1164.all;

entity fsm is
	port(
		CLK			:	in  std_logic;
		RESET		:	in  std_logic;

		-- Inputs
		KEY			:	in  std_logic_vector(15 downto 0); -- Keyboard
		CNT_OF		:	in  std_logic;

		-- Outputs
		-- Moor
		FSM_CNT_CE	:	out std_logic;
		FSM_MX_MEM	:	out std_logic;
		FSM_MX_LCD	:	out std_logic;
		-- Mealy
		FSM_LCD_CLR	:	out std_logic;
		FSM_LCD_WR	:	out std_logic
	);
end entity fsm;

architecture behavioral of fsm is
	type t_state is (
		START,
		TEST1_0,
		TEST2_0,
		TEST3_0,
		TEST4_1, TEST4_2,
		TEST5_1, TEST5_2,
		TEST6_1, TEST6_2,
		TEST7_1, TEST7_2,
		TEST8_1, TEST8_2,
		TEST9_1, TEST9_2,
		TEST10_2, TEST10_1,
		TEST11_2,
		WRONG, PRINT_MSG_WRONG, PRINT_MSG_RIGHT,
		FINISH
	);
	signal present_state, next_state : t_state;
begin

-- -------------------------------------------------------
	sync_logic : process(RESET, CLK)
	begin
		if (RESET = '1') then
			present_state <= START;
		elsif (CLK'event AND CLK = '1') then
			present_state <= next_state;
		end if;
	end process sync_logic;

-- -------------------------------------------------------

	next_state_logic : process(present_state, KEY, CNT_OF)
	begin
		case (present_state) is
			when START =>
				next_state <= START;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(2) = '1') then
						next_state <= TEST1_0;
					end if;
				end if;

			when TEST1_0 =>
				next_state <= TEST1_0;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(7) = '1') then
						next_state <= TEST2_0;
					end if;
				end if;

			when TEST2_0 =>
				next_state <= TEST2_0;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(6) = '1') then
						next_state <= TEST3_0;
					end if;
				end if;

			when TEST3_0 =>
				next_state <= TEST3_0;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(3) = '1') then
						next_state <= TEST4_1;
					end if;
					if (KEY(1) = '1') then
						next_state <= TEST4_2;
					end if;
				end if;

			when TEST4_1 =>
				next_state <= TEST4_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(3) = '1') then
						next_state <= TEST5_1;
					end if;
				end if;

			when TEST4_2 =>
				next_state <= TEST4_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(6) = '1') then
						next_state <= TEST5_2;
					end if;
				end if;

			when TEST5_1 =>
				next_state <= TEST5_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(5) = '1') then
						next_state <= TEST6_1;
					end if;
				end if;

			when TEST5_2 =>
				next_state <= TEST5_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(7) = '1') then
						next_state <= TEST6_2;
					end if;
				end if;

			when TEST6_1 =>
				next_state <= TEST6_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(8) = '1') then
						next_state <= TEST7_1;
					end if;
				end if;

			when TEST6_2 =>
				next_state <= TEST6_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(9) = '1') then
						next_state <= TEST7_2;
					end if;
				end if;

			when TEST7_1 =>
				next_state <= TEST7_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(5) = '1') then
						next_state <= TEST8_1;
					end if;
				end if;

			when TEST7_2 =>
				next_state <= TEST7_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(2) = '1') then
						next_state <= TEST8_2;
					end if;
				end if;

			when TEST8_1 =>
				next_state <= TEST8_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(7) = '1') then
						next_state <= TEST9_1;
					end if;
				end if;

			when TEST8_2 =>
				next_state <= TEST8_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(8) = '1') then
						next_state <= TEST9_2;
					end if;
				end if;

			when TEST9_1 =>
				next_state <= TEST9_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(6) = '1') then
						next_state <= TEST10_1;
					end if;
				end if;

			when TEST9_2 =>
				next_state <= TEST9_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(8) = '1') then
						next_state <= TEST10_2;
					end if;
				end if;

			when TEST10_1 =>
				next_state <= TEST10_1;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_RIGHT;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
				end if;

			when TEST10_2 =>
				next_state <= TEST10_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
					if (KEY(0) = '1') then
						next_state <= TEST11_2;
					end if;
				end if;

			when TEST11_2 =>
				next_state <= TEST11_2;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_RIGHT;
				elsif KEY(15 downto 0) /= "0000000000000000" then
					next_state <= WRONG;
				end if;

			when WRONG =>
				next_state <= WRONG;
				if KEY(15) = '1' then
					next_state <= PRINT_MSG_WRONG;
				end if;

			when PRINT_MSG_RIGHT =>
				next_state <= PRINT_MSG_RIGHT;
				if (CNT_OF = '1') then
					next_state <= FINISH;
				end if;

			when PRINT_MSG_WRONG =>
				next_state <= PRINT_MSG_WRONG;
				if (CNT_OF = '1') then
					next_state <= FINISH;
				end if;

			when FINISH =>
				next_state <= FINISH;
				if KEY(15) = '1' then
					next_state <= START;
				end if;

			when others => next_state <= START;
		end case;

	end process next_state_logic;

-- -------------------------------------------------------

	output_logic : process(present_state, KEY)
	begin
		FSM_CNT_CE		<= '0';
		FSM_MX_MEM		<= '0';
		FSM_MX_LCD		<= '0';
		FSM_LCD_WR		<= '0';
		FSM_LCD_CLR		<= '0';

		case (present_state) is
			when PRINT_MSG_RIGHT =>
				FSM_CNT_CE		<= '1';
				FSM_MX_MEM		<= '1';
				FSM_MX_LCD		<= '1';
				FSM_LCD_WR		<= '1';
			when PRINT_MSG_WRONG =>
				FSM_CNT_CE		<= '1';
				FSM_MX_MEM		<= '0';
				FSM_MX_LCD		<= '1';
				FSM_LCD_WR		<= '1';
			when FINISH =>
				if (KEY(15) = '1') then
					FSM_LCD_CLR	<= '1';
				end if;
			when others =>
				if (KEY(14 downto 0) /= "000000000000000") then
					FSM_LCD_WR	<= '1';
				end if;
				if (KEY(15) = '1') then
					FSM_LCD_CLR	<= '1';
				end if;
		end case;
	end process output_logic;

end architecture behavioral;
