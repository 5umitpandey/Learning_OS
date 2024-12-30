#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure for memory blocks
struct MemoryBlock {
    int size;
    bool allocated;
    int startAddr;
};

class MemoryManager {
private:
    vector<MemoryBlock> memory;
    int totalSize;

public:
    // Constructor initializes memory with a single large free block
    MemoryManager(int size) : totalSize(size) {
        memory.push_back({size, false, 0}); // Entire memory block is initially free
    }

    // Display current memory status
    void displayMemory() {
        cout << "\nMemory Status:\n";
        for (const auto& block : memory) {
            cout << "Start Address: " << block.startAddr
                 << ", Size: " << block.size
                 << ", " << (block.allocated ? "Allocated" : "Free") << "\n";
        }
    }

    // First Fit Allocation Strategy
    void firstFit(int reqSize) {
        for (auto& block : memory) {
            if (!block.allocated && block.size >= reqSize) {
                allocateBlock(block, reqSize);
                return;
            }
        }
        cout << "No suitable block found for First Fit allocation.\n";
    }

    // Best Fit Allocation Strategy
    void bestFit(int reqSize) {
        auto bestBlock = memory.end();
        for (auto it = memory.begin(); it != memory.end(); ++it) {
            if (!it->allocated && it->size >= reqSize &&
                (bestBlock == memory.end() || it->size < bestBlock->size)) {
                bestBlock = it;
            }
        }

        if (bestBlock != memory.end()) {
            allocateBlock(*bestBlock, reqSize);
        } else {
            cout << "No suitable block found for Best Fit allocation.\n";
        }
    }

    // Worst Fit Allocation Strategy
    void worstFit(int reqSize) {
        auto worstBlock = memory.end();
        for (auto it = memory.begin(); it != memory.end(); ++it) {
            if (!it->allocated && it->size >= reqSize &&
                (worstBlock == memory.end() || it->size > worstBlock->size)) {
                worstBlock = it;
            }
        }

        if (worstBlock != memory.end()) {
            allocateBlock(*worstBlock, reqSize);
        } else {
            cout << "No suitable block found for Worst Fit allocation.\n";
        }
    }

    // Allocate a block and split if necessary
    void allocateBlock(MemoryBlock& block, int reqSize) {
        int startAddress = block.startAddr;
        block.allocated = true;
        if (block.size > reqSize) {
            memory.insert(find(memory.begin(), memory.end(), block) + 1,
                          {block.size - reqSize, false, startAddress + reqSize});
            block.size = reqSize;
        }
        cout << "Memory block of size " << reqSize << " allocated at address " << startAddress << ".\n";
    }

    // Free a block at a specific start address
    void freeBlock(int startAddr) {
        for (auto& block : memory) {
            if (block.startAddr == startAddr && block.allocated) {
                block.allocated = false;
                cout << "Block at address " << startAddr << " has been freed.\n";
                mergeFreeBlocks();
                return;
            }
        }
        cout << "No allocated block found at the given address.\n";
    }

    // Merge consecutive free blocks
    void mergeFreeBlocks() {
        for (auto it = memory.begin(); it != memory.end() - 1; ++it) {
            if (!it->allocated && !(it + 1)->allocated) {
                it->size += (it + 1)->size;
                memory.erase(it + 1);
                --it;
            }
        }
    }
};

int main() {
    int initialSize;
    cout << "Enter the total memory size: ";
    cin >> initialSize;
    MemoryManager memoryManager(initialSize);

    int choice, reqSize, startAddr;
    while (true) {
        cout << "\nMemory Allocation Menu:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Free a Block\n";
        cout << "5. Display Memory Status\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the size of memory to allocate: ";
                cin >> reqSize;
                memoryManager.firstFit(reqSize);
                break;
            case 2:
                cout << "Enter the size of memory to allocate: ";
                cin >> reqSize;
                memoryManager.bestFit(reqSize);
                break;
            case 3:
                cout << "Enter the size of memory to allocate: ";
                cin >> reqSize;
                memoryManager.worstFit(reqSize);
                break;
            case 4:
                cout << "Enter the start address of the block to free: ";
                cin >> startAddr;
                memoryManager.freeBlock(startAddr);
                break;
            case 5:
                memoryManager.displayMemory();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
