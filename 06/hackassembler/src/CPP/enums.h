#ifndef ENUMS_H
#define ENUMS_H

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