Library ieee;
use ieee.std_logic_1164.all; 

ENTITY tb_fa IS
END tb_fa;

ARCHITECTURE behavior OF tb_fa IS
 COMPONENT full_adder_vhdl_code
 PORT(
 A : IN bit;
 B : IN bit;
 Cin : IN bit;
 S : OUT bit;
 Cout : OUT bit
 );
 END COMPONENT;


signal A : bit := '0';
signal B : bit := '0';
signal Cin : bit := '0';
signal S : bit;
signal Cout : bit;
 
BEGIN

 uut: full_adder_vhdl_code PORT MAP (
 A => A,
 B => B,
 Cin => Cin,
 S => S,
 Cout => Cout
 );
 
 stim_proc: process
 begin
 A <= '0'; B <= '0'; Cin <= '0'; wait for 10 ps;
 A <= '0'; B <= '1'; Cin <= '0'; wait for 10 ps;
 A <= '1'; B <= '0'; Cin <= '0'; wait for 10 ps;
 A <= '1'; B <= '1'; Cin <= '0'; wait for 10 ps;
 A <= '0'; B <= '0'; Cin <= '1'; wait for 10 ps;
 A <= '0'; B <= '1'; Cin <= '1'; wait for 10 ps;
 A <= '1'; B <= '0'; Cin <= '1'; wait for 10 ps;
 A <= '1'; B <= '1'; Cin <= '1'; wait for 10 ps; 
 
 end process;
 
END;