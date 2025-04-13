#pragma once

// System-level Includes
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

// Project-level Includes
#include "process.hh"

enum InstructionType {
  INSTRUCTION_ALLOCATE,
  INSTRUCTION_WRITE,
  INSTRUCTION_READ,
  INSTRUCTION_INVALID
};

class Instruction {

  InstructionType type;
  std::uint64_t processId;
  std::vector<std::uint64_t> arguments;

public:

  Instruction() :
    type(INSTRUCTION_INVALID),
    processId(-1)
  {}

  Instruction(InstructionType it,
	      std::uint64_t pid,
	      std::vector<std::uint64_t> args) :
    type(it),
    processId(pid),
    arguments(args)
  {}

  InstructionType            getType() { return type; }
  std::uint64_t              getPid()  { return processId; }
  std::vector<std::uint64_t> getArgs() { return arguments; }
};

class Workload {
  std::uint64_t id;

  std::unordered_map<std::uint64_t, Process*> processes;

  std::vector<Instruction> instructions;

public:

  Workload(std::string);

  ~Workload();

  void execute();
};
