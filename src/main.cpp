#include <cstdlib>
#include "display.h"
#include "chip8.h"

int main(int argc, char const *argv[]){
    chip8 chip;

    init_SDL();

    while (1)
    {
        chip.cpu.decode_and_execute(chip, chip.cpu.fetch(chip.ram));
        
        prepare_scene();

        control_input();
        
        if(chip.update_display)
            present_scene();
    }
    

    return 0;
}
