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

    chip8.memory[0x300] = 0xF0;
    chip8.memory[0x200] = 0xA3;
    chip8.memory[0x201] = 0x00;
    chip8.memory[0x202] = 0x61;
    chip8.memory[0x203] = 0x0A;
    chip8.memory[0x204] = 0x62;
    chip8.memory[0x205] = 0x05;
    chip8.memory[0x206] = 0xD1;
    chip8.memory[0x207] = 0x21;
    chip8.memory[0x208] = 0xD1;
    chip8.memory[0x209] = 0x21;

    
    chip8_step(&chip8);
    chip8_step(&chip8);
    chip8_step(&chip8);
    chip8_step(&chip8);

    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64 ; j++){
            if(chip8.display[i][j])     printf("1");
            else                        printf("0");
        }
        printf("\n");
    }
    printf("V[F] = %u\n", (unsigned int)chip8.V[0xF]);
    chip8_step(&chip8);

    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64 ; j++){
            if(chip8.display[i][j])     printf("1");
            else                        printf("0");
        }
        printf("\n");
    }
    printf("V[F] = %u\n", (unsigned int)chip8.V[0xF]);


    return 0;
}
