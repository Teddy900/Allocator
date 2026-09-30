#include <iostream>
#include "LinearAllocator.h"

int main() {
    // 1. Create our custom allocator with 1024 bytes (1 KB) of memory capacity
    std::cout << "--- Starting Program ---\n";
    LinearAllocator allocator(1024);

    // 2. Allocate memory for an array of 10 integers (10 * 4 bytes = 40 bytes)
    std::cout << "\nAllocating 10 ints...\n";
    int* myIntArray = (int*)allocator.allocate(10 * sizeof(int));
    
    if (myIntArray != nullptr) {
        // Prove that the memory works by using it
        for(int i = 0; i < 10; ++i) {
            myIntArray[i] = i * 10;
        }
        std::cout << "First element: " << myIntArray[0] << ", Last element: " << myIntArray[9] << "\n";
    }
    std::cout << "Memory used so far: " << allocator.getUsedMemory() << " bytes\n";

    // 3. Allocate memory for a single double (8 bytes)
    std::cout << "\nAllocating a double...\n";
    double* myDouble = (double*)allocator.allocate(sizeof(double));
    
    if (myDouble != nullptr) {
        *myDouble = 3.14159;
        std::cout << "Double value: " << *myDouble << "\n";
    }
    std::cout << "Memory used so far: " << allocator.getUsedMemory() << " bytes\n";

    // 4. Reset the allocator (frees everything instantly)
    std::cout << "\nClearing allocator...\n";
    allocator.clear();
    std::cout << "Memory used after clear: " << allocator.getUsedMemory() << " bytes\n\n";

    return 0; // When main ends, the allocator's destructor is automatically called
}
