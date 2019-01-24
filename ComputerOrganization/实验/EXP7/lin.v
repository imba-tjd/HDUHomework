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
    .clka(Rise),
    .wea(0),
    .addra(PC[7:2]),
    .dina(0),
    .douta(Inst_code)
    );

	debounce b(Clk,Button,Button_out);

    assign PC_new=PC+4;
    always @ (Button_out)
    begin
    if(Button_out==0)
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

module debounce (
    input clk_100MHz,
    input BTN,
    output reg BTN_Out
    );

	reg BTN1,BTN2;
	wire BTN_Down;
	reg [21:0] cnt;
	reg BTN_20ms_1,BTN_20ms_2;
	wire BTN_Up;

	always @(posedge clk_100MHz)
	begin
		BTN1 <= BTN;
		BTN2 <= BTN1;
	end
	assign BTN_Down = (~BTN2)&& BTN1 ; //从0到1的跳变

	always @(posedge clk_100MHz)
	begin
		if (BTN_Down)
			begin
				cnt <= 22'b0;
				BTN_Out <= 1'b1;
			end
		else	cnt <= cnt+1'b1;
		if (cnt==22'h20000) BTN_20ms_1 <= BTN;
		BTN_20ms_2 <= BTN_20ms_1;
		if (BTN_Up) BTN_Out <= 1'b0;
	end

	assign BTN_Up = BTN_20ms_2 && (~BTN_20ms_1);//从1到0

endmodule
