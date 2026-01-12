#ifndef DISPLAY
#define DISPLAY
#include <SDL2/SDL.h>

#define W 64
#define H 32
#define SCALE 20

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_AudioDeviceID deviceId;
}App;

struct chip8;

void init_SDL(chip8& chip);
void control_input(chip8& chip);
void prepare_scene();
void present_scene(chip8& chip);
void close();
#endif