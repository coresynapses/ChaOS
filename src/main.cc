#include <cstdio>

#include "shell.hh"
#include "auth.hh"

int main()
{
  // Print the boot up message.
  std::printf("Initiating ChaOS...\n\n");

  // Authenticate the user.
  if (authenticateUser()) {
    // If passed, start the shell.
  } else {
    // Otherwise, shut down.
    std::printf("\nShutting down.\n\n");
  }
}
