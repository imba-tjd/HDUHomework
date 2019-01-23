module EXP2(input[3:0] A, input[3:0] B, input C0, output[3:0] F, output C4);
    wire C1, C2, C3;
    wire[3:0] G, P;

    assign G[0] = A[0]&B[0];
    assign G[1] = A[1]&B[1];
    assign G[2] = A[2]&B[2];
    assign G[3] = A[3]&B[3];
    assign P[0] = A[0]|B[0];
    assign P[1] = A[1]|B[1];
    assign P[2] = A[2]|B[2];
    assign P[3] = A[3]|B[3];

    assign C1 = G[0]|(P[0]&C0);
    assign C2 = G[1]|(P[1]&C1);
    assign C3 = G[2]|(P[2]&C2);
    assign C4 = G[3]|(P[3]&C3);

    Adder A0(A[0],B[0],C0,F[0]),
        A1(A[1],B[1],C1,F[1]),
        A2(A[2],B[2],C2,F[2]),
        A3(A[3],B[3],C3,F[3]);
endmodule

module Adder(A,B,C,F);
	input A,B,C;
	output F;

	assign F=A^B^C;
endmodule
