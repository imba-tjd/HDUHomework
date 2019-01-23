module AddressCreator(Addr, Write_Reg, A_B,
    R_Addr_A, R_Addr_B, W_Addr);

    input Write_Reg, A_B;
    input [4:0] Addr;
    output [4:0] R_Addr_A, R_Addr_B, W_Addr;

    assign R_Addr_A=Write_Reg==0&&A_B==0?Addr:0;
    assign R_Addr_B=Write_Reg==0&&A_B==1?Addr:0;
    assign W_Addr=Write_Reg==1?Addr:0;
endmodule
