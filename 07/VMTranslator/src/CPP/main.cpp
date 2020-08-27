#include <iostream>
#include <fstream>
#include <String>

#include "Parser.h"

int main() {

	std::ifstream fstream;

	std::ifstream& fRef = fstream;

	Parser p(fRef);

	p.scan();

	return 0;
}