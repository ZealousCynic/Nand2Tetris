#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "StringHandler.h"
#include "FileHandler.h"
#include "Maps.h"

class Parser {

public:
    Parser(std::ifstream& input);

    std::string toWrite;

    std::string advance();
    void scan();   

    ~Parser();

private:

    int lineNumber;
    StringHandler sh;
    FileHandler fh;
    std::ifstream& input;

    void print(std::string filename, std::string toPrint);

    std::string chooseDirectory();
    std::string cleanInput(std::string toClean);

    Instruction getCurrentInstruction(std::string toCompare);
    MemoryAccess getCurrentMemoryAccess(std::string toCompare);
    std::string getAssemblyInstruction(Instruction toGet);
    std::string getPushMemoryInstruction(MemoryAccess toGet);
    std::string getPopMemoryInstruction(MemoryAccess toGet);

    void addAsmPrologue();
    void addAsmEpilogue();

    void push(std::vector<std::string> parts);
    void pop(std::vector<std::string> parts);
};

#endif