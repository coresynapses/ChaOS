// System-specific includes
#include <cstdio>
#include <cwchar>
#include <iostream>
#include <format>
#include <memory>

// Project-specific includes
#include "auth.hh"
#include "scheduler.hh"
#include "process.hh"
#include "shell.hh"
#include "example.hh"

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
  // Print the boot up message.
  std::printf("Initiating ChaOS...\n\n");

  // Authenticate the user.
  if (authenticateUser()) {
    // Ignore this block.
    // This is code for a previous assignment.
    {
      // // If passed, do the following:
      // // Create a process that adds two numbers and give it no IO
      // // permissions.
      // SumProcess* sp = new SumProcess;
      // Process p1(sp, PROCESS_IO_PERMISSIONS::NONE);
      
      // // Create a process that calculates the first 100 prime numbers
      // // and give it write permissions.
      // PrimesProcess* prp = new PrimesProcess;
      // Process p2(prp, PROCESS_IO_PERMISSIONS::WRITE);
      
      // // Start the Egg Shell as a Process Object and give
      // // read and write permissions.
      // EggShell* sh = new EggShell("Prompt");
      // Process p3(sh, PROCESS_IO_PERMISSIONS::READ_AND_WRITE);

      // p1.run();
      // p2.run();
      // p3.run();
    }

    // This block is for Assignment 4.
    {
      // First, process the command line arguments.
      std::vector<ProcessArgument> args;

      for (int i = 0; i < argc; i += 3) {
	try {
	  args.emplace_back(std::stoi(argv[i]), argv[i+1], argv[i+2]);
	}
	catch(std::exception e) {
	  std::cerr << std::format("Invalid command-line arguments.\n"
				   "Encountered the following error:\n{}", e.what());
	}
      }

      // Create the scheduler and pass it the command line arguments.
      Scheduler sch(args);

      // Set the scheduler to FCFS scheduling algorithm.
      sch.setAlgorithm(SchedulingAlgorithm::SCHEDULER_FCFS);

      // Execute the processes and then clear the scheduler.
      sch.execute();
      sch.outputStatistics();
      sch.clear();

      // Set the scheduler to SJF scheduling algorithm.
      sch.setAlgorithm(SchedulingAlgorithm::SCHEDULER_SJF);

      // Add other processes.
      SumProcess* sp     = new SumProcess;
      PrimesProcess* prp = new PrimesProcess;
      EggShell* sh       = new EggShell("Prompt: ");

      Process* p4 = new Process(sp,  PROCESS_IO_PERMISSIONS::NONE);
      Process* p5 = new Process(prp, PROCESS_IO_PERMISSIONS::WRITE);
      Process* p6 = new Process(sh,  PROCESS_IO_PERMISSIONS::READ_AND_WRITE);

      sch.addProcess(4, std::chrono::system_clock::now(), std::chrono::system_clock::now() + 5s, p4);
      sch.addProcess(5, std::chrono::system_clock::now(), std::chrono::system_clock::now() + 4s, p5);
      sch.addProcess(6, std::chrono::system_clock::now(), std::chrono::system_clock::now() + 6s, p6);

      // Execute the processes and then clear the scheduler.
      sch.execute();
      sch.outputStatistics();
      sch.clear();
    }
  } else {
    // Otherwise, shut down.
    std::printf("\nShutting down.\n\n");
  }
}
