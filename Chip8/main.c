#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chip8.h"

int main(void){
    Chip8 chip8;

    chip8_init(&chip8);

    srand(time(NULL));


    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    chip8.memory[0x200] = 0x61;
    chip8.memory[0x201] = 0xAA;
    chip8.memory[0x202] = 0xF1;
    chip8.memory[0x203] = 0x18;

    
    chip8_step(&chip8);
    chip8_step(&chip8);

    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    // printf("Value of Register V[1] = %u\n",chip8.V[0x1]);
    printf("The sound timer is %u\n", (unsigned int)chip8.sound_timer);

    return 0;
}
