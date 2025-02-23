#include "shell.hh"
  
EggShell::EggShell()
  : prompt("Command")
{}
  
EggShell::EggShell(std::string _prompt)
  : prompt(_prompt)
{}

void EggShell::operator()() {
  std::string command;
  
  std::printf("Welcome to the Egg Shell.\n");
  // std::cout << std::format("{}: ", prompt);
  // std::getline(std::cin, command);

  // std::vector<std::string> tokens = parse(command);

  // commands[tokens[0]].execute(tokens);
}

void EggShell::setPrompt(std::string _prompt) {
  prompt = _prompt;
}

std::vector<std::string> EggShell::parse(std::string command) {
  std::vector<std::string> tokens;

  int a = 0, b = 0;

  for (; b < command.size(); b++) {
    if (command[b] == ' ')
      tokens.push_back(command.substr(a, b - a));
  }

  return tokens;
}
