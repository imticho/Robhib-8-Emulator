#include <iostream>
#include "CPU.h"
#include "Monitor.h"
#include <thread>
#include <chrono>

const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;


int main(int, char** argv){
    
    int videoScale = std::stoi(argv[1]);

    CPU cpu;
    Monitor monitor = Monitor(&cpu); 
    Display display = Display("Robhib-8 emu", CHIP8_WIDTH * videoScale, CHIP8_HEIGHT * videoScale, CHIP8_WIDTH, CHIP8_HEIGHT);
    int videoPitch = sizeof(cpu.video[0]) * CHIP8_WIDTH;
    int numCycles = 0;
    while(true) {
        monitor.printState();
        cpu.cycle();
        numCycles++;
        printf("Number of cycles: %d\n", numCycles);
        // std::cout<< "cycle completed!\n";
        display.Update(cpu.video, videoPitch);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
