#ifndef PARSER_H
#define PARSER_H

#include<ios>
#include<string>
#include<iostream>
#include<fstream>

#include "SymbolTable.h"
#include "enums.h"
#include "maps.h"


class Parser {

public:

	// Opens the input file and gets ready to parse it
	Parser(std::string toParse);

	std::ifstream in2;
	std::ifstream input;

	std::string filename;

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
	std::string label();

	~Parser();

private:

	int lineCount; // For labels

	std::string processedInput;
	std::string cleanedInput;
	std::string current;
	std::string currentSymbol;

	void cleanInput();
	void printTemp(std::string filename, std::string toPrint);
	void checkInstructionType();
	void scanForLabel();
	bool findA();
	std::string scanSymbol();
	std::string scanLabel();
	std::string convertToBinary(int toConvert);
	bool checkForLabel();
	bool checkForSymbol();
	void removeLabel();
};

#endif