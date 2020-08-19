#include "SymbolTable.h"

SymbolTable::SymbolTable() {

	addEntry("R0", 0);
	addEntry("R1", 1);
	addEntry("R2", 2);
	addEntry("R3", 3);
	addEntry("R4", 4);
	addEntry("R5", 5);
	addEntry("R6", 6);
	addEntry("R7", 7);
	addEntry("R8", 8);
	addEntry("R9", 9);
	addEntry("R10", 10);
	addEntry("R11", 11);
	addEntry("R12", 12);
	addEntry("R13", 13);
	addEntry("R14", 14);
	addEntry("R15", 15);
	addEntry("SCREEN", 16384);
	addEntry("KBD", 24576);
	addEntry("SP", 0);
	addEntry("LCL", 1);
	addEntry("ARG", 2);
	addEntry("THIS", 3);
	addEntry("THAT", 4);
}

void SymbolTable::addEntry(std::string symbol, int address) {

	symbols.insert(std::make_pair(symbol, address));
}

bool SymbolTable::contains(std::string symbol) {
	if (symbols.find(symbol) != symbols.end())
		return true;
	return false;
}

int SymbolTable::getAddress(std::string symbol) {
	
	return symbols.find(symbol)->second;
}

int SymbolTable::getNextAddress() {
	
	nextAddress++;

	return nextAddress;
}

void SymbolTable::printTable() {
	for (auto const& pair : symbols) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
}