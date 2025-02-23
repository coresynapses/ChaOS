#include "process.hh"
#include <chrono>

// Namespace for Chrono Literals
using namespace std::literals::chrono_literals;

Process::Process(Code* c, PROCESS_IO_PERMISSIONS perms = PROCESS_IO_PERMISSIONS::NONE) :
  // pid(UUID::Generate()),
  arrivalTime(std::chrono::system_clock::now()),
  terminationTime(std::chrono::system_clock::now()),
  cpuBurstTime(std::chrono::microseconds::zero()),
  ioBurstTime(std::chrono::microseconds::zero()),
  priority(PROCESS_PRIORITY::MEDIUM),
  state(PROCESS_STATE::NEW),
  remainingTime(10 * 60 * 1000000 * 1us), // 10 minutes
  waitingTime(0ms),
  turnaroundTime(0ms),
  memoryRequired(0),
  ioPermissions(perms),
  // children({}),
  parent(nullptr),
  code(c)
{}

Process::~Process() {
  updateState();
  stop();
}

void Process::run() {
  updateState();
  arrivalTime = std::chrono::system_clock::now();
  // code(args...);
  // code->run();
  (*code)();
}

void Process::updateState() {
  switch(state) {
  case PROCESS_STATE::NEW:
    state = PROCESS_STATE::READY;
    break;
  case PROCESS_STATE::READY:
    state = PROCESS_STATE::RUNNING;
    break;
  case PROCESS_STATE::RUNNING:
    state = (suspended) ? PROCESS_STATE::SUSPENDED :
            (waiting)   ? PROCESS_STATE::WAITING
	                : PROCESS_STATE::TERMINATED;
    break;
  case PROCESS_STATE::SUSPENDED:
    state = (!suspended) ? PROCESS_STATE::RUNNING :
            (waiting)    ? PROCESS_STATE::WAITING
	                 : PROCESS_STATE::TERMINATED;
    break;
  case PROCESS_STATE::WAITING:
    state = (suspended) ? PROCESS_STATE::SUSPENDED :
            (!waiting)  ? PROCESS_STATE::RUNNING
	                : PROCESS_STATE::TERMINATED;
    break;
  case PROCESS_STATE::TERMINATED:
    // Do nothing
    break;
  };
}

void Process::updateRemainingTime() {
  // This makes this function way more readable.
  using namespace std::chrono;
  
  // Calculates the duration between the start of the intial process
  // to right now.
  // Then it type-casts that duration to microseconds.
  // Then it subtracts that from the remaining time.
  remainingTime -= duration_cast<microseconds>(arrivalTime - system_clock::now());
}

void Process::stop() {
  updateState();
  terminationTime = std::chrono::system_clock::now();
  turnaroundTime = std::chrono::duration_cast<std::chrono::microseconds>(terminationTime - arrivalTime);
}
