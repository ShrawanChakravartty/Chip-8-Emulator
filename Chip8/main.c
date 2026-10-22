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

    chip8.memory[0x200] = 0xC1;
    chip8.memory[0x201] = 0x0F;

    
    chip8_step(&chip8);

    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    printf("Value of Register V[1] = %u\n",chip8.V[0x1]);

    return 0;
}
