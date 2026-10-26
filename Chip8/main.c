#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chip8.h"

int main(void){
    Chip8 chip8;

    chip8_init(&chip8);

    if(!chip8_load_rom(&chip8, "PONG")){
        return 1;
    }
    printf("Successfully Loaded ROM into memory\n");

    srand(time(NULL));

    for(int i = 0; i < 1001; i++){
        chip8_step(&chip8);
    }


    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);
    
    

    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    printf("SP = %u\n",chip8.SP);

    printf("I = 0x%03X\n",chip8.I);

    for(int i = 512; i < 800; i++ ){
        printf("Memory[0x%03X] = 0x%02X\n", i , chip8.memory[i]);
    }

    return 0;
}
