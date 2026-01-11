#ifndef DISPLAY
#define DISPLAY
#include <SDL2/SDL.h>

#define W 64
#define H 32
#define SCALE 20

typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
}App;

void init_SDL();
void control_input();
void prepare_scene();
void present_scene();
#endif