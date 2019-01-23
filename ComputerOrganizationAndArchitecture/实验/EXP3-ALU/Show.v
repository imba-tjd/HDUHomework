module Show(F_LED_SW, F, OF, ZF, LED);
    input OF, ZF;
    input[2:0] F_LED_SW;
    input[31:0] F;
    output[7:0] LED;
    reg[7:0] LED;

    always @ (*)
    begin
        case(F_LED_SW)
            3'b000:LED<=F[7:0];
            3'b001:LED<=F[15:8];
            3'b010:LED<=F[23:16];
            3'b011:LED<=F[31:24];
            default:begin LED[7]<=ZF; LED[0]<=OF; LED[6:1]<=6'b0; end
        endcase
    end
endmodule