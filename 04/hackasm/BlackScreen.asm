//Color the entire screen black

@0
D=A
@i
M=D


@24575
D=A
@R0
M=D
@SCREEN
D=A
@address
M=D
(LOOP)
	@i
	D=M
	@R0
	D=D-M
	@END
	D;JGT
	
	//Set 16 bits on addres to 1
	@address
	A=M
	M=-1
	
	//Increment i
	@i
	M=M+1
	
	//Increment address
	@address
	M=M+1
	@LOOP
	0;JMP

@END
(END)
0;JMP