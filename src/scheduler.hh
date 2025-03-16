#pragma once

// System-specific includes
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <queue>
#include <cstdint>
#include <chrono>

// Project-specific includes
#include "process.hh"

enum SchedulingAlgorithm {
  SCHEDULER_FCFS,
  SCHEDULER_SJF
};

template<typename T>
struct ProcessQueueAlgorithm {
private:
  bool FCFS(const T& lhs, const T& rhs) const {
    return lhs->getArrivalTime() < rhs->getArrivalTime();
  }

  bool SJF(const T& lhs, const T& rhs) const {
    return lhs->getTurnaroundTime() < rhs->getTurnaroundTime();
  }

public:
  SchedulingAlgorithm algo;

  bool operator() (const T& lhs, const T& rhs) const {
    switch (algo) {
    case SCHEDULER_FCFS:
      return FCFS(lhs, rhs);
    case SCHEDULER_SJF:
      return SJF(lhs, rhs);
    }
  }
};

struct ProcessArgument {
  ProcessArgument(std::uint64_t _processId, std::string _arrivalTime, std::string _burstTime) :
    processId(_processId), arrivalTime(_arrivalTime), burstTime(_burstTime)
  {}
  std::uint64_t processId;
  std::string   arrivalTime;
  std::string   burstTime;
};

class Scheduler {
  std::vector<ProcessArgument> args;

  std::vector<std::string> processStatistics;
  std::priority_queue<Process*, std::vector<Process*>, ProcessQueueAlgorithm<Process*>> processQueue;

  SchedulingAlgorithm schedulingAlgorithm;

public:

  Scheduler(std::vector<ProcessArgument>);
  ~Scheduler();

  void addProcess(std::uint64_t,
		  std::chrono::time_point<std::chrono::system_clock>,
		  std::chrono::time_point<std::chrono::system_clock>,
		  Process*);

  void setAlgorithm(SchedulingAlgorithm);

  void execute();

  void clear();

  void outputStatistics();
};
