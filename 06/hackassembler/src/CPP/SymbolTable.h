#ifndef SYMTABLE_H
#define SYMTABLE_H

#include<string>
#include<iostream>
#include<map>

class SymbolTable {

public:
	SymbolTable();

	void addEntry(std::string symbol, int address);
	bool contains(std::string symbol);
	int getAddress(std::string symbol);
	int getNextAddress();

	void printTable();

private:
	int nextAddress = 15;

	std::map<std::string, int> symbols;
};

#endif