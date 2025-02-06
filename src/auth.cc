#include "auth.hh"

void authenticateUser()
{
  std::string username;
  std::string password;

  short tries = 3;
  
  do {
    std::printf("Username: ");
    std::getline(std::cin, username);
    
    std::printf("Password: ");
    std::getline(std::cin, password);

    if (username != "root" || password != "toor") {
      tries--;
      if (tries == 0) {
	std::fprintf(stderr, "\nAuthentication failed. No tries left.\n\nShutting down.\n\n");
	break;
      } else {
	std::fprintf(stderr, "\nAuthentication failed. Tries left: %d.\n\n", tries);
      }
    } else {
      std::fprintf(stderr, "\nAuthentication successful.\n\n");
      break;
    }
  } while (username != "root" || password != "toor");
}
