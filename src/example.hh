#pragma once

// System-specific includes
#include <cstdio>
#include <vector>

// Project-specific includes
#include "code.hh"

// This class contains code that adds two numbers and outputs the
// result.
class SumProcess : public Code {
public:
  void operator() () override {
    int a = 2;
    int b = 3;

    std::printf("%d + %d = %d\n", a, b, (a + b));
  }
};

// This class contains code that calculates the first 100 prime
// numbers and outputs the result.
class PrimesProcess : public Code {
public:
  void operator() () override {
    // Calculate first 100 primes

    std::vector<unsigned short> primes = { 2, 3 };

    for (unsigned short i = 2; primes.size() < 100 && i < 1000; i++) {
      if (is_prime(i, primes)) {
	primes.push_back(i);
      }
    }

    for (auto n : primes)
      std::printf("%d ", n);
    std::putchar('\n');
  }

  bool is_prime(unsigned short n, std::vector<unsigned short> &primes) {
    for (auto i : primes) {
      if ((n % i) == 0) {
	return false;
      }
    }
    return true;
  }
};

