#include "Platform.h"
#include <chrono>
#include <thread>

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
    window_width = windowWidth;
    window_height = windowHeight;
    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

Platform::~Platform()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Platform::Update(void const* buffer, int pitch)
{
    SDL_PumpEvents();
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Platform::processInput(char* keypad) {
    bool quit = false;
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_1:
                keypad[0x1] = 1;
                break;
            case SDL_SCANCODE_2:
                keypad[0x2] = 1;
                break;
            case SDL_SCANCODE_3:
                keypad[0x3] = 1;
                break;
            case SDL_SCANCODE_4:
                keypad[0xC] = 1;
                break;
            case SDL_SCANCODE_Q:
                keypad[0x4] = 1;
                break;
            case SDL_SCANCODE_W:
                keypad[0x5] = 1;
                break;
            case SDL_SCANCODE_E:
                keypad[0x6] = 1;
                break;
            case SDL_SCANCODE_R:
                keypad[0xD] = 1;
                break;
            case SDL_SCANCODE_A:
                keypad[0x7] = 1;
                break;
            case SDL_SCANCODE_S:
                keypad[0x8] = 1;
                break;
            case SDL_SCANCODE_D:
                keypad[0x9] = 1;
                break;
            case SDL_SCANCODE_F:
                keypad[0xE] = 1;
                break;
            case SDL_SCANCODE_Z:
                keypad[0xA] = 1;
                break;
            case SDL_SCANCODE_X:
                keypad[0x0] = 1;
                break;
            case SDL_SCANCODE_C:
                keypad[0xB] = 1;
                break;
            case SDL_SCANCODE_V:
                keypad[0xF] = 1;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return quit;
}
