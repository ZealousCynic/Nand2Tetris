#include "Parser.h"

Parser::Parser(std::ifstream& toParse)
	:input(toParse)
{

}

void Parser::scan() {

	std::cout << "Parser input: \n";

	while (!input.eof())
	{
		std::string converted;

		advance();
		checkInstructionType();

		switch (currentCommand) {

		case A_COMMAND:
			if (checkForSymbol())
			{

			}
			else
			{
				converted = convertToBinary();
				toWrite.append(converted + "\n");
			}
			break;

		case C_COMMAND:

			break;

		case L_COMMAND:

			break;
		default:
			std::cout << "Something bad happened. \n";
			break;
		}
	}
}

void Parser::advance() {

	//Get next line in stream
	std::getline(input, current);

	for (int i = 0; i < current.length(); i++)
		//Is the current and next character '/'?
		if (current[i] == '/' && current[i + 1] == '/')
			//If so, erase the remainder of the the string
			current.erase(i, current.length() - i);

	//Is the string empty or a line break? If so, start over.
	if (current.length() <= 1)
		advance();

	std::cout << current << "\n";
}

void Parser::checkInstructionType() {

	char instruction = current[0];

	switch (instruction)
	{
	case '@':
		currentCommand = A_COMMAND;
		break;
	case '$':
		currentCommand = L_COMMAND;
		break;
	default:
		currentCommand = C_COMMAND;
		break;
	}
}

bool Parser::checkForSymbol() {
	return false;
}

std::string Parser::convertToBinary() {
	std::string temp = current;

	temp.erase(0, 1);

	int toConvert = std::stoi(temp);

	// This is dumb -- Look into decent initialization
	int bits[16];

	for (int i = 0; i < 15; i++)
		bits[i] = 0;

	for (int i = 0; toConvert > 0; i++)
	{
		bits[i] = toConvert % 2;
		toConvert /= 2;
	}

	std::string toReturn = "";

	for (int i = 0; i < 15; i++)
		toReturn.append(std::to_string(bits[i]));

	return toReturn;
}

std::string Parser::symbol() {
	return "";
}
std::string Parser::dest() {
	return "";
}
std::string Parser::comp() {
	return "";
}
std::string Parser::jump() {
	return "";
}

Parser::~Parser() {
	//Delete any dynamicly allocated variables
}