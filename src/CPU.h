// CPU

#include "Memory.h"
#include "Display.h"
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
    Display display = Display(64, 32);
    unsigned int pc= 0;
    unsigned int stack_pointer = 0;

public:
    CPU();
    ~CPU();
    uint16_t fetch();
    void decode_and_execute(uint16_t instruction);
};

