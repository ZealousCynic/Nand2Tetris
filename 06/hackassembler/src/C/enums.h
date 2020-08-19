#ifndef ENUMS_H
#define ENUMS_H

#include<map>
#include<string>

typedef enum commandType_t {
	A_COMMAND = 0,
	C_COMMAND = 1,
	L_COMMAND
} commandType;

//typedef enum instructionBitsA_t {
//	ZERO = 101010,
//	ONE = 111111,
//	NEG_ONE = -111010,
//	D = 001100,
//	A = 110000,
//	NOT_D = 001101,
//	NOT_A = 110001,
//	MINUS_D = 001111,
//	MINUS_A = 110011,
//	D_PLUS_ONE = 011111,
//	A_PLUS_ONE = 110111,
//	D_MINUS_ONE = 001110,
//	A_MINUS_ONE = 110010,
//	D_PLUS_A = 000010,
//	D_MINUS_A = 010011,
//	A_MINUS_D = 000111,
//	D_AND_A = 000000,
//	D_OR_A = 010101,
//} instructionBitsA;

std::map<std::string, std::string> instructionMap = {
	{"0", "101010"},
	{"1", "111111"}, 
	{"-1", "111010"},
	{"D", "001100"},
	{"A", "110000"},
	{"!D", "001101"},
	{"!A", "110001"},
	{"-D", "001111"},
	{"-A", "110011"},
	{"D+1", "011111"},
	{"A+1", "110111"},
	{"D-1", "001110"},
	{"A-1", "110010"},
	{"D+A", "000010"},
	{"D-A", "010011"},
	{"A-D", "000111"},
	{"D&A", "000000"},
	{"D|A", "010101"},
	{"M", "110000"},
	{"!M", "110001"},
	{"-M", "110011"},
	{"M+1", "110111"},
	{"M-1", "110010"},
	{"D+M", "000010"},
	{"D-M", "010011"},
	{"M-D", "000111"},
	{"D&M", "000000"},
	{"D|M", "010101"},
};

std::map<std::string, std::string> destinationMap = {
	{"null", "000"},
	{"M", "001"},
	{"D", "010"},
	{"MD", "011"},
	{"A", "100"},
	{"AM", "101"},
	{"AD", "110"},
	{"AMD", "111"},
};

//typedef enum instructionBitsB_t {
//
//} instructionBitsB;
//
//typedef enum destinationBits_t {
//
//} destinationBits;
//
//typedef enum jumpBits_t {
//
//} jumpBits;
#endif