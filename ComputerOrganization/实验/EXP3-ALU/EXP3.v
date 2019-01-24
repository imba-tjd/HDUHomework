module EXP3(AB_SW, ALU_OP, F_LED_SW, LED);
    input[2:0] AB_SW, ALU_OP, F_LED_SW;
    output[7:0] LED;

    reg[31:0] A, B, F;
    reg[7:0] LED;
    reg ZF, OF;

    Assign a(AB_SW, A, B);
    ALU b(A, B, ALU_OP, F, ZF, OF);
    Show c(F_LED_SW, F, OF, ZF, LED);
endmodule
