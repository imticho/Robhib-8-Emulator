#include "Monitor.h"
#include <iostream>
#include <string>

Monitor::Monitor(CPU *cpu): cpu(cpu) {}

Monitor::~Monitor() {}

void Monitor::printRegisters() {
    std::cout << "Register Values:\n";
    printf("Index Register Value: 0x%X\n|", cpu->registers.I);
    for(int i = 0; i < sizeof(cpu->registers.V); i++) {
        printf(" V%X: %d |", i, cpu->registers.V[i]);
        if (i == 7) {
             std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}