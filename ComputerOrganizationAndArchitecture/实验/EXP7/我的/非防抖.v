`timescale 100ms / 10ms
module EXP7(Select, Clk, Rst, LED, Button);
    input Clk, Rst, Button;
    input [1:0] Select;
    output reg [7:0] LED;

    wire [31:0] Inst_code;
    reg [31:0] PC; // 其实只会用到8位
    wire [31:0] PC_new;
	 wire Rise,Fall;

    Inst a (
    .clka(Button),
    .wea(0),
    .addra(PC[7:2]),
    .dina(0),
    .douta(Inst_code)
    );

    assign PC_new=PC+4;
    always @ (negedge Button)
    begin
        if(Rst == 1)
            PC<=0; // 因为要对同一个reg赋值，不能写到两个always语句块中，否则会报Signal PC[31] in unit EXP7 is connected to multiple drivers
        else
            PC<=PC_new;
    end

    always @ (posedge Button) // Show
    begin
        case(Select)
            0:LED<=Inst_code[7:0];
            1:LED<=Inst_code[15:8];
            2:LED<=Inst_code[23:16];
            3:LED<=Inst_code[31:24];
        endcase
    end
endmodule