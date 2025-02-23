#pragma once

// System-specific includes
#include <iostream>
#include <format>
#include <string>
#include <vector>

// Project-specific includes
#include "code.hh"

class EggShell : public Code {
  std::string prompt;

public:

  EggShell();
  EggShell(std::string);

  void operator() () override;

  void run () override {
    (*this)();
  }

  void setPrompt(std::string);

  std::vector<std::string> parse(std::string);

};
