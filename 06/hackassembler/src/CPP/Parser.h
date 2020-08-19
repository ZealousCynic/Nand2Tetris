#ifndef PARSER_H
#define PARSER_H

#include<ios>
#include<string>
#include<iostream>
#include<fstream>

#include "SymbolTable.h"

extern "C" {
	#include "./../C/enums.h"
}

class Parser {

public:
	// Opens the input file and gets ready to parse it
	Parser(std::ifstream& toParse);

	std::ifstream& input;
	std::string processedInput;
	std::string current;
	std::string currentSymbol;
	std::string toWrite;
	bool hasMoreCommands;

	commandType currentCommand;
	SymbolTable symt;

	void scan();

	void advance();
	std::string symbol();
	std::string dest();
	std::string comp();
	std::string jump();

	~Parser();

private:
	void printTemp();
	void checkInstructionType();
	bool findA();
	std::string scanSymbol();
	std::string convertToBinary(int toConvert);
	bool checkForSymbol();
};

#endif