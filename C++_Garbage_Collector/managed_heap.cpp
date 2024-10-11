#include "managed_heap.hpp"

namespace My_GC {
	void* managed_heap::allocate(size_t size) {
		memory_block* block = new memory_block(size);
		if (!BaseAddress) {
			BaseAddress = block;
		}

		if (LastBlock) {
			LastBlock->next_block = block;
		}

		LastBlock = block;

		memory_blocks.push_back(block);
		return block->data; // Return the pointer to the allocated data
	}

	void* managed_heap::my_malloc(size_t size) {
		for (auto block : memory_blocks) {
			if (block->isFree && block->size >= size) {
				block->isFree = false;
				return block->data;
			}
		}
		return allocate(size);
	}

	void managed_heap::my_free(void* ptr) {
	}
}