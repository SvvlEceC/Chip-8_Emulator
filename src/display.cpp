#include "display.h"
#include "chip8.h"

static App app;

void init_SDL(){
    memset(&app, 0, sizeof(App));
    
    int rendererFlag, windowFlag;

    rendererFlag = SDL_RENDERER_ACCELERATED;

    windowFlag = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Cannot initialize: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow("Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W * SCALE, H * SCALE, windowFlag);

    if(!app.window){
        printf("Cannot open window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlag);

    if(!app.renderer){
        printf("Cannot create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}
void control_input(chip8& chip){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT:
            exit(0);
            break;

            case SDL_KEYDOWN:{
                uint8_t index = keyboard_event(event.key);
                if(index != 0xFF)
                    chip.keypad[index] = 1;
            }
            break;

            case SDL_KEYUP:{
                uint8_t index = keyboard_event(event.key);
                if(index != 0xFF)
                    chip.keypad[index] = 1;
            }
            break;
        }
    }
}

uint8_t keyboard_event(SDL_KeyboardEvent key){
    switch (key.keysym.sym)
    {
        case SDLK_1:
        return 0;
        break;

        case SDLK_2:
        return 1;
        break;

        case SDLK_3:
        return 2;
        break;

        case SDLK_4:
        return 3;
        break;

        case SDLK_q:
        return 4;
        break;

        case SDLK_w:
        return 5;
        break;

        case SDLK_e:
        return 6;
        break;

        case SDLK_r:
        return 7;
        break;

        case SDLK_a:
        return 8;
        break;

        case SDLK_s:
        return 9;
        break;

        case SDLK_d:
        return 10;
        break;

        case SDLK_f:
        return 11;
        break;

        case SDLK_z:
        return 12;
        break;

        case SDLK_x:
        return 13;
        break;

        case SDLK_c:
        return 14;
        break;

        case SDLK_v:
        return 15;
        break;
        
        default:
        return 0xFF;
        break;
    }
}
void prepare_scene(){
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}
void present_scene(chip8& chip){
    SDL_RenderClear(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    for(int i = 0; i < 64*32; i++){
        if(chip.display[i]){
            SDL_Rect rect = {i % 64 * SCALE, i / 64 * SCALE, SCALE, SCALE};
            SDL_RenderFillRect(app.renderer, &rect);
        }
    }
    SDL_RenderPresent(app.renderer);
}