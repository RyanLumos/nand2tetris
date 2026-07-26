// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(LOOP)
    @SCREEN
    D=A
    @addr
    M=D

    @KBD
    D=M
    @SET_BLACK
    D;JNE

    @color
    M=0
    @DRAW
    0;JMP

(SET_BLACK)
    @color
    M=-1

(DRAW)
    @addr
    D=M
    @KBD
    D=D-A
    @LOOP
    D;JEQ

    @color
    D=M
    @addr
    A=M
    M=D

    @addr
    M=M+1

    @DRAW
    0;JMP

