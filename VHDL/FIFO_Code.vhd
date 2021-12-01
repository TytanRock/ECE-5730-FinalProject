library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity FIFO is
    generic (num : in integer := 32);
    port (  complete : in std_logic;
            data_in : in std_logic_vector(7 downto 0);
            pop : in std_logic;
            data_out : out std_logic_vector (7 downto 0));
end FIFO;

architecture behavior of FIFO is

type fifo_size is array (0 to num-1) of std_logic_vector (7 downto 0);
signal mem : fifo_size; --declaring 32  buffers with 8 bit wide 
signal stop : integer range 0 to num-1 := 0;
signal start : integer range 0 to num-1 := 0;

begin
    --at the rising edge of complete
    --data is received into buffer
    --if index of mem reaches num (32) the index is changed ot 0
    process(complete, pop, data_in)
    variable newStart : integer range 0 to num-1;
    variable newEnd : integer range 0 to num-1;
    begin
        if complete'event and complete = '1' then
            newEnd := stop - 2;
            if not(start = newEnd) then
                start <= start + 1;
                if(start = num-1) then
                    mem(0) <= data_in;
                else
                    mem(start + 1) <= data_in;
                end if;
            end if;
        end if;
        --assuming pop as a 1 bit input
        --first value from the queue is stored into data_out object
        --queue is updated
        newStart := start - 1;
        if pop'event and pop = '1' then
            if not (newStart = stop) then 
                stop <= stop + 1;
            end if;
        end if;
        
        if(stop = num - 1) then
            data_out <= mem(0);
        else
            data_out <= mem(stop + 1);
        end if;
    end process;
end;
 
      
    


