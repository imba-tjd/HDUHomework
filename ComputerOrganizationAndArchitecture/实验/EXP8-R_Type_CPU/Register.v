module Register(R_Addr_A, R_Addr_B, W_Addr, W_Data, Write_Reg, Clka, Reset,
    R_Data_A, R_Data_B);

    input Write_Reg, Clka, Reset;
    input [4:0] R_Addr_A, R_Addr_B, W_Addr;
    input [31:0] W_Data;
    output [31:0] R_Data_A, R_Data_B;

    reg[31:0] REG_FILES[0:31];

    assign R_Data_A=REG_FILES[R_Addr_A];
    assign R_Data_B=REG_FILES[R_Addr_B];

    always @ (negedge Clka)
    begin
        if(Reset) // 书本如此
        begin:reset // Declarations not allowed in unnamed block
            integer i;
            for(i = 0;i<31;i=i+1)
            begin
                REG_FILES[i]<=0;
            end
        end
        else
        begin
            if(Write_Reg)
            begin
                REG_FILES[W_Addr]<=W_Data;
            end
        end
    end
endmodule
