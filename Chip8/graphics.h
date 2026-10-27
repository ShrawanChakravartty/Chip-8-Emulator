#ifndef Graphics_H
#define Graphics_H
#include "chip8.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

//Initialize the graphics struct
typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
}Graphics;

//Function that initializes the graphics
bool graphics_init(Graphics *graphics, Chip8 *chip8);

//Destroys the renderer and the window
void graphics_destroy(Graphics *graphics);

//Render the graphics
void graphics_render(Graphics *graphics, Chip8 *chip8);

#endif