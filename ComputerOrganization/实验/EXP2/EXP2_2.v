module EXP2_2(A, B, C0, F, C8);
    input[7:0] A, B;
    input C0;
    output[7:0] F;
    output C8;
    wire C1, C2, C3, C4, C5, C6, C7;
    wire[7:0] G, P;

    assign G[0] = A[0]&B[0];
    assign G[1] = A[1]&B[1];
    assign G[2] = A[2]&B[2];
    assign G[3] = A[3]&B[3];
    assign G[4] = A[4]&B[4];
    assign G[5] = A[5]&B[5];
    assign G[6] = A[6]&B[6];
    assign G[7] = A[7]&B[7];
    assign P[0] = A[0]|B[0];
    assign P[1] = A[1]|B[1];
    assign P[2] = A[2]|B[2];
    assign P[3] = A[3]|B[3];
    assign P[4] = A[4]|B[4];
    assign P[5] = A[5]|B[5];
    assign P[6] = A[6]|B[6];
    assign P[7] = A[7]|B[7];

    assign C1 = G[0]|(P[0]&C0);
    assign C2 = G[1]|(P[1]&C1);
    assign C3 = G[2]|(P[2]&C2);
    assign C4 = G[3]|(P[3]&C3);
    assign C5 = G[4]|(P[4]&C4);
    assign C6 = G[5]|(P[5]&C5);
    assign C7 = G[6]|(P[6]&C6);
    assign C8 = G[7]|(P[7]&C7);

    Adder A0(A[0],B[0],C0,F[0]),
        A1(A[1],B[1],C1,F[1]),
        A2(A[2],B[2],C2,F[2]),
        A3(A[3],B[3],C3,F[3]),
        A4(A[4],B[4],C4,F[4]),
        A5(A[5],B[5],C5,F[5]),
        A6(A[6],B[6],C6,F[6]),
        A7(A[7],B[7],C7,F[7]);
endmodule

module Adder(A,B,C,F);
	input A,B,C;
	output F;

	assign F=A^B^C;
endmodule
