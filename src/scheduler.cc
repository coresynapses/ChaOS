#include "scheduler.hh"

Scheduler::Scheduler(std::vector<ProcessArgument> _args) :
  args(_args), schedulingAlgorithm(SchedulingAlgorithm::SCHEDULER_FCFS)
{
  ProcessQueueAlgorithm<Process*> pqa;
  pqa.algo = SchedulingAlgorithm::SCHEDULER_FCFS;
}

Scheduler::~Scheduler() {}


void Scheduler::addProcess(std::uint64_t,
			   std::chrono::time_point<std::chrono::system_clock>,
			   std::chrono::time_point<std::chrono::system_clock>,
			   Process* p) {
  processQueue.push(p);
}

void Scheduler::setAlgorithm(SchedulingAlgorithm algo) {
  schedulingAlgorithm = algo;
  switch (schedulingAlgorithm) {
  case SCHEDULER_FCFS:
    algo = SchedulingAlgorithm::SCHEDULER_FCFS;
    break;
  case SCHEDULER_SJF:
    algo = SchedulingAlgorithm::SCHEDULER_SJF;
    break;
  default:
    std::cerr <<
      "Invalid Scheduling algorithm.\n"
      "Defaulting to FCFS Scheduling.\n";
    schedulingAlgorithm = SchedulingAlgorithm::SCHEDULER_FCFS;
  };
}

void Scheduler::execute() {
  while (!processQueue.empty()) {
    processQueue.top()->run();
    std::string temp = std::format("Completion Time: {}\n"
				   "Turnaround Time: {}\n"
				   "Arrival Time: {}\n",
				   processQueue.top()->getTurnaroundTime(),
				   processQueue.top()->getTurnaroundTime(),
				   processQueue.top()->getArrivalTime());
    processStatistics.push_back(temp);
    processQueue.pop();
  }
}

void Scheduler::clear() {
  args.clear();
  processStatistics.clear();

  while (!processQueue.empty()) {
    processQueue.pop();
  }
}

void Scheduler::outputStatistics() {
  for (std::string str : processStatistics) {
    std::cout << str << std::endl;
  }
}
