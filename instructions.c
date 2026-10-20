#include "chip8.h"

void chip8_execute_6xnn(Chip8 *chip8, uint16_t instruction){

    //TODO : Extract the register no. and value and put the value in the extracted register no.
    uint8_t reg_no = chip8_decode_instruction(instruction).x;

    uint8_t value = chip8_decode_instruction(instruction).nn;
    
    chip8->V[reg_no] = value;
}

void chip8_execute_7xnn(Chip8 *chip8, uint16_t instruction){
    //Get the register no.
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value to add
    uint8_t value = chip8_decode_instruction(instruction).nn;

    //add the value
    chip8->V[x] += value;
}

void chip8_execute_Annn(Chip8 *chip8, uint16_t instruction){
    //Get the memry address to store
    uint16_t address = chip8_decode_instruction(instruction).nnn;

    //store the memory address in the index register
    chip8->I = address;
}

void chip8_execute_8xy4(Chip8 *chip8, uint16_t instruction){
    //Get address of first register
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Get address of second register
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //Store the addition
    uint16_t overflow = chip8->V[add1] + chip8->V[add2];

    //Store the value to the variable
    chip8->V[add1] = (uint8_t)(overflow & 0x00FF);

    //Check for overflow
    if(overflow > 255)      chip8->V[0xF] = 1;
    else                    chip8->V[0xF] = 0;
}

void chip8_execute_8xy5(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //Find The result
    uint16_t subtct = chip8->V[add1] - chip8->V[add2];

    //Check for borrow
    if(chip8->V[add1] < chip8->V[add2])    chip8->V[0xF] = 0;
    else                chip8->V[0xF] = 1;

    //Store the last 8 bits of the result to first register  
    chip8->V[add1] = subtct & 0x00FF;

}

void chip8_execute_8xy7(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //Get the result for reverse subtraction
    uint16_t revsub = chip8->V[add2] - chip8->V[add1];
    
    //Check for borrow
    if(chip8->V[add2] >= chip8->V[add1])    chip8->V[0xF] = 1;
    else                                    chip8->V[0xF] = 0;

    //Assign the result 
    chip8->V[add1] = revsub & 0x00FF;
}

void chip8_execute_8xy0(Chip8 *chip8, uint16_t instruction){
   //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //Assign the second value to first
    chip8->V[add1] = chip8->V[add2];
}

void chip8_execute_8xy1(Chip8 *chip8, uint16_t instruction){
   //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //OR operation of the two registers
    chip8->V[add1] = chip8->V[add1] | chip8->V[add2];
}

void chip8_execute_8xy2(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //AND operation of the two registers
    chip8->V[add1] = chip8->V[add1] & chip8->V[add2];
}

void chip8_execute_8xy3(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //XOR operation of the two registers
    chip8->V[add1] = chip8->V[add1] ^ chip8->V[add2];
}

void chip8_execute_8xy6(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //implement the choice based action
    if(chip8->shift_uses_vy != 0)       chip8->V[add1] = chip8->V[add2];

    //store the lsb in VF
    chip8->V[0xF] = chip8->V[add1] & 0x01;

    //Right shift the VX
    chip8->V[add1] = chip8->V[add1] >> 1;

}

void chip8_execute_8xyE(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;

    //implement the choice based action
    if(chip8->shift_uses_vy != 0)       chip8->V[add1] = chip8->V[add2];

    //store the msb in VF
    chip8->V[0xF] = (chip8->V[add1] & 0x80) >> 7;

    //left shift the VX
    chip8->V[add1] = chip8->V[add1] << 1;

}
