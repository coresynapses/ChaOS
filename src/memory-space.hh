#pragma once

// System-level include
#include <cstdint>

class MemorySpace {
  std::uint64_t capacity;
  
public:

  MemorySpace() : capacity(16'000) {}

  MemorySpace(std::uint64_t c) : capacity(c) {}

  void setCapacity(std::uint64_t c) { capacity = c; }
};
