	//Description: Increaments number stored in R15 until its value is greater than
	//the number in R14
	
	//TODO: Add R16 as BASE NUMBER
	
	//R16: TODO 
	//R15: Number to be incremented
	//R14: Stop when number is greater than
	
	
	@3
	D=A
	@R15
	M=D
	@30
	D=A	
	@R13	
(COUNT)
	@R14
	D=M
	D=D+M[15]
	M[14]=D

	
	@R13
	M=D	
	D=D-M[14]
	@COUNT
	D;JGT

@END
(END)
0;JMP