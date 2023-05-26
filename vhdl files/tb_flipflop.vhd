LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity tb_flipflop is end tb_flipflop;

architecture behavioral of tb_flipflop is 
signal Q1: bit;
signal D1: bit;
signal CLK1: bit;
signal Rst1: bit;
component FFSR port (
D: in bit;
CLK:in bit;
Rst: in bit;
Q: out bit);
end component;

begin
M1: FFSR port map (D=>D1,CLK=>CLK1, Q=>Q1, Rst=>Rst1);
process
begin
 CLK1<='0' ; wait for 100 ns;
 CLK1<='1' ; wait for 100 ns;
 CLK1<='0' ; wait for 100 ns;
 CLK1<='1' ; wait for 100 ns;
 CLK1<='0' ; wait for 100 ns;
 CLK1<='1' ; wait for 100 ns;
 CLK1<='0' ; wait for 100 ns;
 CLK1<='1' ; wait for 100 ns;
end process;
process
begin
 D1<='0' ; wait for 150 ns;
 D1<='1' ; wait for 250 ns;
 D1<='0' ; wait for 50 ns;
 D1<='1' ; wait for 350 ns;
 
end process;
process
begin
 Rst1 <= '1'; wait for 400 ns;
 Rst1 <= '0'; wait for 400 ns;
end process;
end behavioral;