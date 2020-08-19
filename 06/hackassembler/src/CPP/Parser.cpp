#include "Parser.h"

Parser::Parser(std::ifstream& toParse)
	:input(toParse)
{

}

void Parser::scan() {

	std::cout << "Parser input: \n";

	while (!input.eof())
	{
		advance();

		processedInput.append(current);

		printTemp();
	}

	std::ifstream processed("temp", std::ifstream::in);
	input = &processed;

	while (!input.eof()) {

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

			std::cout << temp << '\n';

			toWrite.append(temp);
				break;
		}
		case L_COMMAND:
			std::cout << "Something bad happened. \n";
			break;
		default:
			std::cout << "Something bad happened. \n";
			break;
		}
	}
}

void Parser::advance() {

	// Get next line in stream
	std::getline(input, current);

	for (int i = 0; i < current.length(); i++)
		// Is the current and next character '/'?
		if (current[i] == '/' && current[i + 1] == '/')
			//If so, erase the remainder of the the string
			current.erase(i, current.length() - i);

	// Is the string empty or a line break? If so, start over.
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

// Actually checks if the 2nd character is a digit.
// If it isn't a digit, it must be a symbol, in which case, return true.
bool Parser::checkForSymbol() {

	if (std::isdigit(current[1]))
	{
		return false;
	}
	return true;
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

bool Parser::findA() {
	if (current[0] == 'M' || current[1] == 'M')
		return true;
	return false;
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

	for (int i = 0; i < current.length();i++)
	{
		if (current[i] == '=')
			dest = current.substr(0, i);
	}

	return destinationMap.find(dest)->second;
}
std::string Parser::comp() {

	std::string comp = "000000";

	return comp;
}
std::string Parser::jump() {

	std::string jump = "000";

		return jump;
}

void Parser::printTemp() {

	std::filebuf fb;
	fb.open("temp", std::ios::out);
	std::ostream ostream(&fb);
	ostream << processedInput;
	fb.close();
}

Parser::~Parser() {
	//Delete any dynamicly allocated variables
}