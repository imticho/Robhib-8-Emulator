#include "CPU.h"

CPU::CPU() {
}

CPU::~CPU() {}

uint16_t CPU::fetch() {
    uint16_t instruction = ((uint16_t)memory.read(pc) << 8) | memory.read(pc + 1);
    pc += 2;
}

void CPU::decode_and_execute(uint16_t instruction){
    int mask = 0b1111;
    int first_nibble = (instruction & (mask << 12)) >> 12;
    int second_nibble = (instruction & (mask << 8)) >> 8;
    int third_nibble = (instruction & (mask << 4)) >> 4;
    int fourth_nibble = instruction & mask;
    switch (first_nibble)
    {
    case 0x0:
        switch (fourth_nibble)
        {
        case 0x0:
            //clear screen
            break;
        case 0xE:
            pc = stack.back();
            stack.pop_back();
            break;
        default:
            break;
        }
        break;
    case 0x1:
        // set pc to 2nd,3rd,4th nibble combined since it is a 12 bit address
        pc = (second_nibble << 8) | (third_nibble << 4) | fourth_nibble;
        break;
    case 0x2:
        stack.push_back(pc);
        pc = (second_nibble << 8) | (third_nibble << 4) | fourth_nibble;
        break;
    default:
        break;
    }
}