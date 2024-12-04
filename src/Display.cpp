#include "Display.h"

Display::Display(int width, int height) 
    : window(nullptr), surface(nullptr), window_width(width), window_height(height) {
    init();
}

Display::~Display() {
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::init() {
    int windowFlags = 0;

    screenBitmap = std::vector<uint8_t>((window_width * window_height) / 8, 0);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, windowFlags);

    if (!window)
    {
        printf("Failed to open %d x %d window: %s\n", window_width, window_width, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    surface = SDL_GetWindowSurface(window); // Get the window's surface
    if (!surface) {
        printf("Failed to create surface: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    return;
}

void Display::clear() {
    SDL_FillRect(surface, NULL, black);
}

int Display::getPixel(int x, int y) {
    if (x < 0 || x >= window_width || y < 0 || y >= window_height) return -1;
    int byteIndex = (y * window_width + x) / 8;
    int bitIndex = x % 8;

    return (screenBitmap[byteIndex] & (1 << (7 - bitIndex))) ? 1 : 0;
}

void Display::draw() {
    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);
    Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);

    for (int y = 0; y < window_width; ++y) {
        for (int x = 0; x < window_height; ++x) {
            SDL_Rect pixelRect = {x * 10, y * 10, 10, 10}; // Scale factor of 10
            int color = getPixel(x, y) ? white : black;
            if(color == -1) continue;
            SDL_FillRect(surface, &pixelRect, color);
        }
    }

    SDL_UpdateWindowSurface(window);
}