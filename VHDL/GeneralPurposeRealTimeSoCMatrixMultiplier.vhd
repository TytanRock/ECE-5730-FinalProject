LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY GeneralPurposeRealTimeSoCMatrixMultiplier IS
	PORT( CLOCK_50  : IN STD_LOGIC;
          SW        : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
			 UART_RX : IN STD_LOGIC; 
			 UART_TX : OUT STD_LOGIC; 
          LEDR      : OUT STD_LOGIC_VECTOR(9 DOWNTO 0)
		);
END GeneralPurposeRealTimeSoCMatrixMultiplier;

ARCHITECTURE Behavior OF GeneralPurposeRealTimeSoCMatrixMultiplier IS

BEGIN

	UART_TX <= UART_RX;
    
    decoder : entity work.Uart_Decoder port map (CLOCK_50, UART_RX, LEDR(9), LEDR(7 DOWNTO 0));

END Behavior;