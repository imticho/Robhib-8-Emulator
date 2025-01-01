
#include <vector>
#include <SDL2/SDL.h>

class Platform
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    std::vector<uint8_t> screenBitmap;
    int window_width;
    int window_height;
public:
    Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~Platform();
    void Update(void const* buffer, int pitch);
    bool processInput(char* keypad);
};


