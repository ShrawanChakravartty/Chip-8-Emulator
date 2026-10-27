#include <stdio.h>
#include "chip8.h"

void chip8_execute(Chip8 *chip8, uint16_t instruction){
    //Get the decoded instruction
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    //fetch the type of instruction
    uint8_t type = decoded.type;

    //Fetch the subtype
    uint8_t subtype = decoded.n;

    //Fetch the last byte
    uint8_t byte = decoded.nn;

    //declare the various cases
    switch(type){
        case 0x0:
            switch(byte){
                case 0xEE:
                    //Handle the jump to address stored in stack
                    chip8_execute_00ee(chip8);
                    break;

                case 0xE0:
                    //Handle the clearing of screen
                    chip8_execute_00e0(chip8);
                    break;

                default:
                    //For legacy op-code 0NNN
            }
            break;

        case 0x1:
            //Handle the jump to address instruction
            chip8_execute_1nnn(chip8, instruction);
            break;

        case 0x2:
            //Handle the 2NNN opcode
            chip8_execute_2nnn(chip8, instruction);
            break;

        case 0x3:
            //Handle the Skip if equal instruction
            chip8_execute_3xnn(chip8, instruction);
            break;

        case 0x4:
            //Handle the Skip if not equal instruction
            chip8_execute_4xnn(chip8, instruction);
            break;

        case 0x5:
            //handle the skip if register value is equal
            if(subtype == 0)
                chip8_execute_5xy0(chip8, instruction);
            break;

        case 0x6:
            //Handle the 6XNN
            chip8_execute_6xnn(chip8, instruction);
            break;
        
        case 0x7:
            //handle immediate addition
            chip8_execute_7xnn(chip8, instruction);
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

                default:
                    //Say that this type is instruction is invalid or not yet implemented
                    printf("Unknown Instruction 0x%04X\n", (unsigned int)instruction);
                    break;
            }
            break;
        
        case 0x9:
            //Handle the not Equality of two register value
            if(subtype == 0)
                chip8_execute_9xy0(chip8, instruction);
            break;
        
        case 0xA:
            //Handle the Address storing instruction in I register
            chip8_execute_Annn(chip8,instruction);
            break;

        case 0xB:
            //Handle the jump with V[0] as offset instruction
            chip8_execute_Bnnn(chip8,instruction);
            break;

        case 0xC:
            //Handle random number assignment
            chip8_execute_Cxnn(chip8, instruction);
            break;

        case 0xD:
            //Handle the sprite drawing 
            chip8_execute_dxyn(chip8, instruction);
            break;

        case 0xE:
            switch(byte){
                case 0x9E:
                    //Handle skip if key is pressed
                    chip8_execute_ex9e(chip8, instruction);
                    break;

                case 0xA1:
                    //Handle skip if key is not pressed
                    chip8_execute_exa1(chip8, instruction);
                    break;

                default:
                    //Say that this type is instruction is invalid or not yet implemented
                    printf("Unknown Instruction 0x%04X\n", (unsigned int)instruction);
                    break;
            }
            break;

        case 0xF:
            switch(byte){
                case 0x07:
                    //Handle the Assignment of delay timer to vx
                    chip8_execute_fx07(chip8, instruction);
                    break;

                case 0x15:
                    //Handle the assignment of vx to delay timer
                    chip8_execute_fx15(chip8, instruction);
                    break;

                case 0x18:
                    //Handle the assignment of vx to sound timer
                    chip8_execute_fx18(chip8, instruction);
                    break;

                case 0x1E:
                    //Handle the add to I reg instruction
                    chip8_execute_fx1e(chip8, instruction);
                    break;

                case 0x0A:
                    //Handle if key is pressed and store its index to vx
                    chip8_execute_fx0a(chip8, instruction);
                    break;

                case 0x29:
                    //Handle Storing of font character address to I register
                    chip8_execute_fx29(chip8, instruction);
                    break;

                case 0x33:
                    //Handles storing of BCD in memory
                    chip8_execute_fx33(chip8, instruction);
                    break;

                case 0x55:
                    //handle the register value storing in memory
                    chip8_execute_fx55(chip8, instruction);
                    break;

                case 0x65:
                    //Handle the storing of values from memory to registers
                    chip8_execute_fx65(chip8, instruction);
                    break;

                default:
                    //Say that this type is instruction is invalid or not yet implemented
                    printf("Unknown Instruction 0x%04X\n", (unsigned int)instruction);
                    break;
            }
            break;

        default:
            //Say that this type is instruction is invalid or not yet implemented
            printf("Unknown Instruction 0x%04X\n", (unsigned int)instruction);
            break;
    }
}
