#include <stdio.h>
#include "chip8.h"

Chip8Instruction chip8_decode_instruction(uint16_t instruction){
    //Initialize the decoded variable
    Chip8Instruction decoded;

    //Extracting type
    decoded.type = (instruction >> 12) & 0x0F;

    //Extracting x
    decoded.x = (instruction >> 8) & 0x0F;

    //Extracting y
    decoded.y = (instruction >> 4) & 0x00F;

    //Extracting n
    decoded.n = instruction & 0x000F;

    //Extraxting nn
    decoded.nn = instruction & 0xFF;

    //Extracting nnn
    decoded.nnn = instruction & 0x0FFF;

    //Return the extracted info
    return decoded;
}

void chip8_execute(Chip8 *chip8, uint16_t instruction){
    //fetch the type of instruction
    uint8_t type = chip8_decode_instruction(instruction).type;

    //Fetch the subtype
    uint8_t subtype = chip8_decode_instruction(instruction).n;

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
                case 0x0:
                    //Handle the assignment of second rg value to first
                    chip8_execute_8xy0(chip8, instruction);
                    break;

                case 0x1:
                    //Handle the bitwise OR operation
                    chip8_execute_8xy1(chip8, instruction);
                    break; 

                case 0x2:
                    //Handle the bitwise AND operation
                    chip8_execute_8xy2(chip8, instruction);
                    break;
                    
                case 0x3:
                    //Handle the bitwise XOR operation
                    chip8_execute_8xy3(chip8, instruction);
                    break;

                case 0x4:
                    //Handle the addition operation
                    chip8_execute_8xy4(chip8, instruction);
                    break; 

                case 0x5:
                    //Handle the subtraction operation
                    chip8_execute_8xy5(chip8, instruction);
                    break;

                case 0x6:
                    //Handle the bitwise right shift operation
                    chip8_execute_8xy6(chip8, instruction);
                    break;

                case 0x7:
                    //Handle the reverse subtraction operation
                    chip8_execute_8xy7(chip8, instruction);
                    break;

                case 0xE:
                    //Handle the bitwise left shift operation
                    chip8_execute_8xyE(chip8, instruction);
                    break;
            }
            break;

        default:
            //Say that this type is instruction is invalid or not yet implemented
            printf("Unknown Instruction 0x%04X\n", (unsigned int)instruction);
            break;
    }
}
