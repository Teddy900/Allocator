#include "LinearAllocator.h"
#include <cstdlib> // for malloc/free
#include <iostream>

LinearAllocator::LinearAllocator(size_t size) : total_size(size), offset(0) {
    // 1. Ask the Operating System for the massive chunk of memory upfront
    start_ptr = (char*)std::malloc(total_size); 
    
    if (start_ptr == nullptr) {
        std::cerr << "Failed to allocate memory from OS!" << std::endl;
    } else {
        std::cout << "LinearAllocator initialized with " << total_size << " bytes.\n";
    }
}

LinearAllocator::~LinearAllocator() {
    // 2. Give the massive chunk back to the Operating System
    std::free(start_ptr);
    start_ptr = nullptr;
    std::cout << "LinearAllocator destroyed. Memory returned to OS.\n";
}

void* LinearAllocator::allocate(size_t size) {
    // 3. Check if we have enough space left in our block
    if (offset + size > total_size) {
        std::cerr << "Allocator Out of Memory!\n";
        return nullptr; 
    }

    // 4. Calculate the memory address to give to the user
    // (start_ptr + offset) advances the pointer by 'offset' bytes
    void* current_address = start_ptr + offset;
    
    // 5. Move our internal tracker forward so the next allocation doesn't overlap
    offset += size;

    return current_address;
}

void LinearAllocator::clear() {
    // 6. The magic of the Linear Allocator: 
    // To "free" all memory, we just reset our offset back to 0!
    // The next time someone calls allocate(), it will just overwrite the old data.
    offset = 0;
}
