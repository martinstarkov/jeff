#pragma once

#include "common.h"

class AllocationMetrics {
public:
	static uint32_t currentUsage();
	static void allocation(const size_t& size);
	static void deallocation(const size_t& size);
	static void printMemoryUsage();
private:
	static uint32_t _totalAllocated;
	static uint32_t _totalFreed;
};

