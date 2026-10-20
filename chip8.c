#include "chip8.h"

void chip8_init(Chip8 *chip8){
    // TODO 1: Set every memory byte to zero.
    int size = sizeof(chip8->memory) / sizeof(chip8->memory[0]);
    for(int i = 0; i < size; i++){
        chip8->memory[i] = 0;
    }
    
    // TODO 2: Set the program counter to 0x200.
    chip8->PC = 0x200;
    
    // TODO 3: Set the register byte to zero
    int reg = sizeof(chip8->V) / sizeof(chip8->V[0]);
    for(int i = 0; i < reg; i++){
        chip8->V[i] = 0;
    }
    
    // TODO 4: Set every address of stack to 0
    int stSize = sizeof(chip8->stack) / sizeof(chip8->stack[0]);
    for(int i = 0; i < stSize; i++){
        chip8->stack[i] = 0;
    }
    
    // TODO 5; set the stack pointer to 0
    chip8->SP = 0;

    // TODO 6 : Set I register to 0
    chip8->I = 0;

    // TODO 7: Set delay and sound timer to 0
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;

    //Initialise the configurable instuction 0x8xy6
    chip8->shift_uses_vy = 0;

}

uint16_t chip8_fetch(Chip8 *chip8){
    // TODO 1: Read the first byte from memory at PC.
    uint8_t first_byte = chip8->memory[chip8->PC];

    // TODO 2: Read the second byte from memory at PC + 1.
    uint8_t second_byte = chip8->memory[chip8->PC + 1];

    // TODO 3: Combine both bytes into one 16-bit instruction.
    uint16_t instruction = ((uint16_t)first_byte << 8) | second_byte;

    // TODO 4: Advance PC by 2.
    chip8->PC += 2;

    // TODO 5: Return the retrived instruction
    return instruction;
}

void chip8_step(Chip8 *chip8){
    //Fetch the instruction
    uint16_t instruction = chip8_fetch(chip8);

    //Execute the fetched instruction
    chip8_execute(chip8, instruction);
}