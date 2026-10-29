#ifndef IO_H
#define IO_H
#include "chip8.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

//Initialize the graphics struct
typedef struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
}Graphics;

//Initialize the audio device struct
typedef struct{
    SDL_AudioDeviceID audio_device;
    float phase;
    Chip8 *chip8;
}Audio;

//Function that initializes the graphics
bool graphics_init(Graphics *graphics, Chip8 *chip8);

//Destroys the renderer and the window
void graphics_destroy(Graphics *graphics);

//Render the graphics
void graphics_render(Graphics *graphics, Chip8 *chip8);

//Initialize the sdl audio
void audio_init(Audio *audio, Chip8 *chip8);

void audio_callback(void *userdata, Uint8 *stream, int len);

//Audio Cleanup
void audio_cleanup(Audio *audio);

#endif