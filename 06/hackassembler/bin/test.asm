@2
M=A
@10
D=A
@20
M=D

@my
M=D
@42
D=A
@derp
M=D

@R0
M=D
@R1
M=D
D=M-1
D;JGT

//This is a comment and should not show in the parser

@62
M=D // This is an inline comment.
@32
M=D
@my
M=D
M+1
D+1