#include "Monitor.h"
#include <iostream>
#include <string>

Monitor::Monitor(CPU *cpu): cpu(cpu) {
    for(int i = 0; i <= 0xF; i++) {
        static_assert(sizeof(cpu->registers.V[i]) == 1, "V registers are not 8 bits wide!");
    }
}

Monitor::~Monitor() {}

void Monitor::printRegisters() {
    std::cout << "Register Values:\n";
    printf("Index Register Value: 0x%04X\n|", cpu->registers.I);
    for(int i = 0; i < sizeof(cpu->registers.V); i++) {
        printf(" V%X: %d |", i, cpu->registers.V[i]);
        if (i == 7) {
             std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void Monitor::printCurrentInstr() {
    printf("pc = %04X : Instruction: 0x%02X%02X\n", cpu->pc, cpu->memory.read(cpu->pc), cpu->memory.read(cpu->pc +1));
}

void Monitor::printState() {
    printCurrentInstr();
    printRegisters();
    if(getInstructionType() == 0xD) {
        // printVideoBuffer();
    }
    if(getInstructionType() == 0x1) {
        numJumps+=1;
    }
    printf("Number of Jumps: %d\n", numJumps);
    if(cpu->pc == 0x049C) {
        printf("Finished VX test\n");
    }
}

uint8_t Monitor::getInstructionType(){
    uint8_t type = cpu->memory.read(cpu->pc) >> 4;
    return type;
}

void Monitor::printVideoBuffer() {
    for(int i = 0; i < 32; i++) {
        for (int j = 0; j < 64; j++) {
            std::cout << (cpu->video[i * 64 + j] ? "1" : "0");
        }
        std::cout << std::endl;
    }
}