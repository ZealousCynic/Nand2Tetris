//Toggle the screen between white and black.

(INIT)

@KBD
D=A
@R1
M=D

@0
D=A
@R2
M=D

@24574
D=A
@R0
M=D
@SCREEN
D=A
@address
M=D

(LOOP)
	@R0
	D=M
	@R2
	D=D-M
	@INIT
	D;JLE
	
	//Read keyboard state: Is it zero?
	@KBD
	D=M
	@SETTOBLACK
	D;JEQ
	@SETTOWHITE
	0;JMP
	
	(RETURNINLOOP)
	//Increment i
	@R2
	M=M+1
	
	//Increment address
	@address
	M=M+1
	@LOOP
	0;JMP


	(SETTOBLACK)
	//Set 16 bits on address to 1
	@address
	A=M
	M=-1
	@RETURNINLOOP
	0;JMP
	
	(SETTOWHITE)
	//Set 16 bits on address to 0
	@address
	A=M
	M=0
	@RETURNINLOOP
	0;JMP

@END
(END)
0;JMP