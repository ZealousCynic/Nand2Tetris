#ifndef SYMTABLE_H
#define SYMTABLE_H

#include<string>
#include<map>

class SymbolTable {

public:
	SymbolTable();

	void addEntry(std::string symbol, int address);
	bool contains(std::string symbol);
	int getAddress(std::string symbol);

private:
	std::map<std::string, int> symbols;
};

#endif