#include "auth.hh"

bool authenticateUser()
{
  std::string username;
  std::string password;

  short tries = 3;
  
  do {
    // Prompt for username.
    std::printf("Username: ");
    std::getline(std::cin, username);
    
    // Prompt for password.
    std::printf("Password: ");
    std::getline(std::cin, password);

    if (username != "root" || password != "toor") {
      // If the provided info does not match, prompt the user again.

      tries--;

      if (!tries) {
	// If the user has no tries, then shut down the OS.

	std::fprintf(stderr, "\nAuthentication failed. No tries left.\n\nShutting down.\n\n");
	return false;

      } else {
	// Otherwise, keep prompting.

	std::fprintf(stderr, "\nAuthentication failed. Tries left: %d.\n\n", tries);
      }

    // If the provided info matches, grant authentication.
    } else {
      std::fprintf(stderr, "\nAuthentication successful.\n\n");
      return true;
    }

  } while (username != "root" || password != "toor");
}
