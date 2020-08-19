#include "Parser.h"

Parser::Parser(std::string toParse)
{
	filename = toParse;
}

void Parser::scan() {

	input.open(filename, std::ifstream::in);

	if (input.is_open()) {

		while (!input.eof())
		{
			cleanInput();
		}
		input.close();
	}
	else
		std::cout << "Could not open assembly file.\n";

	printTemp();

	in2.open("temp", std::ifstream::in);

	if (in2.is_open())
	{
		lineCount = 0;

		while (!in2.eof()) {

			advance();

			if (current.empty())
				continue;

			std::string converted;
			checkInstructionType();

			switch (currentCommand) {

			case A_COMMAND:
			{
				if (checkForSymbol())
				{
					currentSymbol = scanSymbol();

					converted = symbol();

					toWrite.append(converted + "\n");
				}
				else
				{
					std::string temp = current;

					temp.erase(0, 1);

					int toConvert = std::stoi(temp);

					converted = convertToBinary(toConvert);

					toWrite.append(converted + "\n");
				}
				break;
			}
			case C_COMMAND:
			{
				std::string temp = "111";

				temp.append(findA() ? "1" : "0");

				temp.append(comp());

				temp.append(dest());

				temp.append(jump());

				toWrite.append(temp + '\n');

				break;
			}
			case L_COMMAND:
				if (checkForLabel()) {

					currentSymbol = scanLabel();

					converted = label();

					toWrite.append(converted + "\n");

				}
				else
					std::cout << "Something bad happened. \n";
				break;
			default:
				std::cout << "Something bad happened. \n";
				break;
			}
		}

		in2.close();
		std::cout << "Writing: \n" << toWrite;
	}
	else
		std::cout << "File could not be opened!\n";

}

void Parser::advance() {

	std::getline(in2, current);
	lineCount++;
}

//This is the most horrible thing I have written in years and years. Please kill it with fire.
void Parser::cleanInput() {

	// Get next line in stream
	std::getline(input, current);

	if (current.length() <= 2 || current.empty() || current[0] == '\n' || current[0] == '\r')
		return;

	for (int i = 0; i < current.length(); i++)
	{
		if (current[i] == ' ')
			current.erase(i, 1);

		// Is the current and next character '/'?
		if (current[i] == '/' && current[i + 1] == '/')
			//If so, erase the remainder of the the string, except the line break.
			current.erase(i, current.length() - i);
		if (current[i] == '\r' && current[i + 1] == '\r')
			current.erase(i, 2);
	}
	while (current[0] == '\r')
		current.erase(0, 1);
	// Is the string empty or a line break? If so, start over.
	if (current.empty())
		return;
	if (current[0] == '\n')
		return;
	if (current[current.length() - 1] != '\r')
		current += '\r';

	current += '\n';
	std::cout << current;
	processedInput.append(current);
}

void Parser::checkInstructionType() {

	char instruction = current[0];

	switch (instruction)
	{
	case '@':
		currentCommand = A_COMMAND;
		break;
	case '(':
		currentCommand = L_COMMAND;
		break;
	default:
		currentCommand = C_COMMAND;
		break;
	}
}

// Actually checks if the 2nd character is a digit.
// If it isn't a digit, it must be a symbol, in which case, return true.
bool Parser::checkForSymbol() {

	if (std::isdigit(current[1]))
		return false;
	return true;
}

bool Parser::checkForLabel() {
	if (current[0] == '(')
		return true;
	return false;
}

std::string Parser::convertToBinary(int toConvert) {

	// This is dumb -- Look into decent initialization
	int bits[16];

	for (int i = 0; i < 16; i++)
		bits[i] = 0;

	for (int i = 15; toConvert > 0; i--)
	{
		bits[i] = toConvert % 2;
		toConvert /= 2;
	}

	std::string toReturn = "";

	for (int i = 0; i < 16; i++)
		toReturn.append(std::to_string(bits[i]));

	return toReturn;
}

std::string Parser::scanSymbol() {

	std::string sub;

	for (int i = 0; i < current.length(); i++)
	{
		if (i >= current.length() - 1 || current[i] == '=' || current[i] == '\n' || current[i] == '\0')
		{
			sub = current.substr(1, i - 1);

			return sub;
		}
	}
}

std::string Parser::scanLabel() {

	std::string sub;

	sub = current.substr(1, current.length() - 3);

	return sub;
}

bool Parser::findA() {
	if (current[0] == 'M' || current[1] == 'M')
		return true;
	return false;
}

std::string Parser::label() {
	
	std::string toReturn;
	int address;

	if (symt.contains(currentSymbol))
	{
		address = symt.getAddress(currentSymbol);
	}
	else {
		address = lineCount + 1;

		symt.addEntry(currentSymbol, address);
	}

	toReturn = convertToBinary(address);

	return toReturn;

}

std::string Parser::symbol() {

	std::string toReturn;
	int address;

	if (symt.contains(currentSymbol))
	{
		address = symt.getAddress(currentSymbol);
	}
	else {
		address = symt.getNextAddress();

		symt.addEntry(currentSymbol, address);
	}

	toReturn = convertToBinary(address);

	return toReturn;
}

std::string Parser::dest() {

	std::string dest = "null";

	for (int i = 0; i < current.length(); i++)
	{
		if (current[i] == '=')
			dest = current.substr(0, i);
	}

	return destinationMap.find(dest)->second;
}

//Dumb solution is dumb, I just wanted it to work at this point.
std::string Parser::comp() {

	std::string comp = "000000";
	int compBegin, compEnd = 0;
	bool jumping = false;

	for (int i = 0; i < current.length(); i++)
	{
		if (current[i] == '=')
			compBegin = i + 1;
		if (current[i] == ';')
		{
			compEnd = i - 1;
			jumping = true;
		}
	}

	if (compEnd == 0 && jumping)
		compEnd = 1;
	if (compEnd == 0)
		compEnd = current.length() - 1;
	

	comp = current.substr(compBegin, compEnd - compBegin);

	return instructionMap.find(comp)->second;
}
std::string Parser::jump() {

	std::string jump = "null";

	int jmpBegin = 0;

	for (int i = 0; i < current.length(); i++)
	{
		if (current[i] == ';')
			jmpBegin = i + 1;
	}

	if (jmpBegin != 0)
		jump = current.substr(jmpBegin, current.length() - jmpBegin - 1);


	return jumpMap.find(jump)->second;
}

void Parser::printTemp() {

	std::filebuf fb;
	fb.open("temp", std::ios::out);
	if (fb.is_open()) {

		std::ostream os(&fb);
		os << processedInput;
		fb.close();
	}
	else {
		std::cout << "Could not open file for writing.";
	}
}

Parser::~Parser() {
	//Delete any dynamicly allocated variables
}