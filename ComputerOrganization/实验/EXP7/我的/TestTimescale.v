`timescale 100ms / 10ms
module EXP7(Select, Clk, Rst, LED, Button);
    input Clk, Rst, Button;
    input [1:0] Select;
    output reg [7:0] LED;

    always@(posedge Clk)
	 begin
	 #10
	     LED<=8'b11111111;
	 #10
			LED<=0;
	 end
endmodule
