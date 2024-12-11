// CPU

#include "Memory.h"
#include "Display.h"
#include <fstream>
#include <cstdint>
#include <vector>

struct Timers {
    uint8_t delay_timer; 
    uint8_t sound_timer; 
};

struct Registers {
    uint8_t V[16]; // General-purpose registers (V0 to VF)
    uint16_t I; // Index register
};


class CPU
{
private:
    Registers registers;
    std::vector<uint16_t> stack;
    Timers timers;
    Memory memory;
    unsigned int pc;
    unsigned int stack_pointer = 0;

public:
    uint32_t video[64*32];

    CPU();
    ~CPU();
    void cycle();
    uint16_t fetch();
    void decode_and_execute(uint16_t instruction);
    void LoadROM(char const* filename);
};

