#include <iostream>
#include "Memory.h"

int main(int, char**){
    Memory memory;
    for (int i = 80; i < 160; i ++) {
        std::cout << std::hex << static_cast<int>(memory.read(i)) << " ";
    }
}
