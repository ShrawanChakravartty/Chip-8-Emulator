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
    uint8_t shift_uses_vy;
} Chip8;

//Group the Instuctions type together
typedef struct{
    uint8_t type;
    uint8_t x;
    uint8_t y;
    uint8_t n;
    uint8_t nn;
    uint16_t nnn;
}Chip8Instruction;

//initialize the values to the default value
void chip8_init(Chip8 *chip8);

//Fetch the instruction from the momory
uint16_t chip8_fetch(Chip8 *chip8);

//Fetch the instruction type
Chip8Instruction chip8_decode_instruction(uint16_t instruction);

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
void chip8_execute_8xy4(Chip8 *chip8, uint16_t instruction);

//Make the subtraction instruction
void chip8_execute_8xy5(Chip8 *chip8, uint16_t instruction);

//Make the reverse subtraction instruction
void chip8_execute_8xy7(Chip8 *chip8, uint16_t instruction);

//Make the register copy instruction
void chip8_execute_8xy0(Chip8 *chip8, uint16_t instruction);

//Make the bitwise or of two register instruction
void chip8_execute_8xy1(Chip8 *chip8, uint16_t instruction);

//Make the bitwise and of two register instruction
void chip8_execute_8xy2(Chip8 *chip8, uint16_t instruction);

//Make the bitwise xor of two register instruction
void chip8_execute_8xy3(Chip8 *chip8, uint16_t instruction);

//Make the right shift instruction
void chip8_execute_8xy6(Chip8 *chip8, uint16_t instruction);

//Make the left shift instruction
void chip8_execute_8xyE(Chip8 *chip8, uint16_t instruction);

#endif