module Parser1(input [31:0] InstCode, output [5:0] OP, output [4:0] rs, output [4:0] rt, output [4:0] rd, output [5:0] func);
    // assign OP=InstCode[5:0];
    // assign rs=InstCode[10:6];
    // assign rt=InstCode[15:11];
    // assign rd=InstCode[20:16];
    // assign func=InstCode[31:26];
    assign OP=InstCode[31:26];
    assign rs=InstCode[25:21];
    assign rt=InstCode[20:16];
    assign rd=InstCode[15:11];
    assign func=InstCode[5:0];
endmodule
