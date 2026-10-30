#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "io.h"
#include "chip8.h"

int main(int argc, char* argv[]){
    //Check if arguments is passed or not
    if(argc < 2){
        printf("Please enter a Game Path after the name of the executable\n");
        return 1;
    }

    //Starts the random function
    srand(time(NULL));

    //initiate chip8 struct
    Chip8 chip8;

    //Userchoice - .boxBorder - True(Each square will have a blank border)
    Graphics graphics = {
        .window = NULL,
        .renderer = NULL,
        .boxBorder = false
    };

    //Initiate audio struct
    Audio audio = {0};

    //Initialize the Chip8 variables
    chip8_init(&chip8);

    //Initalize the sdl video and audio
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
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
    if(!chip8_load_rom(&chip8, argv[1])){
        graphics_destroy(&graphics);
        SDL_Quit();
        return 1;
    }
    printf("Successfully Loaded ROM into memory\n");

    //Initialize the sound
    audio_init(&audio, &chip8);

    //Makes an event handler for sdl
    SDL_Event sdl_event;

    //Sets the running status of the main execution loop
    bool running = true;

    //Sets the starting time of the main execution loop
    Uint32 previous_time = SDL_GetTicks();

    //Stores the accumulated time 1 sec contributes 600 and after 1000 units one instuction is executed
    Uint32 instruction_accumulator = 0;

    //Stores the accumlated tics
    Uint32 timer_accumulator = 0;

    //Main execution loop
    while(running){
        //Get the current execution ticks
        Uint32 current_time = SDL_GetTicks();
        
        //Get the ticks elapsed
        Uint32 diff = current_time - previous_time;

        //Assign the present time to the previous time
        previous_time = current_time;

        //Add to the total accumulated time
        instruction_accumulator += 600 * diff;

        //Add to the timer accumulator
        timer_accumulator += 60 * diff;

        //Check for pending events 
        while(SDL_PollEvent(&sdl_event)){

            // Cases for different pending events
            switch(sdl_event.type){

                //Pending event is quit
                case SDL_QUIT:
                    running = false;
                    break;   

                //Pending event is key is pressed
                case SDL_KEYDOWN:
                    //Check for each key press
                    switch(sdl_event.key.keysym.sym){
                        case SDLK_1:
                            chip8.keyboard[0x1] = true;
                            break;
                        case SDLK_2:
                            chip8.keyboard[0x2] = true;
                            break; 
                        case SDLK_3:
                            chip8.keyboard[0x3] = true;
                            break; 
                        case SDLK_4:
                            chip8.keyboard[0xC] = true;
                            break; 
                        case SDLK_q:
                            chip8.keyboard[0x4] = true;
                            break; 
                        case SDLK_w:
                            chip8.keyboard[0x5] = true;
                            break; 
                        case SDLK_e:
                            chip8.keyboard[0x6] = true;
                            break; 
                        case SDLK_r:
                            chip8.keyboard[0xD] = true;
                            break; 
                        case SDLK_a:
                            chip8.keyboard[0x7] = true;
                            break; 
                        case SDLK_s:
                            chip8.keyboard[0x8] = true;
                            break; 
                        case SDLK_d:
                            chip8.keyboard[0x9] = true;
                            break; 
                        case SDLK_f:
                            chip8.keyboard[0xE] = true;
                            break; 
                        case SDLK_z:
                            chip8.keyboard[0xA] = true;
                            break; 
                        case SDLK_x:
                            chip8.keyboard[0x0] = true;
                            break; 
                        case SDLK_c:
                            chip8.keyboard[0xB] = true;
                            break; 
                        case SDLK_v:
                            chip8.keyboard[0xF] = true;
                            break;
                        case SDLK_ESCAPE:
                            //Quit 
                            printf("Quiting ...\n");
                            running = false;
                            break;
                    }
                    break;
                
                //Pending event is Key is released
                case SDL_KEYUP:
                    switch(sdl_event.key.keysym.sym){
                        case SDLK_1:
                            chip8.keyboard[0x1] = false;
                            break;
                        case SDLK_2:
                            chip8.keyboard[0x2] = false;
                            break; 
                        case SDLK_3:
                            chip8.keyboard[0x3] = false;
                            break; 
                        case SDLK_4:
                            chip8.keyboard[0xC] = false;
                            break; 
                        case SDLK_q:
                            chip8.keyboard[0x4] = false;
                            break; 
                        case SDLK_w:
                            chip8.keyboard[0x5] = false;
                            break; 
                        case SDLK_e:
                            chip8.keyboard[0x6] = false;
                            break; 
                        case SDLK_r:
                            chip8.keyboard[0xD] = false;
                            break; 
                        case SDLK_a:
                            chip8.keyboard[0x7] = false;
                            break; 
                        case SDLK_s:
                            chip8.keyboard[0x8] = false;
                            break; 
                        case SDLK_d:
                            chip8.keyboard[0x9] = false;
                            break; 
                        case SDLK_f:
                            chip8.keyboard[0xE] = false;
                            break; 
                        case SDLK_z:
                            chip8.keyboard[0xA] = false;
                            break; 
                        case SDLK_x:
                            chip8.keyboard[0x0] = false;
                            break; 
                        case SDLK_c:
                            chip8.keyboard[0xB] = false;
                            break; 
                        case SDLK_v:
                            chip8.keyboard[0xF] = false;
                            break;
                    }
                    break;
            }
        }
        //Only Run when enough time has passed
        while(instruction_accumulator >= 1000){
            //Launch the cycle of fetch decode execute
            chip8_step(&chip8);

            //One instruction costs 1000 units so decrement it from the accumulator
            instruction_accumulator -= 1000;
        }
        
        //Only Decrease the delay timer and sound timer by one 60 times per second
        while(timer_accumulator >= 1000){
            if(chip8.delay_timer > 0)       chip8.delay_timer--;
             
            if(chip8.sound_timer > 0)       chip8.sound_timer--;
            
            timer_accumulator -= 1000;
        }

        //Loop the rendering engine
        graphics_render(&graphics, &chip8);
    }

    //Closes the SDL audio
    audio_cleanup(&audio);

    //Destroys the window and quits the sdl completely
    graphics_destroy(&graphics);
    SDL_Quit();

    return 0;
}
