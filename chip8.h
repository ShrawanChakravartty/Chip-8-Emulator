#ifndef CHIP8_H
#define CHIP8_H
#include <stdint.h>

//Initialize the struct
typedef struct {
    uint8_t memory[4096];
    uint16_t PC;
    uint8_t V[16];
    uint16_t stack[16];
    uint8_t SP;
    uint16_t I;
    uint8_t delay_timer;
    uint8_t sound_timer;
} Chip8;

//initialize the values to the default value
void chip8_init(Chip8 *chip8);

//Fetch the instruction from the momory
uint16_t chip8_fetch(Chip8 *chip8);

//Get the register no.
uint8_t chip8_get_register(uint16_t instruction);

//Get the value from the instruction
uint8_t chip8_get_value(uint16_t instruction);

//Execute the instruction of storing (6xnn)
void chip8_execute_6xnn(Chip8 *chip8, uint16_t instruction);

//Make the auto execute function
void chip8_execute(Chip8 *chip8, uint16_t instruction);

//Make the function to start the fetch decode execute cycle
void chip8_step(Chip8 *chip8);

//Make the instruction that adds value
void chip8_execute_7xnn(Chip8 *chip8, uint16_t instruction);

//Make the instruction for storing memory address in the I register
void chip8_execute_Annn(Chip8 *chip8, uint16_t instruction);

//Make the instruction to add the value of two registers and store it to first
void chip8_execute_8xy4(Chip8 *chip8, uint16_t instrution);

#endif