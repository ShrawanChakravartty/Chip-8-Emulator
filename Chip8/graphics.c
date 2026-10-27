#include "graphics.h"
#define TITLE "Chip - 8 Emulator"
#define scale 10

bool graphics_init(Graphics *graphics, Chip8 *chip8){
    //Height and width of the window 
    int height = (sizeof(chip8->display)/sizeof(chip8->display[0])) * scale;
    int width = (sizeof(chip8->display[0])/sizeof(chip8->display[0][0])) * scale;

    //Initialize the window
    graphics->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height,0);

    if(!graphics->window){
        printf("%s\n", SDL_GetError());
        return false;
    }

    //Assins the renderer
    graphics->renderer = SDL_CreateRenderer(graphics->window, -1, 0);

    //Check for error
    if(!graphics->renderer){
        printf("%s\n", SDL_GetError());
        return false;
    }

    //Set the drawing color of the renderer
    if(SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(graphics->renderer);
        SDL_DestroyWindow(graphics->window);
        return false;
    }

    //Clear the renderer buffer and draws into the renderer
    if(SDL_RenderClear(graphics->renderer)){
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(graphics->renderer);
        SDL_DestroyWindow(graphics->window);
        return false;
    }

    //Presents the renderer into the window
    SDL_RenderPresent(graphics->renderer);

    return true;
}

void graphics_destroy(Graphics *graphics){
    //Destroy the renderer 
    SDL_DestroyRenderer(graphics->renderer);

    //Destroy the window
    SDL_DestroyWindow(graphics->window);
}

void graphics_render(Graphics *graphics, Chip8 *chip8){
    //Height and width of the window 
    int height = (sizeof(chip8->display)/sizeof(chip8->display[0]));
    int width = (sizeof(chip8->display[0])/sizeof(chip8->display[0][0]));

    //Clear the screen
    if(SDL_SetRenderDrawColor(graphics->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)){
        printf("%s\n", SDL_GetError());
        return;
    }
    if(SDL_RenderClear(graphics->renderer)){
        printf("%s\n", SDL_GetError());
        return;
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //Make a rectangle for the cordinate 
            SDL_Rect rect = {j * scale, i * scale, scale, scale};

            //Make the rectangle
            if(chip8->display[i][j]){
                //Change the draw color to white and check for errors
                if(SDL_SetRenderDrawColor(graphics->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE)){
                    printf("%s\n", SDL_GetError());
                    return;
                }

                //Fill the display according to the rectangle
                if(SDL_RenderFillRect(graphics->renderer, &rect)){
                    printf("%s\n", SDL_GetError());
                    return;
                }
            }
        }
    }
    //Presents the renderer into the window
    SDL_RenderPresent(graphics->renderer);
}

