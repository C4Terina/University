LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity exam_tb is
end exam_tb;


architecture behavioral of exam_tb is
	
	signal a_t, b_t: bit;
	signal z_t	: bit;

	component exam 
	port(
		A: in bit;
 		B: in bit;
 		Z: out bit
	    );
	end component;

begin 
	UUI: exam
		port map(a_t, b_t, z_t);
process 
begin
	a_t <= '0'; b_t <= '0'; wait for 10 ps;
	a_t <= '0'; b_t <= '1'; wait for 10 ps;
	a_t <= '1'; b_t <= '0'; wait for 10 ps;
	a_t <= '1'; b_t <= '1'; wait for 10 ps;
end process;
	

end behavioral;