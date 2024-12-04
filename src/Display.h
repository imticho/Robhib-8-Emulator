
#include <vector>
#include <SDL2/SDL.h>

class Display
{
private:
    SDL_Window* window;
    SDL_Surface* surface;
    uint32_t black = SDL_MapRGB(surface->format, 0, 0, 0);
    uint32_t white = SDL_MapRGB(surface->format, 255, 255, 255);
    std::vector<uint8_t> screenBitmap;
    const int window_width;
    const int window_height;
public:
    Display(int width, int height);
    ~Display();

    void init();
    void clear();
    int getPixel(int x, int y);
    void draw();
};


