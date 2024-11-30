#include <iostream>
#include "Memory.h"

int main(int, char**){
    Memory memory;
    memory.write(0, 3);
    std::cout << int(memory.read(0)) << std::endl;
}
