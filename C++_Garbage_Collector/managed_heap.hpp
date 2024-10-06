#pragma once

#include <vector>

struct memory_block {
	size_t size;
	bool isFree;
	memory_block* next_block;
	void* data;
	
	memory_block(size_t s) : size(s), isFree(true), next_block(nullptr), data(nullptr) {}
	~memory_block() {
		free(data);
	}
};

class managed_heap
{
private:
	memory_block* BaseAddress;
	std::vector<memory_block*> memory_blocks;

public:
    managed_heap() = default;
    ~managed_heap() {

        for (auto block : memory_blocks) {
            delete block; 
        }
    }

    void* allocate(size_t size) {
        memory_block* block = new memory_block(size);
        memory_blocks.push_back(block);
        return block->data; // Return the pointer to the allocated data
    }

    // Function to deallocate a block (you may need to enhance this)
    void deallocate(void* ptr) {
        for (auto block : memory_blocks) {
            if (block->data == ptr) {
                block->isFree = true;
                break;
            }
        }
    }
	
};

