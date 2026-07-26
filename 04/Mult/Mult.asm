// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//Method 2: Bitwise multiplication

// R2 = 0, mask = 1, shifted_R0 = R0
@2
M=0
@mask
M=1
@0
D=M
@shifted_R0
M=D

// n = 16
@16
D=A
@n
M=D

(LOOP)
    // if (n == 0) END
    @n
    D=M
    @END
    D;JEQ

    // if (mask & R1 != 0) R2 += shifted_R0
    @1
    D=M
    @mask
    D=D&M
    @SHIFT_PREP
    D;JEQ
    @shifted_R0
    D=M
    @2
    M=D+M

// shifted_R0 *= 2, mask *= 2, n -= 1
(SHIFT_PREP)
    @shifted_R0
    D=M
    M=D+M
    @mask
    D=M
    M=D+M
    @n
    M=M-1
    
    @LOOP
    0;JMP

(END)
0;JMP