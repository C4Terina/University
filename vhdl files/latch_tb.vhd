entity latch_tb is
end entity;

architecture tb of latch_tb is
signal D, EN, Q: in bit;

component latch port (
	D, EN, Q: in bit);
end component;

begin
L1: latch port map (D=>D1, EN=>EN1,Q=>Q1);
process
begin
	EN1 <= '0'; D <= '0'; wait for 250 ns;
	EN1 <= '1'; D <= '1'; wait for 150 ns;
	EN1 <= '0'; D <= '0'; wait for 250 ns;
	EN1 <= '1'; D <= '0'; wait for 150 ns;
	EN1 <= '0'; D <= '0'; wait for 100 ns;
	EN1 <= '0'; D <= '0'; wait for 100 ns;
	EN1 <= '0'; D <= '0'; wait for 100 ns;
	EN1 <= '0'; D <= '0'; wait for 100 ns;
	EN1 <= '0'; D <= '0'; wait for 50 ns;
	EN1 <= '0'; D <= '0'; wait for 50 ns;

end process;
end tb;