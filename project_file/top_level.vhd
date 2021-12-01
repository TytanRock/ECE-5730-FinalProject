-- MATRIX_CALCULATOR.vhd

-- Generated using ACDS version 18.1 625

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity MATRIX_CALCULATOR is
	port (
		CLOCK_50                                 : in  std_logic                    := '0';             --                              clk.clk
		UART_RX                                  : in std_logic;
        UART_TX                                  : out std_logic;
        LEDR                                     : out std_logic_vector(9 downto 0)
	);
end entity MATRIX_CALCULATOR;

architecture Behavior of MATRIX_CALCULATOR is
    signal next_write : std_logic_vector(7 downto 0);
    signal toWrite    : std_logic_vector(7 downto 0);
    signal next_read  : std_logic_vector(7 downto 0);
    signal toRead     : std_logic_vector(7 downto 0);
    
    signal gotUart    : std_logic;
    signal decodedRead: std_logic_vector(7 downto 0);
    
    
    component MATRIX_CALCULATOR_sys is
        port (
            clk_clk                                 : in  std_logic                    := '0';             --                              clk.clk
            nextval_external_connection_export      : out std_logic_vector(7 downto 0);                    --      nextval_external_connection.export
            nextwriteval_external_connection_export : out std_logic_vector(7 downto 0);                    -- nextwriteval_external_connection.export
            readval_external_connection_export      : in  std_logic_vector(7 downto 0) := (others => '0'); --      readval_external_connection.export
            writeval_external_connection_export     : out std_logic_vector(7 downto 0)                     --     writeval_external_connection.export
        );
    end component;
    
begin
    
    calculator : MATRIX_CALCULATOR_sys port map (CLOCK_50, next_read, next_write, toRead, toWrite);
    
    uart_decoder : entity work.Uart_Decoder port map (CLOCK_50, UART_RX, gotUart, decodedRead);
    
    read_fifo : entity work.FIFO port map (gotUart, decodedRead, next_read(0), toRead);
    
    LEDR(7 downto 0) <= toRead;
    
end Behavior;