#pragma once

// System-specific includes
#include <cstdint>

// Project-specific includes
// #include ""

enum PageProtectionStatus {
  PAGE_READ_ONLY,
  PAGE_READ_WRITE,
  PAGE_EXECUTE_ONLY
};

class Page {
  // Fixed page size = 4 KB
  const size_t  pageSize = 4'000;

  std::uint64_t pageNumber;
  std::uint64_t pageOffset;

  PageProtectionStatus protectionStatus;
  bool validBit;

public:
  Page() :
    pageNumber(0),
    pageOffset(0),
    protectionStatus(PAGE_READ_ONLY),
    validBit(true)
  {}
  
  Page(std::uint64_t pnum, std::uint64_t poff, PageProtectionStatus pps = PAGE_READ_ONLY) :
    pageNumber(pnum),
    pageOffset(poff),
    protectionStatus(pps),
    validBit(true)
  {}

};
