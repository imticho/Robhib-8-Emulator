#include <iostream>
#include "CPU.h"
#include "Monitor.h"

const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;


int main(int, char** argv){
    
    int videoScale = std::stoi(argv[1]);

    CPU cpu;
    Monitor monitor = Monitor(&cpu); 
    Display display = Display("Robhib-8 emu", CHIP8_WIDTH * videoScale, CHIP8_HEIGHT * videoScale, CHIP8_WIDTH, CHIP8_HEIGHT);
    int videoPitch = sizeof(cpu.video[0]) * CHIP8_WIDTH;

    while(true) {
        cpu.cycle();
        monitor.printRegisters();
        // std::cout<< "cycle completed!\n";
        display.Update(cpu.video, videoPitch);
        
    }
}
