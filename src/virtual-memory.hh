#pragma once

// System-specific includes
#include <cstdint>

// Project-specific includes
#include "memory-space.hh"


class VirtualMemoryManager {

  MemorySpace physicalMemory;
  MemorySpace virtualMemory;

  std::uint64_t capacity;

public:
  VirtualMemoryManager() : capacity(1'000'000) {
    physicalMemory = MemorySpace(1'000'000);
    virtualMemory  = MemorySpace(1'000'000);
  }

  VirtualMemoryManager(std::uint64_t c) : capacity(c) {
    physicalMemory = MemorySpace(c);
    virtualMemory  = MemorySpace(c);
  }

  VirtualMemoryManager(std::uint64_t p, std::uint64_t v) : capacity(p) {
    physicalMemory = MemorySpace(p);
    virtualMemory  = MemorySpace(v);
  }

  std::uint64_t translateVirtualToPhysical(std::uint64_t addr) { return addr; }


  bool isEnoughMemory(std::uint64_t size) { return size < capacity; }

  void write();
};

