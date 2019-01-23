module AddressCreator(Addr, R_Addr, W_Addr);
    input Write_Reg, A_B;
    input [5:0] Addr;
    output [5:0] R_Addr_A, R_Addr_B, W_Addr;

    assign R_Addr=Write_Reg==0?Addr:0;
    assign W_Addr=Write_Reg==1?Addr:0;
endmodule
