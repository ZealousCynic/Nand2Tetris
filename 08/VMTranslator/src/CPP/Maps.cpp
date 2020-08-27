#include "Maps.h"

// The ASM parser may throw a hissy fits over no CR's. Will adjust in future.

#pragma region VMTOASMINSTRUCTIONMAP

const std::unordered_map<Instruction, std::string> VMToASMInstructionMap = {
    {ADD, 
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "A=A-1\r\n"
    "M=D+M\r\n"},

    {SUB,
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "A=A-1\r\n"
    "D=M\r\n"
    "A=A+1\r\n"
    "D=D-M\r\n"
    "M=D\r\n"

    },

    {NEG, 
    
    "@SP\r\n"
    "A=M-1\r\n" 
    "D=M\r\n"
    "@LESSTHAN%i\r\n"
    "D;JLT\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "@CONTINUE%i\r\n"
    "0;JMP\r\n"
    "(LESSTHAN%i)\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=!M\r\n"
    "M=M+1\r\n"
    "(CONTINUE%i)\r\n"
    
    },

    {EQ, 
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "A=A-1\r\n"
    "D=D-M\r\n"
    "@NOTEQUAL%i\r\n"
    "D;JNE\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=-1\r\n"
    "@CONTINUE%i\r\n"
    "0;JMP\r\n"
    "(NOTEQUAL%i)\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=0\r\n"
    "(CONTINUE%i)\r\n"
    },
    
    {GT, 

    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "A=A-1\r\n"
    "D=D-M\r\n"
    "@GREATERTHAN%i\r\n"
    "D;JGE\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=-1\r\n"
    "@CONTINUE%i\r\n"
    "0;JMP\r\n"
    "(GREATERTHAN%i)\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=0\r\n"
    "(CONTINUE%i)\r\n"
    },
    
    {LT, 
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "A=A-1\r\n"
    "D=D-M\r\n"
    "@LESSTHAN%i\r\n"
    "D;JLE\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=-1\r\n"
    "@CONTINUE%i\r\n"
    "0;JMP\r\n"
    "(LESTTHAN%i)\r\n"
    "@SP\r\n"
    "A=M-1\r\n"
    "M=0\r\n"
    "(CONTINUE%i)\r\n"
    },
    
    {AND, 
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "A=A-1\r\n"
    "M=D&M\r\n"    
    },
    
    {OR, 
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "A=A-1\r\n"
    "M=D|M\r\n"
    },
    
    {NOT, 
    
    "@SP\r\n"
    "A=M-1\r\n"
    "M=!M\r\n"
    },

    {IF,
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@%s\r\n"
    "D;JNE\r\n"
    }
};

#pragma endregion

#pragma region PUSHMAP

const std::unordered_map<MemoryAccess, std::string> PushMap = {

    {ARGUMENT,
    
    "D=A\r\n"
    "@ARG\r\n"
    "A=D+M\r\n"
    "D=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"    
    },
    {LOCAL,
    
    "D=A\r\n"
    "@LCL\r\n"
    "A=D+M\r\n"
    "D=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    },

    {STATIC,
    
    "D=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    },

    {CONSTANT, 
    
    "D=A\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    },

    {THIS,
    
    "D=A\r\n"
    "@THIS\r\n"
    "A=D+M\r\n"
    "A=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    },

    {THAT,
    
    "D=A\r\n"
    "@THAT\r\n"
    "A=D+M\r\n"
    "D=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    },

    {POINTER,
    
    "D=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    },

    {TEMP,

    "@SP\r\n"
    "D=M\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    }
};

#pragma endregion

#pragma region POPMAP

const std::unordered_map<MemoryAccess, std::string> PopMap = {
    
    {ARGUMENT,
    
    "D=A\r\n"
    "@ARG\r\n"
    "D=D+M\r\n"
    "@R13\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@R13\r\n"
    "A=M\r\n"
    "M=D\r\n"

    },

    {LOCAL,
    
    "D=A\r\n"
    "@LCL\r\n"
    "D=D+M\r\n"
    "@R13\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@R13\r\n"
    "A=M\r\n"
    "M=D\r\n"
    
    },

    {STATIC,
    
    "D=A\r\n"
    "@R13\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@R13\r\n"
    "A=M\r\n"
    "M=D\r\n"
    
    },

    {CONSTANT,
    
    "D=A\r\n"
    "@SP\r\n"
    "A=M\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "M=M+1\r\n"
    
    },

    {THIS,
    
    "D=A\r\n"
    "@THIS\r\n"
    "D=D+M\r\n"
    "@R13\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@R13\r\n"
    "A=M\r\n"
    "M=D\r\n"
    
    },
    
    {THAT,
    
    "D=A\r\n"
    "@THAT\r\n"
    "D=D+M\r\n"
    "@R13\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@R13\r\n"
    "A=M\r\n"
    "M=D\r\n"
    
    },

    {POINTER,
    
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    
    },

    {TEMP,
    
    "D=A\r\n"
    "@R13\r\n"
    "M=D\r\n"
    "@SP\r\n"
    "AM=M-1\r\n"
    "D=M\r\n"
    "@R13\r\n"
    "A=M\r\n"
    "M=D\r\n"
    
    },
};

#pragma endregion

#pragma region INSTRUCTIONMAP

const std::unordered_map<std::string, Instruction> InstructionMap = {
    {"ADD", ADD},
    {"SUB", SUB},
    {"NEG", NEG},
    {"EQ", EQ},
    {"GT", GT},
    {"LT", LT},
    {"PUSH",PUSH},
    {"POP",POP},
    {"AND", AND},
    {"OR", OR},
    {"NOT", NOT},
    {"FUNCTION", FUNCTION},
    {"IF-GOTO", IF},
    {"RETURN", RETURN},
    {"LABEL", LABEL},
    {"CALL", CALL},
};

#pragma endregion

#pragma region MEMORYACCESSMAP

const std::unordered_map<std::string, MemoryAccess> MemoryAccessMap = {
    {"ARGUMENT", ARGUMENT},
    {"LOCAL",LOCAL},
    {"STATIC",STATIC},
    {"CONSTANT",CONSTANT},
    {"THIS",THIS},
    {"THAT",THAT},
    {"POINTER",POINTER},
    {"TEMP",TEMP},
};

#pragma endregion

#pragma region ASMPROLOGUE

const std::string prologue = 
// SP
"@256\r\n"
"D=A\r\n"
"@SP\r\n"
"M=D\r\n"

// LCL
"@300\r\n"
"D=A\r\n"
"@LCL\r\n"
"M=D\r\n"

// ARG
"@400\r\n"
"D=A\r\n"
"@ARG\r\n"
"M=D\r\n"

// THIS
"@3000\r\n"
"D=A\r\n"
"@THIS\r\n"
"M=D\r\n"

// THAT
"@3010\r\n"
"D=A\r\n"
"@THAT\r\n";

#pragma endregion
