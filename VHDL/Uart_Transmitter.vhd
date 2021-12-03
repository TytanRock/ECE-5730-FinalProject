LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY Uart_Transmitter IS
    GENERIC( 
            BaudRate    : IN INTEGER := 9600;
            ClockRate   : IN INTEGER := 50_000_000
	       );
	PORT( 
            Clk, Send     : IN STD_LOGIC;
            Data          : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
            Tx            : OUT STD_LOGIC
		);
END Uart_Transmitter;

ARCHITECTURE Behavior OF Uart_Transmitter IS
    SIGNAL started  : STD_LOGIC;            -- Whether we've started or not
    SIGNAL bit_location : Integer RANGE 0 TO 9 := 0;     -- Where to save the bit
BEGIN

    PROCESS (Send, bit_location)
    BEGIN
        IF bit_location = 9 THEN
            started <= '0';
        ELSIF Send = '1' AND Send'event THEN
            started <= '1';
        END IF;
    END PROCESS;
    
    PROCESS (Clk, started, Data)
    VARIABLE counter : Integer RANGE 0 TO ((ClockRate*2) / BaudRate) := 0;
    BEGIN
        IF Clk = '1' AND Clk'event THEN
            IF started = '1' THEN
                counter := counter + 1;
                IF counter = ((ClockRate) / BaudRate) THEN
                    counter := 0;
                    bit_location <= bit_location + 1;
                ELSIF counter = (ClockRate / (BaudRate*2)) THEN                    
                    -- Send the start bit
                    IF(bit_location = 0) THEN
                        Tx <= '0';
                    -- Send data bits
                    ELSIF bit_location > 0 AND bit_location < 9 THEN
                        Tx <= Data(bit_location - 1);
                    -- Send the stop bit
                    ELSE
                        Tx <= '1';
                    END IF;
                END IF;
            ELSE
                bit_location <= 0;
                counter := 0;
                Tx <= '1';
            END IF;
        END IF;
    END PROCESS;

END Behavior;
