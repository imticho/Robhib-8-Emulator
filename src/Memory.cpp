#include "Memory.h"
#include <stdexcept>

Memory::Memory() {
    memory.fill(0);
}

uint8_t Memory::read(size_t address) const {
    if (address >= memory.size()) {
        throw std::out_of_range("Memory read out of bounds");
    }
    return memory[address];
}

void Memory::write(size_t address, uint8_t value) {
    if (address >= memory.size()) {
        throw std::out_of_range("Memory write out of bounds");
    }
    memory[address] = value;
}