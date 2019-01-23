module ALU(A, B, ALU_OP, F, ZF, OF);
    input[31:0] A, B;
    input[2:0] ALU_OP;
    output ZF, OF;
    output[31:0] F;

    reg[31:0] F;
    reg C32;

    always @ (*)
    begin
        case(ALU_OP)
            3'b000:begin F<=A&B; end
            3'b001:begin F<=A|B; end
            3'b010:begin F<=A^B; end
            3'b011:begin F<=~(A^B); end
            3'b100:begin {C32,F}<=A+B; end
            3'b101:begin {C32,F}<=A-B; end
            3'b110:begin F<=A<B?1:0; end
            3'b111:begin F<=B<<A; end
            default:begin  end
        endcase
    end

	 assign ZF=~(|F);
    assign OF=C32^F[31]^A[31]^B[31];
endmodule