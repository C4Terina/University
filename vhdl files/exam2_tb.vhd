LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity exam2_tb is
end exam2_tb;


architecture behavioral of exam2_tb is
	
	signal a_t, b_t, c_t: bit;
	signal z_t	: bit;
	

	component exam2 
	port(
		A: in bit;
 		B: in bit;
		C: in bit;
 		Z: out bit
	    );
	end component;

begin 
	UUI: exam2
		port map(a_t, b_t, c_t, z_t);
process 
begin
	a_t <= '0'; b_t <= '0'; c_t <= '0'; wait for 10 ps;
	a_t <= '0'; b_t <= '0'; c_t <= '1'; wait for 10 ps;
	a_t <= '0'; b_t <= '1'; c_t <= '0'; wait for 10 ps;
	a_t <= '0'; b_t <= '1'; c_t <= '1'; wait for 10 ps;
	a_t <= '1'; b_t <= '0'; c_t <= '0'; wait for 10 ps;
	a_t <= '1'; b_t <= '0'; c_t <= '1'; wait for 10 ps;
	a_t <= '1'; b_t <= '1'; c_t <= '0'; wait for 10 ps;
	a_t <= '1'; b_t <= '1'; c_t <= '1'; wait for 10 ps;
	
end process;
	

end behavioral;