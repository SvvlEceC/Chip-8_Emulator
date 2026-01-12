#include "display.h"
#include "chip8.h"

static App app;

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

void close(){
    if(app.deviceId > 0)
        SDL_CloseAudioDevice(app.deviceId);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

void audio_callback(void* userdata, Uint8* stream, int len){
    static uint32_t running_time = 0;
    const int frequency = 44100;
    const int beep_freq = 440;
    const int volume = 3000;

    int16_t* buffer = (int16_t*)stream;
    int samples = len / sizeof(int16_t);

    if(((chip8*)userdata)->sound_timer.get() > 0){
        for(int i = 0; i < samples; i++){
            if(!((running_time++ / (frequency / (beep_freq * 2))) % 2)){
                *(buffer + i) = volume;
            }
            else{
                *(buffer + i) = -volume;
            }
        }    
    }
    else{
        memset(stream, 0, len);
    }

}

void init_SDL(chip8& chip){
    memset(&app, 0, sizeof(App));

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Cannot initialize: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_AudioSpec want, have;

    want.freq = 44100;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = 4096;
    want.callback = audio_callback;
    want.userdata = &chip;


    
    app.deviceId = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);

    if (app.deviceId == 0) {
        printf("Unable to create sound device: %s\n", SDL_GetError());
    } else {
        SDL_PauseAudioDevice(app.deviceId, 0);
    }
    
    int rendererFlag, windowFlag;

    rendererFlag = SDL_RENDERER_ACCELERATED;

    windowFlag = 0;


    app.window = SDL_CreateWindow("Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W * SCALE, H * SCALE, windowFlag);

    if(!app.window){
        printf("Cannot open window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
                    chip.keypad[index] = 0;
            }
            break;
        }
    }
}