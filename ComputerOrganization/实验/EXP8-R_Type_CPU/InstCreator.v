module InstCreator(input Clka, input Reset, output [31:0] InstCode);
    reg [31:0] PC;
    wire [31:0] PC_new;

    ROM_B rom (
    .clka(Clka),
    .wea(1'b0),
    .addra(PC[7:2]),
    .dina(0),
    .douta(InstCode)
    );

    assign PC_new=PC+4;
    always @ (negedge Clka)
    begin
        if(Reset == 1)
            PC<=0; // 因为要对同一个reg赋值，不能写到两个always语句块中，否则会报Signal PC[31] in unit EXP7 is connected to multiple drivers
        else
            PC<=PC_new;
    end
endmodule
