LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY Uart_Decoder IS
    GENERIC( 
            BaudRate    : IN INTEGER := 9600;
            ClockRate   : IN INTEGER := 50_000_000
	       );
	PORT( 
            Clk, Rx     : IN STD_LOGIC;
            Complete    : OUT STD_LOGIC;
            Data        : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
		);
END Uart_Decoder;

ARCHITECTURE Behavior OF Uart_Decoder IS
    SIGNAL started  : STD_LOGIC;            -- Whether we've started or not
    SIGNAL bit_location : Integer RANGE 0 TO 9 := 0;     -- Where to save the bit
    SIGNAL data_reg : STD_LOGIC_VECTOR(9 DOWNTO 0); -- Local copy of the data, including start and stop bit
BEGIN

    PROCESS (Rx, bit_location)
    BEGIN
        IF bit_location = 9 THEN
            started <= '0';
        ELSIF Rx = '0' AND Rx'event THEN
            started <= '1';
        END IF;
    END PROCESS;
    
    PROCESS (Clk, Rx, started)
    VARIABLE counter : Integer RANGE 0 TO ((ClockRate / BaudRate)+1) := 0;
    BEGIN
        IF Clk = '1' AND Clk'event THEN
            IF started = '1' THEN
                counter := counter + 1;
                IF counter = ((ClockRate) / BaudRate) THEN
                    counter := 0;
                    bit_location <= bit_location + 1;
                ELSIF counter = (ClockRate / (BaudRate * 2)) THEN
                    data_reg(bit_location) <= Rx;
                END IF;
            ELSE
                bit_location <= 0;
                counter := 0;
            END IF;
        END IF;
    END PROCESS;
    
    Complete <= NOT started;
    Data <= data_reg(8 DOWNTO 1);

END Behavior;
