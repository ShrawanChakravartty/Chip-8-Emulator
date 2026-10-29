#include "io.h"
#include <string.h>
#define TITLE "Chip - 8 Emulator"
#define scale 10
#include <stdatomic.h>

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

void audio_init(Audio *audio, Chip8 *chip8){
    audio->chip8 = chip8;

    //descibe the audiospec
    SDL_AudioSpec spec = {
        .freq = 44100,
        .channels = 1,
        .format = AUDIO_F32SYS,
        .samples = 128, 
        .callback = audio_callback,
        .userdata = audio
    };
    //For reporitng back
    SDL_AudioSpec obtained;

    //Open the audio device with the specific configuration
    audio->audio_device = SDL_OpenAudioDevice(NULL, 0, &spec, &obtained, 0);

    //check for error
    if(!audio->audio_device){
        printf("%s\n", SDL_GetError());
        return;
    }

    //Unpause the audio
    SDL_PauseAudioDevice(audio->audio_device, 0);
}

void audio_callback(void *userdata, Uint8 *stream, int len){
    //Setting every byte to zero
    memset(stream, 0, len);

    //Get access to the sound timer
    Audio *audio = (Audio *)userdata;
    
    //Condition to play sound
    if(audio->chip8->sound_timer > 0){

        float* buffer = (float*)stream;

        int sample_count = len / sizeof(float);

        for(int i = 0; i < sample_count; i++){
            audio->phase = audio->phase + (440.0f / 44100.0f);
            if(audio->phase >= 1.0f)     audio->phase -= 1.0f;

            if(audio->phase < 0.5f){
                buffer[i] = 0.25f;
            }
            else{
                buffer[i] = -0.25f;
            }
        }
    }
    else    memset(stream, 0, len);
}

void audio_cleanup(Audio *audio){
    //Closes the audiodevice
    if(audio->audio_device != 0)     SDL_CloseAudioDevice(audio->audio_device);
    
    //Sets the audio device to 0
    audio->audio_device = 0;
}
