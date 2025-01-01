#include "CPU.h"
#include <algorithm>


CPU::CPU() {
    LoadROM("../5-quirks.ch8");
    // for(int i = 0; i < 334; i++) {
    //     printf("Memory at %i: 0x%X\n",i, memory.read(i));
    // }
    std::fill(std::begin(video), std::end(video), 0);
    std::fill(std::begin(registers.V), std::end(registers.V), 0);
    registers.I = 0;
    pc = 0x200;
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
			memory.write(0x200 + i , buffer[i]);
		}

		// Free the buffer
		delete[] buffer;
	}
}

uint16_t CPU::fetch() {
    uint16_t firstHalf = 0 | memory.read(pc);
    firstHalf = firstHalf << 8;

    uint16_t instruction = firstHalf | memory.read(pc + 1);
    pc += 2;
    return instruction;
}

void CPU::decode_and_execute(uint16_t instruction){
    // printf("Instruction: 0x%X\n", instruction);
    if(instruction == 0x00E0) {
        std::cout << "read first instruction correctly\n";
    }
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
            std::fill(std::begin(video), std::end(video), 0);
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
    case 0x3: {
        uint8_t target_reg = (instruction & 0x0F00) >> 8;
        uint8_t value = instruction & 0x00FF;
        if (registers.V[target_reg] == value) pc += 2;
        break;
    }
    case 0x4: {
        uint8_t target_reg = (instruction & 0x0F00) >> 8;
        uint8_t value = instruction & 0x00FF;
        if (registers.V[target_reg] != value) pc += 2;
        break;
    }
    case 0x5: {
        uint8_t x_reg = (instruction & 0x0F00) >> 8;
        uint8_t y_reg = (instruction & 0x00F0) >> 4;
        if (registers.V[x_reg] == registers.V[y_reg]) pc += 2;
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
    case 0x8: {
        uint8_t x_reg = (instruction & 0x0F00) >> 8;
        uint8_t y_reg = (instruction & 0x00F0) >> 4;
        switch (fourth_nibble)
        {
        case 0x0:
            registers.V[x_reg] = registers.V[y_reg];
            break;
        case 0x1:
            registers.V[x_reg] = registers.V[x_reg] | registers.V[y_reg];
            break;
        case 0x2:
            registers.V[x_reg] = registers.V[x_reg] & registers.V[y_reg];
            break;
        case 0x3:
            registers.V[x_reg] = registers.V[x_reg] ^ registers.V[y_reg];
            break;
        case 0x4: {
            int tempSum = int(registers.V[x_reg]) + int(registers.V[y_reg]);
            registers.V[x_reg] = tempSum & 0xFF;
            if(tempSum > 0xFF) {
                registers.V[0xF] = 1;
            }
            else {
                registers.V[0xF] = 0;
            }
            break;
        }
        case 0x5: {
            uint8_t temp = (registers.V[x_reg] >= registers.V[y_reg]) ? 1:0;
            if(temp) {
                registers.V[x_reg] -= registers.V[y_reg];
            }
            else {
                registers.V[x_reg] = (registers.V[x_reg] - registers.V[y_reg]) & 0xFF;
            }
            registers.V[0xF] = temp;
            break;
        }
        case 0x6: {
            uint8_t bitShifted;
            if(registers.V[x_reg] & 0b1) {
                bitShifted = 1;
            }
            else {
                bitShifted = 0;
            }
            registers.V[x_reg] = registers.V[x_reg] >> 1;
            registers.V[0xF] = bitShifted;
            break;
        }
        case 0x7: {
            uint8_t temp = (registers.V[y_reg] >= registers.V[x_reg]) ? 1:0;
            if(temp) {
                registers.V[x_reg] = registers.V[y_reg] - registers.V[x_reg];
            }
            else {
                registers.V[x_reg] = (registers.V[y_reg] - registers.V[x_reg]) & 0xFF;
            }
            registers.V[0xF] = temp;
            break;
        }
        case 0xE: {
            int temp = registers.V[x_reg];
            registers.V[x_reg] = registers.V[x_reg] << 1;
            if(temp & 0x80u) {
                registers.V[0xF] = 1;
            }
            else {
                registers.V[0xF] = 0;
            }

            break;
        }
        default:
            break;
        }
        break;
    }
    case 0x9: {
        uint8_t x_reg = (instruction & 0x0F00) >> 8;
        uint8_t y_reg = (instruction & 0x00F0) >> 4;
        if (registers.V[x_reg] != registers.V[y_reg]) pc += 2;
        break;
    }
    case 0xA: {
        uint16_t address = instruction & 0x0FFF;
        registers.I = address;
        break;
    }
    case 0xB: {
        uint16_t address = instruction & 0x0FFF;
        uint8_t x_reg = second_nibble;
        pc = address + registers.V[x_reg];
        break;
    }
    case 0xC: {
        uint8_t x_reg = second_nibble;
        uint8_t value = instruction & 0x00FF;
        uint8_t randbyte = random();
        registers.V[x_reg] = randbyte & value;
        break;
    }
    case 0xD: {
        uint8_t x_reg = (instruction & 0x0F00) >> 8;
        uint8_t y_reg = (instruction & 0x00F0) >> 4;
        uint8_t n = instruction & 0x000F;
        registers.V[0xF] = 0;
        uint8_t xcoord = registers.V[x_reg] & 63;
        uint8_t ycoord = registers.V[y_reg] & 31;
        
        for (int row = 0; row < n; row++) {
            uint8_t spriteData = memory.read(row + registers.I);
            uint8_t mask = 0b10000000;
            for (int col = 0; col < 8; col++) {
                uint8_t spritePixel = spriteData & (mask >> col); 
                uint32_t* screenData = &video[(ycoord + row) * 64 + (xcoord + col)];
                if(spritePixel) {
                    if (*screenData == 0xFFFFFFFF) {
                        registers.V[0xF] = 1;
                        *screenData = 0;
                    }
				    else {
                        *screenData = 0xFFFFFFFF;
                    }
                }
            }
        }
        break;
    }
    case 0xF: {
        uint8_t vx = second_nibble;
        uint8_t lastByte = (third_nibble << 4) | fourth_nibble;
        switch (lastByte)
        {
        case 0x1E:
            registers.I += registers.V[vx];
            break;
        case 0x33: {
            uint8_t value = registers.V[vx];
            memory.write(registers.I, value / 100);          // Hundreds digit
            memory.write(registers.I + 1, (value / 10) % 10); // Tens digit
            memory.write(registers.I + 2, value % 10);       // Ones digit
            break;
        }
        case 0x55:
            for (int i = 0; i <= vx; i++) {
                memory.write(registers.I + i, registers.V[i]);
            } 
            break;
        case 0x65:
            for (int i = 0; i <= vx; i++) {
                registers.V[i] = memory.read(registers.I + i);
            } 
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
}

void CPU::cycle() {
    decode_and_execute(fetch());
}