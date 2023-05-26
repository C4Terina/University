LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity exam2 is 
port(
 A: in bit;
 B: in bit;
 C: in bit;
 Z: out bit);
end exam2;

architecture behavioral of exam2 is 
	signal D, E: bit;
begin
	D <= A OR B;
	E <= C OR A;
	Z <= D AND E;
	
end behavioral;