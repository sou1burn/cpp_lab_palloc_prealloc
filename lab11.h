#pragma once
#ifndef lab11_h
#define lab11_h
#include <stdlib.h>

struct  MemoryManager {
	unsigned int* bitmap;
	size_t size;
};

size_t my_strlen(const char* str);
char* palloc(MemoryManager& memory_manager, int n);
char* prealloc(MemoryManager& memory_manager, char* p, int new_size);
void pfree(MemoryManager& memory_manager, char* p);
void init_memory_manager(MemoryManager& memory_manager, size_t size);
void destroy_memory_manager(MemoryManager& memory_manager);
void print_memory_status(MemoryManager& memory_manager);
#endif
