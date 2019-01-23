module Show(R_Data_A, R_Data_B, A_B, Select,
    LED);

    input A_B;
    input [1:0] Select;
    input [31:0] R_Data_A, R_Data_B;

    output reg [7:0] LED;

    always @ (*)
    begin
        if(A_B == 0)
        begin
            case(Select)
                0:LED=R_Data_A[7:0];
                1:LED=R_Data_A[15:8];
                2:LED=R_Data_A[23:16];
                3:LED=R_Data_A[31:24];
            endcase
        end
        else
        begin
            case(Select)
                0:LED=R_Data_B[7:0];
                1:LED=R_Data_B[15:8];
                2:LED=R_Data_B[23:16];
                3:LED=R_Data_B[31:24];
            endcase
        end
    end
endmodule
