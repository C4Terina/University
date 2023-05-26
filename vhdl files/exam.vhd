LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity exam is 
port(
 A: in bit;
 B: in bit;
 Z: out bit);
end exam;

architecture behavioral of exam is 
	signal C, E, D: bit;
begin

	C <= NOT A;
	D <= A OR B;
	E <= C AND D;
	Z <= E OR D;

end behavioral;