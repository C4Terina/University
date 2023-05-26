LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity FFSR is port (
D : in bit;
CLK : in bit;
Rst: in bit;
Q : out bit);
end FFSR;

ARCHITECTURE dataflow OF FFSR IS
BEGIN
process(CLK,RST)
begin
 IF RST='1' THEN
    Q<='0';
 ELSIF RISING_EDGE(CLK) then
    Q <= D;
end if;
end process;
END dataflow ;