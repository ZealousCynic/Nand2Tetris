#include "Parser.h"

Parser::Parser(std::ifstream &fRef)
    : input(fRef)
{
}

void Parser::scan()
{

    toWrite = "";
    lineNumber = 0;

    std::string toOpen = chooseFile();

    input.open(toOpen, std::ios::in);

    if (input.is_open())
    {
        addAsmPrologue();

        while (!input.eof())
        {

            std::string current = advance();

            current = cleanInput(current);
            char delim = ' ';

            std::vector<std::string> instructionParts = sh.split(current, delim);

            std::string splitInstruction = instructionParts[0];
            std::cout << splitInstruction << '\n';

            Instruction currentInstruction = getCurrentInstruction(instructionParts[0]);

            std::string toReplace;

            switch (currentInstruction)
            {
            case ADD:
                toWrite.append(getAssemblyInstruction(currentInstruction));
                break;
            case SUB:
                toWrite.append(getAssemblyInstruction(currentInstruction));
                break;
            case AND:
                toWrite.append(getAssemblyInstruction(currentInstruction));
                break;
            case OR:
                toWrite.append(getAssemblyInstruction(currentInstruction));
                break;
            case NOT:
                toWrite.append(getAssemblyInstruction(currentInstruction));
                break;
            case PUSH:
                push(instructionParts);
                break;
            case POP:
                pop(instructionParts);
                break;
            // The same logic is used in all case. To save on LoC, just fall through.
            case NEG:
            case EQ:
            case GT:
            case LT:                        
                toReplace = getAssemblyInstruction(currentInstruction);

                for(int i = 0; i < toReplace.length(); i++)
                {
                    if(toReplace[i] == '%' && toReplace[i + 1] == 'i') {
                        toReplace.replace(i, 2, std::to_string(lineNumber));
                    }
                }
                toWrite.append(toReplace);
                break;
            case INVALID_INSTRUCTION:
                break;
            default:
                std::cout << "Somthing went wrong during instruction translation. Line: " << lineNumber << '\n';
                break;
            }

            lineNumber++;
        }

        input.close();

        addAsmEpilogue();

        std::string toPrintName = sh.eraseFromCharacter(toOpen, '.') += ".asm";
        print(toPrintName, toWrite);
    }
    else
    {
        std::cout << "Could not open the file.";
        toWrite = "ERROR";
        print("ERROR.txt", toWrite);
    }
}

std::string Parser::advance()
{
    std::string toReturn;

    std::getline(input, toReturn);

    return toReturn;
}

std::string Parser::cleanInput(std::string toClean)
{

    toClean = sh.removeCharacterAtIndex(toClean, '1', 0);
    toClean = sh.removeComments(toClean, '/');

    // If there's only a CR on the line, return an empty string.
    if (toClean[0] == '\r' || toClean.empty())
        return {};

    toClean = sh.removeCharacter(toClean, '\r');
    toClean = sh.convertToUpper(toClean);

    return toClean;
}

Instruction Parser::getCurrentInstruction(std::string toCompare)
{

    auto it = InstructionMap.find(toCompare);
    if (it != InstructionMap.end())
        return it->second;
    return INVALID_INSTRUCTION;
}

MemoryAccess Parser::getCurrentMemoryAccess(std::string toCompare)
{

    auto it = MemoryAccessMap.find(toCompare);
    if (it != MemoryAccessMap.end())
        return it->second;
    return INVALID_MEMORYACCESS;
}

std::string Parser::getAssemblyInstruction(Instruction toGet)
{
    auto it = VMToASMInstructionMap.find(toGet);
    if (it != VMToASMInstructionMap.end())
        return it->second;
    return "";
}

std::string Parser::getPushMemoryInstruction(MemoryAccess toGet)
{
    auto it = PushMap.find(toGet);
    if (it != PushMap.end())
        return it->second;
    return "";
}

std::string Parser::getPopMemoryInstruction(MemoryAccess toGet)
{
    auto it = PopMap.find(toGet);
    if (it != PopMap.end())
        return it->second;
    return "";
}

void Parser::print(std::string filename, std::string toPrint)
{

    std::filebuf fb;
    fb.open(filename, std::ios::out);
    if (fb.is_open())
    {

        std::ostream os(&fb);
        os << toPrint;
        fb.close();
    }
    else
    {
        std::cout << "Could not open file for writing.";
    }
}

void Parser::push(std::vector<std::string> parts) {
    
    MemoryAccess memoryAccess = getCurrentMemoryAccess(parts[1]);
    int parsed;
    std::string intContainer;

    switch(memoryAccess) {

        case ARGUMENT:
            toWrite.append("@" + parts[2]).append("\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));
            break;
        case LOCAL:
            toWrite.append("@" + parts[2]).append("\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));
            break;
        case STATIC:
            parsed = std::stoi(parts[2]);

            if(parsed > 240)
            {
                std::cout << "Static cannot be over 240. Current line: " << lineNumber << '\n';
                exit(-2);
            }

            parsed += 16;

            toWrite.append("@" + std::to_string(parsed) + "\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));
            break;
        case CONSTANT:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));
            break;
        case THIS:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));
            break;
        case THAT:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));
            break;
        case POINTER:
            parsed = std::stoi(parts[2]);

            if(parsed > 1) {
                std::cout << "Pointer cannot be over 1. Line: " << lineNumber << '\n';
                exit(-3);
            }
            
            if(parsed == 0)
                toWrite.append("@THIS\r\n");
            else
                toWrite.append("@THAT\r\n");
            
            toWrite.append(getPushMemoryInstruction(memoryAccess));

            break;
        case TEMP:

            parsed = std::stoi(parts[2]);

            if(parsed > 7) {
                std::cout << "Temp cannot be over 7. Line: " << lineNumber << '\n';
                exit(-2);
            }

            parsed += 5;
            
            toWrite.append("@R" + std::to_string(parsed) + "\r\n");
            toWrite.append(getPushMemoryInstruction(memoryAccess));           

            break;
        default:
                std::cout << "Something went wrong during translation of push memory access instructions. Line: " << lineNumber << '\n';
        break;
    }
}

void Parser::pop(std::vector<std::string> parts) {
    MemoryAccess memoryAccess = getCurrentMemoryAccess(parts[1]);
    int parsed;

    switch(memoryAccess) {
        case ARGUMENT:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));
            break;
        case LOCAL:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));
            break;
        case STATIC:
            parsed = std::stoi(parts[2]);

            if(parsed > 240)
            {
                std::cout << "Static cannot be over 240. Current line: " << lineNumber << '\n';
                exit(-2);
            }

            parsed += 16;

            toWrite.append("@" + std::to_string(parsed) + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));
            break;
        case CONSTANT:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));
            break;
        case THIS:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));
            break;
        case THAT:
            toWrite.append("@" + parts[2] + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));
            break;
        case POINTER:
            parsed = std::stoi(parts[2]);

            if(parsed > 1) {
                std::cout << "Pointer cannot be over 1. Line: " << lineNumber << '\n';
                exit(-3);
            }            
            
            toWrite.append(getPopMemoryInstruction(memoryAccess));

            if(parsed == 0)
                toWrite.append("@THIS\r\n");
            else
                toWrite.append("@THAT\r\n");

            toWrite.append("M=D\r\n");

            break;
        case TEMP:
            parsed = std::stoi(parts[2]);

            if(parsed > 7) {
                std::cout << "Temp cannot be over 7. Line: " << lineNumber << '\n';
                exit(-2);
            }

            parsed += 5;

            toWrite.append("@R" + std::to_string(parsed) + "\r\n");
            toWrite.append(getPopMemoryInstruction(memoryAccess));           
            break;
        default:
            std::cout << "Something went wrong during translation of pop memory access instructions. \n";
            break;
    }
}

void Parser::addAsmPrologue() {
    toWrite.append(prologue);
}

// Trap the CPU in an infinite loop
void Parser::addAsmEpilogue() {

    toWrite.append(
        "(END)\r\n"
        "@END\r\n"
        "0;JMP\r\n"
        );
}

std::string Parser::chooseFile()
{
    std::string filename;

    std::cout << "Hello, VM! \n\nPlease enter the name of a vm file to convert to Hack assembly:\n";

    std::getline(std::cin, filename);

    if (filename == "" || filename == "\r")
        filename = "BasicTest.vm";

    return filename;
}

Parser::~Parser()
{
}