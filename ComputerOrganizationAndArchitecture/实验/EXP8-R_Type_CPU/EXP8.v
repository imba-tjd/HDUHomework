module EXP8(Select, Clk, Rst, LED, Button);
    input Clk, Rst, Button;
    input [2:0] Select; // 选择ALU运算结果字节或者标志OF、ZF
    output [7:0] LED;

    wire Button_out;
    Debouncing debouncing(Clk, Rst, Button, Button_out);
    //assign Button_out=Button;

    wire [31:0] InstCode;
    InstCreator instCreator(Button_out, Rst, InstCode);

    wire [5:0] OP, func;
    wire [4:0] rs, rt, rd;
    Parser1 parser1(InstCode, OP, rs, rt, rd, func);

    wire Write_Reg;
    wire [2:0] ALU_OP;
    Parser2 parser2(OP, func, Write_Reg, ALU_OP);

    wire [31:0] R_Data_A, R_Data_B, W_Data;
    Register register(rs, rt, rd, W_Data, Write_Reg, Button_out, Rst, R_Data_A, R_Data_B);

    wire ZF, OF;
    ALU alu(R_Data_A, R_Data_B, ALU_OP, W_Data, ZF, OF);

    Show show(Select, W_Data, ZF, OF, LED);
endmodule
