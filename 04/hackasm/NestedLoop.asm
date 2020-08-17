//
//Since function calls (or a stack) haven't been implemented, 
//this stub is limited to using jumps to reach code. 
//Neither is external files supported, so all code will be written in a single file.
//
//<--------------	Register Usage	--------------->
//
//C = Clobbered
//N = Values preserved
//
//Registers used: R0, R1, R2, R3, R5, R13, R14, R15
//
//
//
//###	Multiplier: ###
//C R15: X
//C R14: Y
//
//N R0: Result
//
//###	Comparison for loop ###
//
//R5 = 10
//
//###	Loop1		###
//
//N R1: i
//
//###	Loop2		###
//
//N R2: j
//

//
//<--------------	Code prologue		--------------->
//

//Zero out all registers to be used in this stub

@0
D=A
@R0
M=D
@R1
M=D
@R2
M=D
@R5
M=D
@R14
M=D
@R15
M=D

//
//<--------------	Loop logic		--------------->
//


//Set comparison for loops
@10
D=A
@R5
M=D

//Since outer loop is only run once, reinitialization of i is not needed.
(OuterLoop)

	//OuterLoop body

	//Set j to 0
	@0
	D=A
	@R2
	M=D
	
	(InnerLoop)

		//InnerLoop body
		@R1
		D=A
		@R15
		M=D
		@R2
		D=A
		@R14
		M=D
		
		@Multiplier
		0;JMP
		
		(ReturnMultiplier)
		
		@R0
		D=M
		@R3
		M=M+D		
		
		//InnerLoop epilogue
		@R5
		D=M
		@R2
		M=M+1
		D=D-M	
		@InnerLoop
		D;JGT
	
	////OuterLoop epilogue
	@R5
	D=M
	@R1
	M=M+1
	D=D-M	
	@OuterLoop
	D;JGT
	
	@R3
	D=M
	@R0
	M=D
	
	@END
	0;JMP
	
//
//<--------------	Multiplier		--------------->
//

(Multiplier)
	
//R15: Number to multiply: x

//@6
//D=A
//@R15
//M=D

//R14: Multiplier: y
//@5
//D=A
//@R14
//M=D

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
	
@ReturnMultiplier
0;JMP	
	
	
@END
(END)
0;JMP

