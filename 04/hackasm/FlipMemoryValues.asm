//Description: Switches the values of R0 and R10

@10
M=1
M=M+1

(START)
@R0
D=M
@temp
M=D
@10
D=M
@R0
M=D
@temp
D=M
@10
M=D

@START
0;JMP