
module MATRIX_CALCULATOR (
	clk_clk,
	readval_external_connection_export,
	nextval_external_connection_export,
	writeval_external_connection_export,
	nextwriteval_external_connection_export);	

	input		clk_clk;
	input	[7:0]	readval_external_connection_export;
	output	[7:0]	nextval_external_connection_export;
	output	[7:0]	writeval_external_connection_export;
	output	[7:0]	nextwriteval_external_connection_export;
endmodule
