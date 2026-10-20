#include <stdio.h>
#include "chip8.h"

int main(void){
    Chip8 chip8;

    chip8_init(&chip8);

    chip8.memory[0x200] = 0x63;
    chip8.memory[0x201] = 0x81;
    chip8.memory[0x202] = 0x64;
    chip8.memory[0x203] = 0x07;
    chip8.memory[0x204] = 0x83;
    chip8.memory[0x205] = 0x4E;
    

    {
    // Previous Tests
    

    //Print Program counter
    // printf("PC = 0x%03X\n", chip8.PC);

    // //Print Index register
    // printf("The index register value is %u\n", chip8.I);
    
    // //Print the stack pointer
    // printf("the stack pointer value is %u\n", chip8.SP);

    // //Print Delay timer
    // printf("The Delay timer value is %u\n", chip8.delay_timer);

    // //Print the sound timer 
    // printf("The sound timer is %u\n", chip8.sound_timer);

    // //Print the value of the V[0] register
    // printf("The value of the V[0] register is %u\n", chip8.V[0]);

    // //Fetch the instruction
    // // uint16_t instruction = chip8_fetch(&chip8);

    // //Print the Instruction
    // printf("The instruction : 0x%04X\n", (unsigned int)instruction);

    // //Print Program counter again
    // printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    // // //Print the register no. 
    // // printf("Register number: %u\n", (unsigned int)chip8_get_register(instruction));

    // // //Print the Value 
    // // printf("Value : %u\n", (unsigned int)chip8_get_value(instruction));

    // //Execute 6xnn instruction and get the value in the register
    // // chip8_execute_6xnn(&chip8, instruction);

    // //Execute using the execute function
    // // chip8_execute(&chip8, instruction);

    // printf("V[%u] = %u\n", (unsigned int)chip8_get_register(instruction), (unsigned int)chip8.V[chip8_get_register(instruction)]);
    
    // printf("V[3] = %u\n", (unsigned int)chip8.V[3]);

    // printf("Value of I register 0x%03X\n", (unsigned int)chip8.I);

    // printf("Value of Register V[F] = %u\n",chip8.V[0xF]);
    }
    
    while(chip8.PC < 0x206){
        chip8_step(&chip8);
    }

    //Print Program counter again
    printf("PC = 0x%03X\n", (unsigned int)chip8.PC);

    printf("Value of Register V[3] = %u\n",chip8.V[0x3]);
    printf("Value of Register V[4] = %u\n",chip8.V[0x4]);
    printf("Value of Register V[F] = %u\n",chip8.V[0xF]);

    return 0;
}
