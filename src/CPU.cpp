#include "CPU.h"


CPU::CPU() {
    LoadROM("../ibmlogo.ch8");
}

CPU::~CPU() {}

void CPU::LoadROM(char const* filename) {
	// Open the file as a stream of binary and move the file pointer to the end
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		// Get size of file and allocate a buffer to hold the contents
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		// Go back to the beginning of the file and fill the buffer
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		// Load the ROM contents into the Chip8's memory, starting at 0x200
		for (long i = 0; i < size; ++i)
		{
			memory.write(200 + i , buffer[i]);
		}

		// Free the buffer
		delete[] buffer;
	}
}

uint16_t CPU::fetch() {
    uint16_t instruction = ((uint16_t)memory.read(pc) << 8) | memory.read(pc + 1);
    pc += 2;
    return instruction;
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
            // clear();
            break;
        case 0xE:
            pc = stack.back();
            stack.pop_back();
            break;
        default:
            break;
        }
        break;
    case 0x1: {
        // set pc to 2nd,3rd,4th nibble combined since it is a 12 bit address
        uint16_t address = instruction & 0x0FFF;
        pc = address;
        break;
    }
    case 0x2: {
        uint16_t address = instruction & 0x0FFF;
        stack.push_back(pc);
        pc = address;
        break;
    }
    case 0x6: {
        uint8_t target_reg = (instruction & 0x0F00) >> 8;
        uint8_t value = instruction & 0x00FF;
        registers.V[target_reg] = value;
        break;
    }
    case 0x7: {
        uint8_t target_reg = (instruction & 0x0F00) >> 8;
        uint8_t value_to_add = instruction & 0x00FF;
        registers.V[target_reg] += value_to_add;
        break;
    }
    case 0xA:
        registers.I = instruction & 0x0FFF;
        break;
    case 0xD: {
        uint8_t x_reg = (instruction & 0x0F00) >> 8;
        uint8_t y_reg = (instruction & 0x00F0) >> 4;
        uint8_t n = instruction & 0x000F;
        registers.V[0xF] = 0;

        uint8_t xcoord = registers.V[x_reg] & 63;
        uint8_t ycoord = registers.V[y_reg] & 31;
        
        for (int row = registers.I; row < n; row++) {
            uint8_t spriteData = memory.read(row);
            uint32_t* screenData = &video[xcoord * ycoord];
            uint8_t mask = 0b10000000;
            while (mask) {
                if(mask & spriteData) {
                    if(*screenData == 0xFFFFFFFF) {
                        *screenData = 0x00000000;
                        registers.V[0xF] = 1;
                    } 
                    else {
                        *screenData = 0xFFFFFFFF;
                    }
                }
                screenData++;
                if(screenData == nullptr) break;
                mask = mask >> 1;
            }
            ycoord++;
            if(ycoord > 63) break;
        }
        break;
    }
    default:
        break;
    }
}

void CPU::cycle() {
    decode_and_execute(fetch());
}