#ifndef PARSER_H
#define PARSER_H

#include<ios>
#include<string>
#include<iostream>
#include<fstream>

extern "C" {
	#include "./../C/enums.h"
}

class Parser {

public:
	// Opens the input file and gets ready to parse it
	Parser(std::ifstream& toParse);

	std::ifstream& input;
	bool hasMoreCommands;
	commandType currentCommand;
	std::string current;
	std::string toWrite;

	void scan();

	void advance();
	std::string symbol();
	std::string dest();
	std::string comp();
	std::string jump();

	~Parser();

private:
	void checkInstructionType();
	std::string convertToBinary();
	bool checkForSymbol();
};

#endif