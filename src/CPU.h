// CPU

#include "Memory.h"
#include <vector>

struct Timers {
    uint8_t delay_timer; 
    uint8_t sound_timer; 
};

struct Registers {
    union {
        struct {
            uint8_t V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF;
        };
        std::array<uint8_t, 16> V; // Variable Registers
    };
    uint16_t I; // Index register
};


class CPU
{
private:
    Registers registers;
    std::vector<uint16_t> stack;
    Timers timers;

public:
    CPU(/* args */);
    ~CPU();
};

CPU::CPU(/* args */)
{
}

CPU::~CPU()
{
}
