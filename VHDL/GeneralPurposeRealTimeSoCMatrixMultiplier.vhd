LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY GeneralPurposeRealTimeSoCMatrixMultiplier IS
	PORT( CLOCK_50  : IN STD_LOGIC;
          SW        : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
			 UART_RX : IN STD_LOGIC; 
			 UART_TX : OUT STD_LOGIC; 
          KEY       : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
          LEDR      : OUT STD_LOGIC_VECTOR(9 DOWNTO 0)
		);
END GeneralPurposeRealTimeSoCMatrixMultiplier;

ARCHITECTURE Behavior OF GeneralPurposeRealTimeSoCMatrixMultiplier IS
    SIGNAL Decoded : STD_LOGIC_VECTOR(7 DOWNTO 0);
    SIGNAL ToSend  : STD_LOGIC_VECTOR(7 DOWNTO 0);
    SIGNAL GotUart : STD_LOGIC;
BEGIN
    decoder : entity work.Uart_Decoder generic map (9600, 50_000_000) port map (CLOCK_50, UART_RX, GotUart, Decoded);
    fifo    : entity work.FIFO generic map (128) port map (GotUart, Decoded, KEY(0), NOT KEY(2), ToSend);
    transmitter : entity work.Uart_Transmitter generic map (9600, 50_000_000) port map (CLOCK_50, KEY(1), ToSend, UART_TX);
    LEDR(7 DOWNTO 0) <= ToSend;

END Behavior;