#ifndef ENUMS_H
#define ENUMS_H


typedef enum CommandType_t {
    INVALID_COMMANDTYPE = 0,
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
} CommandType;


typedef enum Instruction_t {
    INVALID_INSTRUCTION = 0,
    ADD,
    SUB,
    NEG,
    EQ,
    GT,
    LT,
    AND,
    OR,
    NOT,
    PUSH,
    POP,
    FUNCTION,
    IF,
    RETURN,
    LABEL,
    CALL,
} Instruction;

typedef enum MemoryAccess_t {
    INVALID_MEMORYACCESS = 0,
    ARGUMENT,
    LOCAL,
    STATIC,
    CONSTANT,
    THIS,
    THAT,
    POINTER,
    TEMP,
} MemoryAccess;

#endif