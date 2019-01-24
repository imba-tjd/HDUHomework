module DataSelector(Select, W_Data);
    input [1:0] Select;
    output reg [31:0] W_Data;

    always @ (*)
        begin
            case(Select)
                0:W_Data=32'hFFFF_FFFF;
                1:W_Data=32'h1234_5678;
                2:W_Data=32'h7777_7777;
                3:W_Data=32'h8080_8080;
            endcase
        end
endmodule
