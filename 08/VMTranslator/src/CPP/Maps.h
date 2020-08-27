#ifndef MAPS_H
#define MAPS_H

#include <String>
#include <unordered_map>

#include "enums.h"

const extern std::unordered_map<Instruction, std::string> VMToASMInstructionMap;
const extern std::unordered_map<MemoryAccess, std::string> PushMap;
const extern std::unordered_map<MemoryAccess, std::string> PopMap;
const extern std::unordered_map<std::string, Instruction> InstructionMap;
const extern std::unordered_map<std::string, MemoryAccess> MemoryAccessMap;

const extern std::string prologue;

#endif