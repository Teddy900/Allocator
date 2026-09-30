#pragma once
#include <cstddef>

class LinearAllocator {
private:
    char* start_ptr;   // Using char* because we can easily do pointer math (1 char = 1 byte)
    size_t total_size;
    size_t offset;     // How far into the memory block we currently are

public:
    // Constructor: Requests the total memory from the OS
    LinearAllocator(size_t size);
    
    // Destructor: Gives the memory back to the OS
    ~LinearAllocator();

    // Hands out a piece of the memory
    void* allocate(size_t size);
    
    // Resets the allocator (frees all memory at once)
    void clear(); 

    // Helper to see how much we've used
    size_t getUsedMemory() const { return offset; }
};
