module EXP5(Addr, Write_Reg, Select, Clk, LED);
    input Write_Reg, Clk;
    input [1:0] Select;
    input [5:0] Addr;
    output [7:0] LED;

    wire [31:0] W_Data, R_Data;
    // wire [5:0] R_Addr, W_Addr;

    DataSelector a(Select, W_Data);
    // AddressCreator b(Addr, R_Addr, W_Addr);
    RAM_B c (
        .clka(Clk),
        .wea(Write_Reg),
        .addra(Addr[5:0]),
        .dina(W_Data),
        .douta(R_Data)
	);
    Show d(R_Data, Select, Write_Reg, LED);
endmodule
