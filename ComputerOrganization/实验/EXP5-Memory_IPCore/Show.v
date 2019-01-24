module Show(R_Data, Select, Write_Reg, LED);
    input [1:0] Select;
    input [31:0] R_Data;
    input Write_Reg;

    output reg [7:0] LED;

    always @ (*)
    begin
        if(Write_Reg==0)
        begin
            case(Select)
                0:LED=R_Data[7:0];
                1:LED=R_Data[15:8];
                2:LED=R_Data[23:16];
                3:LED=R_Data[31:24];
            endcase
        end
        else
        begin
            LED=0;
        end
    end
endmodule
