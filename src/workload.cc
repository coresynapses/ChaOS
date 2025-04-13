#include "workload.hh"
#include <cstdint>

Workload::Workload(std::string filename) {
  // std::printf("Workload filename: %s\n\n", filename.c_str());
  std::ifstream inputFile;

  inputFile.open(filename);

  // Get the Workload ID
  std::string temp;
  std::getline(inputFile, temp);

  id = std::stoi(temp);
  // std::printf("Workload ID: %llu\n", id);

  // Get the list of process ID's
  std::getline(inputFile, temp);

  std::stringstream ss(temp);
  char p;
  ss >> p;
  if (p != 'p')
    std::printf("Invalid workload: %s\n", temp.c_str());
  // else
  //   std::printf("Reading process IDs: ");

  std::uint64_t pid;
  while (!ss.eof()) {
    ss >> pid;
    processes[pid] = nullptr;
    // std::cout << pid << " ";
  }
  ss.clear();
  putchar('\n');

  // Get the list of instructions
  std::getline(inputFile, temp);

  if (temp != "i")
    std::printf("Invalid workload: %s\n", temp.c_str());
  // else
  //   std::printf("Reading instructions: \n");

  InstructionType type;
  std::uint64_t arg;
  std::vector<std::uint64_t> args;

  while (!inputFile.eof()) {
    std::getline(inputFile, temp);
    if (temp.empty()) continue;
    ss.str(temp);

    ss >> temp;
    // std::cout << temp << " ";

    if (temp == "allocate") {
      type = InstructionType::INSTRUCTION_ALLOCATE;
    }
    else if (temp == "write") {
      type = InstructionType::INSTRUCTION_WRITE;
    }
    else if (temp == "read") {
      type = InstructionType::INSTRUCTION_READ;
    }
    else {
      type = InstructionType::INSTRUCTION_INVALID;
    }

    ss >> pid;
    // std::cout << pid << " ";
      
    while (!ss.eof()) {
      ss >> arg;
      // std::cout << arg << " ";
      args.push_back(arg);
    }

    Instruction instr(type, pid, args);
    instructions.push_back(instr);

    temp.clear();
    args.clear();
    ss.clear();
  }

  inputFile.close();
}

Workload::~Workload() {
  for (std::unordered_map<std::uint64_t, Process*>::iterator it = processes.begin();
       it == processes.end();
       it++) {
    if (it->second) 
      delete it->second;
  }
}

void Workload::execute() {
  std::printf("Executing workload %llu\n\n", id);

  std::printf("\nLaunching processes:\n");
  for (std::unordered_map<std::uint64_t, Process*>::iterator it = processes.begin();
       it == processes.end();
       it++) {
    std::printf("Creating process %llu.\n", it->first);
    it->second = new Process(nullptr, PROCESS_IO_PERMISSIONS::READ_AND_WRITE);
  }

  std::printf("\nExecuting instructions:\n");

  for (auto instr : instructions) {
    if (instr.getType() == InstructionType::INSTRUCTION_ALLOCATE) {
      std::printf("Allocating of %llu memory for process %llu.\n",
		  instr.getArgs()[0],
		  instr.getPid());

      processes[instr.getPid()]->allocate(instr.getArgs()[0]);
    }
    else if (instr.getType() == InstructionType::INSTRUCTION_READ) {
      std::printf("Reading memory address %#llX from process %llu.\n",
		  instr.getArgs()[0],
		  instr.getPid());

      processes[instr.getPid()]->readMemory(instr.getArgs());
    }
    else if (instr.getType() == InstructionType::INSTRUCTION_WRITE) {
      std::printf("Writing %llu to memory address %#llX for process %llu.\n",
		  instr.getArgs()[1],
		  instr.getArgs()[0],
		  instr.getPid());

      processes[instr.getPid()]->writeMemory(instr.getArgs());
    }
    else {
      std::printf("Invalid instruction.\n");
    }
  }
}
