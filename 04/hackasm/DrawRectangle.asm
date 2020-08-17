//Screen RAM region begins at: 16384 
//Registers used:

//Rect height
@160
D=A
@R0
M=D
@n
M=D

@i
M=0

@SCREEN
D=A
@address
M=D

@16
D=A
@address
M=M+D

(LOOP)
	@i
	D=M
	@n
	D=D-M
	@END
	D;JGT
	
	@address
	A=M
	M=-1
	
	@i
	M=M+1
	@32
	D=A
	@address
	M=M+D
	@LOOP
	0;JMP

@END
(END)
0;JMP