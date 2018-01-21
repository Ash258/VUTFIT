library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity testbench is
end testbench;

architecture behv of testbench is

    component ledc8x8 is
    port (  SMCLK, RESET: in std_logic;
            ROW, LED: out std_logic_vector(0 to 7)
    );
    end component;

    signal smclk: std_logic := '0';
    signal reset: std_logic;
    signal row, led: std_logic_vector(0 to 7);

    constant period: time := 135.6 ns; -- odvozeno od f(SMCLK) = 7.3728 MHz

begin

    uut: ledc8x8 port map(smclk, reset, row, led);

    smclk <= not smclk after period / 2;

    test: process
    begin
        reset <= '1';
        wait until smclk'event and smclk = '1';
        reset <= '0';
        wait;
    end process;

end behv;
