entity latch is port (	 
	D: in bit;
	EN: in bit; 
	Q: out bit);
end latch;

architecture bhv of latch is
begin
	process (EN, D)
	begin
    	if (EN = '1') then
        	Q <= D;
    	end if;
end process;
	

end bhv;