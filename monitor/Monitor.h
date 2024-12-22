#ifndef MONITOR_H
#define MONITOR_H

#include "../src/CPU.h"

class Monitor
{
private:
    CPU *cpu;
public:
    Monitor(CPU *cpu);
    ~Monitor();
    void printRegisters();
};

#endif
