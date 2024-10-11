#pragma once

#include <vector>

namespace My_GC {
	struct memory_block {
		size_t size;
		bool isFree;
		memory_block* next_block;
		void* data;

		memory_block(size_t s) : size(s), isFree(true), next_block(nullptr), data(malloc(s)) {}
		~memory_block() {
			free(data);
		}
	};

	class managed_heap
	{
	private:
		memory_block* BaseAddress;
		memory_block* LastBlock;
		std::vector<memory_block*> memory_blocks;

		void* allocate(size_t size);

	public:
		managed_heap() = default; //Default constructor
		~managed_heap() {
			for (auto block : memory_blocks) {
				delete block;
			}
		}

		void* my_malloc(size_t size);

		void my_free(void* ptr);
	};
}