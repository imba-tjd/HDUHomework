// https://blog.csdn.net/AeroYoung/article/details/78809906
`timescale 10ms / 1ms
module EXP7(Select, Clk, Rst, LED, Button);
    input Clk, Rst, Button;
    input [1:0] Select;
    output reg [7:0] LED;

    wire [31:0] Inst_code;
    reg [31:0] PC; // 其实只会用到8位
    wire [31:0] PC_new;
    wire Button_out;

    Inst a (
    .clka(Clk),
    .wea(0),
    .addra(PC[7:2]),
    .dina(0),
    .douta(Inst_code)
    );

    KeyDebounced b(Button,Button_out,Clk,Rst);

    assign PC_new=PC+4;
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

module KeyDebounced(keyVal,key,clock,reset);

parameter KeyCnt = 8;//默认8个按键
parameter TIME   = 20'd999_999;//50Mhz 0.02us 20ms 10^6-1

input clock,reset;
input  [7:0] key;
output [7:0] keyVal;//输出稳定的键值

reg [19:0]       time_cnt;
reg [19:0]       time_cnt_next;
reg [KeyCnt-1:0] key_reg;
reg [KeyCnt-1:0] key_reg_next;

//时序电路 给定时器赋值
always @(posedge clock,negedge reset)
  begin
    if(!reset)
      time_cnt <= 20'h0;
    else
      time_cnt <= time_cnt_next;
  end

//组合电路 实现定时器
always @(*)
  begin
    if(time_cnt == TIME)
      time_cnt_next = 20'h0;
    else
      time_cnt_next =time_cnt + 20'h1;
  end

//时序电路 给按键寄存器赋值
always @(posedge clock,negedge reset)
  begin
    if(!reset)
      key_reg <= 8'h0;
    else
      key_reg <= key_reg_next;
  end

//组合电路 每隔一个定时器周期接受依次按键的值
always @(*)
  begin
    if(time_cnt == TIME)
      key_reg_next = key;
    else
      key_reg_next <= key_reg;
  end

assign keyVal = key_reg & (~key_reg_next);

endmodule