module EXP4(Addr, Write_Reg, Select, Clk, Reset, A_B, LED);
    input Write_Reg, Clk, Reset, A_B;
    input [1:0] Select;
    input [4:0] Addr;
    output [7:0] LED;

    wire [31:0] W_Data;
    wire [4:0] R_Addr_A, R_Addr_B, W_Addr;
    wire [31:0] R_Data_A, R_Data_B;

    DataSelector a(Select, W_Data);
    AddressCreator b(Addr, Write_Reg, A_B, R_Addr_A, R_Addr_B, W_Addr);
    Register c(R_Addr_A, R_Addr_B, W_Addr, W_Data, Write_Reg, Clk, Reset, R_Data_A, R_Data_B);
    Show d(R_Data_A, R_Data_B, A_B, Select, LED);
endmodule
