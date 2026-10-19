#include <stdio.h>
#include "chip8.h"

uint8_t chip8_get_register(uint16_t instruction){
    // TODO: Extract the second hexadecimal digit.
    return (uint8_t)((instruction >> 8) & 0x0F);
}

uint8_t chip8_get_value(uint16_t instruction){
    //TODO: Extract the last two hexadecimal digits
    return instruction & 0xFF;
}

void chip8_execute_6xnn(Chip8 *chip8, uint16_t instruction){
    //TODO : Extract the register no. and value and put the value in the extracted register no.
    uint8_t reg_no = chip8_get_register(instruction);

    uint8_t value = chip8_get_value(instruction);
    
    chip8->V[reg_no] = value;
}

void chip8_execute_7xnn(Chip8 *chip8, uint16_t instruction){
    //Get the register no.
    uint8_t x = chip8_get_register(instruction);

    //Get the value to add
    uint8_t value = chip8_get_value(instruction);

    //add the value
    chip8->V[x] += value;
}

void chip8_execute_Annn(Chip8 *chip8, uint16_t instruction){
    //Get the memry address to store
    uint16_t address = instruction & 0x0FFF;

    //store the memory address in the index register
    chip8->I = address;
}

void chip8_execute_8xy4(Chip8 *chip8, uint16_t instruction){
    //Get address of first register
    uint8_t add1 = chip8_get_register(instruction);

    //Get address of second register
    uint8_t add2 = (instruction >> 4) & 0x00F;

    //Store the addition
    uint16_t overflow = chip8->V[add1] + chip8->V[add2];

    //Store the value to the variable
    chip8->V[add1] = (uint8_t)(overflow & 0x00FF);

    //Check for overflow
    if(overflow > 255)      chip8->V[0xF] = 1;
    else                    chip8->V[0xF] = 0;
}

void chip8_execute(Chip8 *chip8, uint16_t instruction){
    //fetch the type of instruction
    uint8_t type = (instruction >> 12) & 0x0F;
    //Fetch the subtype
    uint8_t subtype = instruction & 0x000F;

    //declare the various cases
    switch(type){
        case 0x6:
            //Handle the 6XNN
            chip8_execute_6xnn(chip8, instruction);
            break;
        
        case 0x7:
            //handle immediate addition
            chip8_execute_7xnn(chip8, instruction);
            break;

        case 0xA:
            //Handle the Address storing instruction in I register
            chip8_execute_Annn(chip8,instruction);
            break;

        case 0x8:
            //Handle the operation of two register
            switch(subtype){
                case 0x4:
                    //Handle the addition operation
                    chip8_execute_8xy4(chip8, instruction);
                    break; 
            }
            break;

        default:
            //Say that this type is instruction is invalid or not yet implemented
            printf("Unknown Instruction 0x%04X\n", (unsigned int)instruction);
            break;
    }
}
