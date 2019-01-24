module Parser2(input [5:0] OP, input [5:0] func, output reg Write_Reg, output reg [2:0] ALU_OP);
    always @(*)
    begin
        if(OP==0)
        case(func)
            6'b100000:begin ALU_OP=3'b100; Write_Reg=1; end
            6'b100010:begin ALU_OP=3'b101; Write_Reg=1; end
            6'b100100:begin ALU_OP=3'b000; Write_Reg=1; end
            6'b100101:begin ALU_OP=3'b001; Write_Reg=1; end
            6'b100110:begin ALU_OP=3'b010; Write_Reg=1; end
            6'b100111:begin ALU_OP=3'b011; Write_Reg=1; end
            6'b101011:begin ALU_OP=3'b110; Write_Reg=1; end
            6'b000100:begin ALU_OP=3'b111; Write_Reg=1; end
        endcase
    end
endmodule
