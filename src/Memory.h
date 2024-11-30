// memory.h

#include <cstdint>
#include <iostream>
#include <array>

using std::uint8_t;
using std::size_t;

const size_t MEMORY_SIZE = 4096;

class Memory {
    public:
        explicit Memory();

        uint8_t read(size_t offset) const;
        void write(size_t offset, uint8_t value);

    private:
        std::array<uint8_t, MEMORY_SIZE> memory;
};