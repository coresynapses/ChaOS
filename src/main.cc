// System-specific includes
#include <cstdio>
#include <cwchar>
#include <iostream>
#include <memory>

// Project-specific includes
#include "auth.hh"
#include "process.hh"
#include "shell.hh"
#include "example.hh"

int main()
{
  // Print the boot up message.
  std::printf("Initiating ChaOS...\n\n");

  // Authenticate the user.
  if (authenticateUser()) {
    // If passed, do the following:
    // Create a process that adds two numbers and give it no IO
    // permissions.
    SumProcess* sp = new SumProcess;
    Process p1(sp, PROCESS_IO_PERMISSIONS::NONE);

    // Create a process that calculates the first 100 prime numbers
    // and give it write permissions.
    PrimesProcess* prp = new PrimesProcess;
    Process p2(prp, PROCESS_IO_PERMISSIONS::WRITE);

    // Start the Egg Shell as a Process Object and give
    // read and write permissions.
    EggShell* sh = new EggShell("Prompt");
    Process p3(sh, PROCESS_IO_PERMISSIONS::READ_AND_WRITE);

    p1.run();
    p2.run();
    p3.run();
  } else {
    // Otherwise, shut down.
    std::printf("\nShutting down.\n\n");
  }
}
