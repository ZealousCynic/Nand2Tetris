#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include "Parser.h"

std::string filename;

void introduction() {

	std::cout << "Write a filename, extension assumed to be .asm, path is relative to parser.exe: \n";

	std::getline(std::cin, filename);

	filename.append(".asm");

	std::cout << "Opening " << filename << " ... \n";
}

void print(std::string* toPrint) {

	std::cout << "Enter a name for the output file: \n";

	std::string outputfile;

	std::getline(std::cin, outputfile);

	std::cout << "Printing output to file: \n\n" << *toPrint;

	std::filebuf fb;
	fb.open(outputfile, std::ios::out);
	std::ostream ostream(&fb);
	ostream << *toPrint;
	fb.close();

	std::cout << "\nOperation finished. \n";
}

int main() {

	introduction();

	std::unique_ptr<std::ifstream> fsPtr(new std::ifstream(filename.c_str(), std::ifstream::in));

	Parser p(*fsPtr);

	p.scan();

	print(&p.toWrite);

	//std::cout << "Symbol table: \n";

	//p.symt.printTable();

	return 0;
}