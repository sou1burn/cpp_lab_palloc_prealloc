#include <stdio.h>
#include <stdlib.h>
#include "lab11.h"
#include <string.h>

#define paragraph_size 16


size_t my_strlen(const char* str) {

	size_t len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

 char* palloc(MemoryManager& memory_manager, int n) {
	
	 size_t paragraphs_needed = (n + paragraph_size - 1) / paragraph_size;
	 size_t start_bit = 0;
	 size_t consecutive_free_bits = 0;

	 for (size_t i = 0; i < memory_manager.size; ++i) {
		 if ((memory_manager.bitmap[i / (sizeof(unsigned int) * 8)] & (1U << (i % (sizeof(unsigned int) * 8)))) == 0) {
			 if (consecutive_free_bits == 0) {
				 start_bit = i;
			 }
			 ++consecutive_free_bits;

		     if (consecutive_free_bits == paragraphs_needed) {
				 for (size_t j = 0; j < paragraphs_needed; ++j) {
					 memory_manager.bitmap[(start_bit + j) / (sizeof(unsigned int) * 8)] |= (1U << ((start_bit + j) % (sizeof(unsigned int) * 8)));
				 }
				 return (char*)memory_manager.bitmap + start_bit * paragraph_size;
			 }
		 }
		 else {
			 consecutive_free_bits = 0;
		 }
	 }
	 return nullptr;
}

 char* prealloc(MemoryManager& memory_manager, char* p, int new_size) {
	 if (p < (char*)memory_manager.bitmap || p >= (char*)memory_manager.bitmap + memory_manager.size * paragraph_size) {
		 return nullptr;
	 }

	 size_t current_block_index = ((char*)p - (char*)memory_manager.bitmap) / paragraph_size;
	 size_t current_paragraphs = (current_block_index + paragraph_size - 1) / paragraph_size;

	 pfree(memory_manager, p);

	 if (new_size <= current_paragraphs * paragraph_size) {

		 return p;
	 }

	 char* new_p = palloc(memory_manager, new_size);

	 if (new_p != nullptr) {

		 size_t copy_size = new_size < current_paragraphs * paragraph_size ? new_size : current_paragraphs * paragraph_size;
		 memcpy(new_p, p, copy_size);

		 pfree(memory_manager, p);
	 }

	 return new_p;
 }


void pfree(MemoryManager& memory_manager, char* p) {

	if (p < (char*)memory_manager.bitmap || p >= (char*)memory_manager.bitmap + memory_manager.size * paragraph_size) {
		return;
	}

	size_t block_index = ((char*)p - (char*)memory_manager.bitmap) / paragraph_size;
	memory_manager.bitmap[block_index / (sizeof(unsigned int) * 8)] &= ~(1U << (block_index % (sizeof(unsigned int) * 8)));
}



void init_memory_manager(MemoryManager& memory_manager, size_t size) {

	memory_manager.size = size;
	memory_manager.bitmap = (unsigned int*)calloc((size + paragraph_size - 1) / paragraph_size / (sizeof(unsigned int) * 8), sizeof(unsigned int));
}



void destroy_memory_manager(MemoryManager& memory_manager) {

	free(memory_manager.bitmap);
	memory_manager.bitmap = NULL;
	memory_manager.size = 0;
}


void print_memory_status(MemoryManager& memory_manager) {

	printf("Memory status: \n");
	for (size_t i = 0; i < memory_manager.size; ++i) {
		unsigned int block = memory_manager.bitmap[i / sizeof(unsigned int) * 8];
		for (size_t j = 0; j < sizeof(unsigned int)* 8 && memory_manager.size; ++j, ++i) {
			printf("%c ", (block & 1U << j) ? '1' : '0');
		}
		printf("\n");
	}
	printf("\n");
}