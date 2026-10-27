#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "chip8.h"

int main(void){
    Chip8 chip8;

    Graphics graphics = {
        .window = NULL,
        .renderer = NULL
    };

    chip8_init(&chip8);

    //Start the sdl init
    if(SDL_Init(SDL_INIT_VIDEO)){
        printf("%s\n", SDL_GetError());
        return 1;
    }

    //Prepare the window for further updation
    if(!graphics_init(&graphics, &chip8)){
        graphics_destroy(&graphics);
        SDL_Quit();
        return 1;
    }

    //loads the rom and in case of failure closes everything
    if(!chip8_load_rom(&chip8, "ROMS/PONG")){
        graphics_destroy(&graphics);
        SDL_Quit();
        return 1;
    }
    printf("Successfully Loaded ROM into memory\n");

    //Starts the random function
    srand(time(NULL));

    //Makes an event handler for sdl
    SDL_Event sdl_event;

    //Sets the running status of the main execution loop
    bool running = true;

    //Sets the starting time of the main execution loop
    Uint32 previous_time = SDL_GetTicks();

    //Main execution loop
    while(running){
        //Get the current execution ticks
        Uint32 current_time = SDL_GetTicks();
        
        //Get the ticks elapsed
        Uint32 diff = current_time - previous_time;

        //Assign the present time to the previous time
        previous_time = current_time;

        //Check for pending events 
        while(SDL_PollEvent(&sdl_event)){

            // Cases for different pending events
            switch(sdl_event.type){

                //Pending event is quit
                case SDL_QUIT:
                    running = false;
                    break;   
            }
        }
        //Launch the cycle of fetch decode execute
        chip8_step(&chip8);

        //Loop the rendering engine
        graphics_render(&graphics, &chip8);
    }


    //Destroys the window and quits the sdl completely
    graphics_destroy(&graphics);
    SDL_Quit();

    return 0;
}
