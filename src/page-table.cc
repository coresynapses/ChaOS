#include "page-table.hh"

void PageTable::allocate(std::uint64_t size) {
  // Check if there is enough memory
  if (!memoryManager->isEnoughMemory(size)) {
    printf("Memory not allocated. Requested allocation size exceeds capacity.\n");
  }

  // Create enough pages to satisfy requirement
  unsigned numPages = size / pageSize + (size % pageSize) ? 1 : 0;
}

std::uint64_t PageTable::read(std::uint64_t addr) {
  return memoryManager->translateVirtualToPhysical(addr);
}

void PageTable::write(std::uint64_t addr, std::uint64_t val) {
  std::uint64_t physicalAddress = memoryManager->translateVirtualToPhysical(addr);
  
} 
