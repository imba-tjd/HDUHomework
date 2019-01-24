//http://blog.sina.com.cn/s/blog_72c14a3d010150m4.html
`timescale 10ms / 1ms
module EXP7(Select, Clk, Rst, LED, Button);
    input Clk, Rst, Button;
    input [1:0] Select;
    output reg [7:0] LED;

    wire [31:0] Inst_code;
    reg [31:0] PC; // 其实只会用到8位
    wire [31:0] PC_new;

    Inst a (
    .clka(Clk),
    .wea(0),
    .addra(PC[7:2]),
    .dina(0),
    .douta(Inst_code)
    );

    RMV_BJ b(Clk,Rst,Button,Button_out);

    assign PC_new=PC+4;

    // always @ (posedge AntiShake[0]) // Button的下降沿
    always @ (negedge Button_out)
    begin
        if(Rst == 1)
            PC<=0; // 因为要对同一个reg赋值，不能写到两个always语句块中，否则会报Signal PC[31] in unit EXP7 is connected to multiple drivers
        else
            PC<=PC_new;
    end

    always @ (*) // Show
    begin
        case(Select)
            0:LED<=Inst_code[7:0];
            1:LED<=Inst_code[15:8];
            2:LED<=Inst_code[23:16];
            3:LED<=Inst_code[31:24];
        endcase
    end
endmodule

module RMV_BJ (
BJ_CLK, //采集时钟，40Hz
RESET, //系统复位信号
BUTTON_IN, //按键输入信号
BUTTON_OUT //消抖后的输出信号
);
input B_CLK;
input RESET;
input BUTTON_IN;
output BUTTON_OUT;
reg BUTTON_IN_Q, BUTTON_IN_2Q, BUTTON_IN_3Q;
always @(posedge BJ_CLK or negedge RESET)
begin
if(~RESET)
begin
BUTTON_IN_Q <= 1'b1;
BUTTON_IN_2Q <= 1'b1;
BUTTON_IN_3Q <= 1'b1;
end
else
begin
BUTTON_IN_Q <= BUTTON_IN;
BUTTON_IN_2Q <= BUTTON_IN_Q;
BUTTON_IN_3Q <= BUTTON_IN_2Q;
end
end
wire BUTTON_OUT = BUTTON_IN_2Q | BUTTON_IN_3Q;
endmodule