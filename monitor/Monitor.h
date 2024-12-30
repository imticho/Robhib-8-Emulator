#ifndef MONITOR_H
#define MONITOR_H

#include "../src/CPU.h"

class Monitor
{
private:
    CPU *cpu;
    int numJumps= 0;
    
public:
    Monitor(CPU *cpu);
    ~Monitor();
    void printRegisters();
    void printCurrentInstr();
    void printState();
    uint8_t getInstructionType();
    void printVideoBuffer();

};

#endif
