#include <iostream>
#include "CPU.h"
#include "Platform.h"
#include "Monitor.h"
#include <thread>
#include <chrono>

const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;


int main(int, char** argv){
    
    int videoScale = std::stoi(argv[1]);

    CPU cpu;
    Monitor monitor = Monitor(&cpu); 
    Platform platform = Platform("Robhib-8 emu", CHIP8_WIDTH * videoScale, CHIP8_HEIGHT * videoScale, CHIP8_WIDTH, CHIP8_HEIGHT);
    int videoPitch = sizeof(cpu.video[0]) * CHIP8_WIDTH;
    int numCycles = 0;
    bool quit = false;
    auto lastTime = std::chrono::steady_clock::now();
    double accumulator = 0.0;
    const double targetTimePerCycle = 16.67;  // 60 Hz -> 16.67ms per timer update
    const double cpuCycleTime = 2.0;  // 500 Hz CPU -> 2ms per CPU cycle

    while(!quit) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        
        accumulator += elapsedTime.count() * 1000.0;  // Convert to milliseconds
        // Update timers
        while (accumulator >= targetTimePerCycle) {
            if (cpu.timers.delay_timer > 0) {
                cpu.timers.delay_timer--;
            }

            if (cpu.timers.sound_timer > 0) {
                cpu.timers.sound_timer--;
            }

            accumulator -= targetTimePerCycle;  // Decrement the accumulator by the target cycle time
        }

        monitor.printState();
        cpu.cycle();
        numCycles++;
        printf("Number of cycles: %d\n", numCycles);
        // std::cout<< "cycle completed!\n";
        platform.Update(cpu.video, videoPitch);
        quit = platform.processInput(cpu.keypad);
        std::this_thread::sleep_for(std::chrono::microseconds(1515));
    }
}
