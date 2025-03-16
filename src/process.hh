#pragma once

// C++ Standard Libraries
#include <cstdlib>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>
#include <utility>

// Project-Specific Includes
// #include "uuid.hh"
#include "code.hh"


enum PROCESS_PRIORITY {
  LOW,       // Used for child threads of normal priority threads
  MEDIUM,    // A normal priority
  HIGH,      // A performance-demanding priority
  CRITICAL,  // A system-critical priority
  KERNEL     // Used for kernel threads
};

enum PROCESS_STATE {
  NEW,       // A recently created process
  READY,     // A process to be run
  RUNNING,   // A running process
  SUSPENDED, // A suspended process
  WAITING,   // A process in the waiting queue
  TERMINATED // A process that has ended
};

enum PROCESS_IO_PERMISSIONS {
  NONE           = 0,      // A process with no IO permission (used by default)
  READ           = 1 << 0, // A process with read permissions
  WRITE          = 1 << 1, // A process with write permissions
  APPEND         = 1 << 2, // A process with append permissions
  READ_AND_WRITE = 1 << 3, // A process with read and write permissions
};

// template<typename Code>
class Process {
  // The process's UUID
  std::uint64_t pid;

  // The time which the process enters the system
  std::chrono::time_point<std::chrono::system_clock> arrivalTime;

  // The time which the process exits the system
  std::chrono::time_point<std::chrono::system_clock> terminationTime;

  // Total CPU burst execution time
  std::chrono::microseconds cpuBurstTime;

  // Total IO burst execution time
  std::chrono::microseconds ioBurstTime;

  // The process's execution priority
  PROCESS_PRIORITY priority;

  // The process's current state
  PROCESS_STATE state;

  // The remaining time that a process has
  std::chrono::microseconds remainingTime;

  // The time a process has spent on the waiting queue
  std::chrono::microseconds waitingTime;

  // Total execution time
  std::chrono::microseconds turnaroundTime;

  // Memory required
  size_t memoryRequired;

  // Flag that define the IO operations that a process can conduct
  PROCESS_IO_PERMISSIONS ioPermissions;

  // A list of child processes
  std::vector<Process> children;

  // The process's parent process
  std::unique_ptr<Process> parent;

  // A function object that stores the code to be run
  Code* code;

  // Determines the process's suspended state
  bool suspended;

  // Determines the process's waiting state
  bool waiting;

public:
  // Constructor sets up the process
  Process(Code* c, PROCESS_IO_PERMISSIONS perms);

  // Destructor to clean up the process
  virtual ~Process();

  // No default constructor, copy constructor, or move constructor
  Process(const Process&) = delete;
  Process(Process&&)      = delete;

  // No copy assignment or move assignment operators
  Process& operator=(const Process&) = delete;
  Process& operator=(Process&&)      = delete;

  // run() executes the process.
  // template<typename... Args>
  void run(// Args... args
	   );

  // updateState() changes the process's state as required
  void updateState();

  // updateRemainingTime() updates the remainingtime member to reflect
  // how much time is left for the process to execute
  void updateRemainingTime(); 

  // stop() terminates the proces
  void stop();

  // Returns arrivalTime member
  std::chrono::time_point<std::chrono::system_clock> getArrivalTime() { return arrivalTime; }

  // Returns turnaroundTime member
  std::chrono::microseconds getTurnaroundTime() { return turnaroundTime; }
};
