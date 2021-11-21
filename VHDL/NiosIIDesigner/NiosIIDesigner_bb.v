
module NiosIIDesigner (
	clk_clk,
	reset_reset_n,
	main_memory_wire_addr,
	main_memory_wire_ba,
	main_memory_wire_cas_n,
	main_memory_wire_cke,
	main_memory_wire_cs_n,
	main_memory_wire_dq,
	main_memory_wire_dqm,
	main_memory_wire_ras_n,
	main_memory_wire_we_n,
	pio_0_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[11:0]	main_memory_wire_addr;
	output	[1:0]	main_memory_wire_ba;
	output		main_memory_wire_cas_n;
	output		main_memory_wire_cke;
	output		main_memory_wire_cs_n;
	inout	[31:0]	main_memory_wire_dq;
	output	[3:0]	main_memory_wire_dqm;
	output		main_memory_wire_ras_n;
	output		main_memory_wire_we_n;
	output	[31:0]	pio_0_external_connection_export;
endmodule
