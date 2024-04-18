#include <stdio.h>
#include "lab11.h"
#include <stdlib.h>
#include <iostream>

#define paragraph_size 16
//добавить функцию перевыделения памяти в header

int main() {


	MemoryManager memory_manager;
	int size;
	std::cout << "Enter size of memory manager: ";
	std::cin >> size;
	
	if (size < 0) {	
		std::cout << "Oops, wrong input\n";
		return 0;
	}

	init_memory_manager(memory_manager, size);

	print_memory_status(memory_manager);
	
	char* ptr1 = palloc(memory_manager, 11);
	char* ptr2 = palloc(memory_manager, 6);
	char* ptr3 = palloc(memory_manager, 14);

	if (ptr1 != NULL && ptr2 != NULL && ptr3 !=  NULL) {

		printf("Memory allocated succesfully\n\n");

		print_memory_status(memory_manager);
		pfree(memory_manager, ptr1);
		print_memory_status(memory_manager);
		/*prealloc(memory_manager, ptr2, 1);
		printf("Memory reallocated\n");
		*/
		print_memory_status(memory_manager);
		pfree(memory_manager, ptr2);
		print_memory_status(memory_manager);
		pfree(memory_manager, ptr3);
		printf("Memory freed succesfully\n\n");
		print_memory_status(memory_manager);
	}
	else {
		printf("Memory allocating failed");
	}

	destroy_memory_manager(memory_manager);
	return 0;
}