#pragma once

// System-specific includes
#include <iostream>

class Code {
public:
  // template<typename... Args>
  // void operator() (Args... args) {
  //   std::cout << "asdf" << std::endl;
  // }

  virtual void operator() () {
    std::cerr << "Type deduction failed.\n";
  }

  virtual void run () {
    (*this)();
  }
};
