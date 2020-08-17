//
//R15: Number to multiply; x
//R14: Times to multiply; y
//R13: Temporary storage of result
//R0: "Return register"
//

//Number to multiply: x

@6
D=A
@R15
M=D

// Multiplier: y
@5
D=A
@R14
M=D

//Loop while adding x to x
(MULTIPLY)
@15
D=M
@13
M=D+M

//Decrement multiplier. Is it still greater than zero?
@14
M=M-1
D=M
@MULTIPLY
D;JGT

//Epilogue, put result in R0, zero out registers
@R13
D=M
@R0
M=D
@R15
M=0
@R14
M=0
@R13
M=0
//Infinite loop
@END
(END)
0;JMP