#pragma once

// System-specific includes
#include <unordered_map>
#include <memory>

// Project-specific includes
#include "virtual-memory.hh"
#include "page.hh"

class PageTable {
  // Fixed page size = 4 KB
  const size_t  pageSize = 4'000;

  std::unordered_map<std::uint64_t, Page> pages;

  static std::unique_ptr<VirtualMemoryManager> memoryManager;
  
public:

  PageTable() {
    if (!memoryManager) {
      memoryManager.reset(new VirtualMemoryManager());
    }
  }

  void          allocate(std::uint64_t);
  std::uint64_t read(std::uint64_t);
  void          write(std::uint64_t, std::uint64_t);
};
