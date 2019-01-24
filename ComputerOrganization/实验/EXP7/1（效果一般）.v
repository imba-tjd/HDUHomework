`timescale 10ms / 1ms
module EXP7(Select, Clk, Rst, LED, Button);
    input Clk, Rst, Button;
    input [1:0] Select;
    output reg [7:0] LED;

    wire [31:0] Inst_code;
    reg [31:0] PC; // 其实只会用到8位
    wire [31:0] PC_new;
	 wire Rise,Fall;

    Inst a (
    .clka(Rise),
    .wea(0),
    .addra(PC[7:2]),
    .dina(0),
    .douta(Inst_code)
    );

	EdgeDetect b(Clk,Rst,Button,Rise,Fall);

    assign PC_new=PC+4;
    always @ (posedge Rise)
    begin
        if(Rst == 1)
            PC<=0; // 因为要对同一个reg赋值，不能写到两个always语句块中，否则会报Signal PC[31] in unit EXP7 is connected to multiple drivers
        else
            PC<=PC_new;
    end

    always @ (posedge Fall) // Show
    begin
        case(Select)
            0:LED<=Inst_code[7:0];
            1:LED<=Inst_code[15:8];
            2:LED<=Inst_code[23:16];
            3:LED<=Inst_code[31:24];
        endcase
    end
endmodule

// https://www.jiaheu.com/topic/116795.html，改
module EdgeDetect(
input clk,
input rst,
input button,
output reg rise,
output reg fall
);
reg[7:0] samp;//移位寄存器采集button键值
//移位寄存器采集button信息
always@(posedge clk)
begin
if(rst)
samp<=8'b0000_0000;
else
samp<={samp[6:0],button};
end
//产生上升沿信息
always@(posedge clk)
begin
if(rst)
rise<=1'b0;
else if(samp==8'b1000_0000)
rise<=1'b1;
else
rise<=1'b0;
end
//产生下降沿信息
always@(posedge clk)
begin
if(rst)
fall<=1'b0;
else if(samp==8'b0111_1111)
fall<=1'b1;
else
fall<=1'b0;
end
endmodule