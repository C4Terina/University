library ieee;

use ieee.std_logic_1164.all;

use ieee.std_logic_unsigned.all;

 

entity gray_counter is port (

 cout   :out std_logic_vector (3 downto 0);

 clk    :in  std_logic;                    

 reset  :in  std_logic);

end gray_counter;

 

 architecture rtl of gray_counter is

 signal c: std_logic_vector (3 downto 0);

 begin

  process (clk, reset)

   begin

    if (reset = '1') then

     c <= (others=>'0');

    elsif (clk'event and (clk='1')) then

      c <= c + 1;

   end if;

  end process;

  cout <= (c(3) &

       (c(3) xor c(2)) &

       (c(2) xor c(1)) &

       (c(1) xor c(0)) );

 end architecture;