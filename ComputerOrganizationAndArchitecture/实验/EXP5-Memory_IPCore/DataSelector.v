module DataSelector(Select, W_Data);
    input [1:0] Select;
    output reg [31:0] W_Data;

    always @ (*)
        begin
            case(Select)
                0:W_Data=32'h1221_3443;
                1:W_Data=32'h5665_7887;
                2:W_Data=32'h9009_1111;
                3:W_Data=32'h2828_8282;
            endcase
        end
endmodule
