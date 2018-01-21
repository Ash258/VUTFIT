-- tb.vhd : FPGA top level testbench
-- Copyright (C) 2011 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Zdenek Vasicek <vasicek AT fit.vutbr.cz>
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_textio.all;
use ieee.numeric_std.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity testbench is
end entity testbench;

-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of testbench is

   signal smclk : std_logic := '1';

   signal ledf  : std_logic;
   signal p3m   : std_logic_vector(7 downto 0) := (others=>'Z');   
   signal afbus : std_logic_vector(11 downto 0) :=(others =>'Z');
   signal xbus  : std_logic_vector(45 downto 0) :=(others =>'Z');
   signal rdbus : std_logic_vector(7 downto 0) :=(others =>'Z');
   signal ldbus : std_logic_vector(7 downto 0) :=(others =>'Z');
   signal lrs, lrw, le : std_logic;

   signal ispi_clk : std_logic:='1';
   signal ispi_cs  : std_logic:='1';
   signal ispi_di  : std_logic:='0';    
   signal ispi_do  : std_logic:='0';
   
begin

   -- ==========================================
   -- Top-level entita reprezentujici cele FPGA
   -- ==========================================
   uut: entity work.fpga
      port map(
         SMCLK    => smclk,
         ACLK     => '0',
         FCLK     => '0',
         LEDF     => ledf,
   
         SPI_CLK  => ispi_clk,
         SPI_CS   => '1',
         SPI_FPGA_CS => ispi_cs,
         SPI_DI   => ispi_di,
         SPI_DO   => ispi_do,
   
         KIN      => open,
         KOUT     => (others => '0'),
   
         LE       => le,
         LRW      => lrw,
         LRS      => lrs,
         LD       => ldbus,

         RA       => open,
         RD       => rdbus,
         RDQM     => open,
         RCS      => open,
         RRAS     => open,
         RCAS     => open,
         RWE      => open,
         RCKE     => open,
         RCLK     => open,

         P3M      => p3m,
         AFBUS    => afbus,
         X        => xbus
   );

   -- ==========================================
   -- LCD display model
   -- ==========================================
   lcd: entity work.lcd
   port map(
      LRS => lrs,
      LRW => lrw,
      LE => le,
      LD => ldbus
   );

   -- ==========================================================================
   -- Clock generator 7.4MHz
   -- ==========================================================================
   smclk <= not smclk after 67.5 ns;

   -- ==========================================================================
   -- Reset generator
   -- ==========================================================================
   p3m(0) <= '1', '0' after 500 ns;

   -- ==========================================================================
   -- SPI clock generator (SMCLK/4)
   -- ==========================================================================
   ispi_clk <= not ispi_clk after 4*67.5 ns;
  
end architecture behavioral;
