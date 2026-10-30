#include <stdlib.h>
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

    //Check the reset flag
    if(chip8->reset_vf)         chip8->V[0xF] = 0;

    //OR operation of the two registers
    chip8->V[add1] = chip8->V[add1] | chip8->V[add2];
}

void chip8_execute_8xy2(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;
    
    //Check the reset flag
    if(chip8->reset_vf)         chip8->V[0xF] = 0;

    //AND operation of the two registers
    chip8->V[add1] = chip8->V[add1] & chip8->V[add2];
}

void chip8_execute_8xy3(Chip8 *chip8, uint16_t instruction){
    //Find address 1
    uint8_t add1 = chip8_decode_instruction(instruction).x;

    //Find address 2
    uint8_t add2 = chip8_decode_instruction(instruction).y;
    
    //Check the reset flag
    if(chip8->reset_vf)         chip8->V[0xF] = 0;

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

void chip8_execute_1nnn(Chip8 *chip8, uint16_t instruction){
    //Get the address to jump
    uint16_t add = chip8_decode_instruction(instruction).nnn;

    //assign the address to PC
    chip8->PC = add;
}

void chip8_execute_2nnn(Chip8 *chip8, uint16_t instruction){
    //Get the jump address
    uint16_t add = chip8_decode_instruction(instruction).nnn;

    //Store the current address to stack
    chip8->stack[chip8->SP] = chip8->PC;

    //Increment the SP
    chip8->SP++;

    //Assign the address to PC
    chip8->PC = add;
}

void chip8_execute_00ee(Chip8 *chip8){
    //Decrement the SP
    chip8->SP--;
    
    //Assign the value at stack to the PC
    chip8->PC = chip8->stack[chip8->SP];
}

void chip8_execute_3xnn(Chip8 *chip8, uint16_t instruction){
    //Get the decoded instruction
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    //Get the register no.
    uint8_t x = decoded.x;

    //Get the value to compare
    uint8_t value = decoded.nn;

    //If equal then skip the next instruction
    if(value == chip8->V[x])    chip8->PC += 2;
}

void chip8_execute_4xnn(Chip8 *chip8, uint16_t instruction){
    //Get the decoded instruction
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    //Get the register no.
    uint8_t x = decoded.x;

    //Get the value to compare
    uint8_t value = decoded.nn;

    //If equal then skip the next instruction
    if(value != chip8->V[x])    chip8->PC += 2;
}

void chip8_execute_5xy0(Chip8 *chip8, uint16_t instruction){
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    uint8_t x = decoded.x;

    uint8_t y = decoded.y;

    if(chip8->V[x] == chip8->V[y])      chip8->PC += 2;
}

void chip8_execute_9xy0(Chip8 *chip8, uint16_t instruction){
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    uint8_t x = decoded.x;

    uint8_t y = decoded.y;

    if(chip8->V[x] != chip8->V[y])      chip8->PC += 2;
}

void chip8_execute_Bnnn(Chip8 *chip8, uint16_t instruction){
    //Get the address 
    uint16_t add = chip8_decode_instruction(instruction).nnn;

    //Store it to PC with V[0] as offset
    chip8->PC = add + (uint16_t)chip8->V[0];
}

void chip8_execute_Cxnn(Chip8 *chip8, uint16_t instruction){
    //Get a random number
    uint8_t random = (uint8_t)(rand() % 256);

    //Get the decoded instruction
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    //Get the nn
    uint8_t nn = decoded.nn;

    //Get the reg no.
    uint8_t x = decoded.x;

    //assign the value to reg x
    chip8->V[x] = random & nn;
}

void chip8_execute_ex9e(Chip8 *chip8,uint16_t instruction){
    //Get register number
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value at x register
    uint8_t value = chip8->V[x];   

    //check if the corresponding value key is pressed
    if(value <= 15 && chip8->keyboard[value] == true)      chip8->PC += 2;
}

void chip8_execute_exa1(Chip8 *chip8,uint16_t instruction){
    //Get register number
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value at x register
    uint8_t value = chip8->V[x];   

    //check if the corresponding value key is pressed
    if(value <= 15 && chip8->keyboard[value] == false)      chip8->PC += 2;
}

void chip8_execute_fx07(Chip8 *chip8,uint16_t instruction){
    //Get the reg no.
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value of delay timer
    uint8_t value = chip8->delay_timer;

    //Set the value to vx
    chip8->V[x] = value;
}

void chip8_execute_fx15(Chip8 *chip8,uint16_t instruction){
    //Get the reg no.
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value of register
    uint8_t value = chip8->V[x];

    //Set the value to delay timer
    chip8->delay_timer = value;
}

void chip8_execute_fx18(Chip8 *chip8,uint16_t instruction){
    //Get the reg no.
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value of register
    uint8_t value = chip8->V[x];

    //Set the value to sound timer
    chip8->sound_timer = value;
}

void chip8_execute_fx1e(Chip8 *chip8,uint16_t instruction){
    //Get the reg address
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value in Vx
    uint8_t value = chip8->V[x];

    //Add to the value of I reg
    chip8->I += (uint16_t)value;
}

void chip8_execute_fx0a(Chip8 *chip8,uint16_t instruction){
    //Get the reg no
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Check for a key press
    bool keypress = false;
    int i;
    for(i = 0; i < 16; i++){
        if(chip8->keyboard[i]){
            keypress = true;
            break;
        }
    }

    //Condition if keypress and if not
    if(keypress)    chip8->V[x] = (uint8_t)i;
    else            chip8->PC -= 2;
}

void chip8_execute_dxyn(Chip8 *chip8, uint16_t instruction){
    //Get the decoded instruction
    Chip8Instruction decoded = chip8_decode_instruction(instruction);

    //Height and width of the display matrix
    int height = (sizeof(chip8->display)/sizeof(chip8->display[0]));
    int width = (sizeof(chip8->display[0])/sizeof(chip8->display[0][0]));


    //Get the X cordinate
    uint8_t x = chip8->V[decoded.x] % width;

    //Get the Y coordinate
    uint8_t y = chip8->V[decoded.y] % height;

    //Set the VF collion flag to 0
    chip8->V[0xF] = 0;

    //Get the no of sprites to draw
    uint8_t n = decoded.n;

    //Draw the sprites
    for(int i = 0; i < n; i++){
        //Get the sprite byte from memory
        uint8_t sprite = chip8->memory[chip8->I + i];

        //Check for out of bounds in Rows
        if((y + i) >= height)    break;

        for(int j = 7, k = 0; j >= 0; j--, k++){
            //Get the bit from the sprite byte
            uint8_t bit = (sprite >> j) & 0x1;

            //Check in out of bounds in columns
            if((x + k) >= width)    break;

            //Check for collisions
            if(bit == 1 && chip8->display[y + i][x + k] == true){
                chip8->display[y + i][x + k] = false;
                chip8->V[0xF] = 1;   
            }
            else if(bit == 1 && chip8->display[y + i][x + k] == false){
                chip8->display[y + i][x + k] = true;
            }
        }
    }
}

void chip8_execute_fx29(Chip8 *chip8, uint16_t instruction){
    //Get the register number
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the character from the register
    uint8_t getvalue = chip8->V[x];

    //Assign the value to I
    chip8->I = 0x050 + (5 * getvalue); 
}

void chip8_execute_fx33(Chip8 *chip8, uint16_t instruction){
    //Get the register no.
    uint8_t x = chip8_decode_instruction(instruction).x;

    //Get the value
    uint8_t value = chip8->V[x];

    //store the value + I reg in memory
    for(int i = 2;i >= 0; i--){
        chip8->memory[chip8->I + i] = value % 10;
        value /= 10;
    }
}

void chip8_execute_fx55(Chip8 *chip8, uint16_t instruction){
    //Get the register number
    uint8_t x = chip8_decode_instruction(instruction).x;

    //store the value of V0 to Vx in memory
    for(int i = 0; i <= x; i++){
        chip8->memory[chip8->I + i] = chip8->V[i];
    }

    //Condition for quirk
    if(chip8->load_store_increment_i)       chip8->I += (uint16_t)(x + 1);
}

void chip8_execute_fx65(Chip8 *chip8, uint16_t instruction){
    //Get the register number
    uint8_t x = chip8_decode_instruction(instruction).x;

    //store the value of memory I to I + x in registers
    for(int i = 0; i <= x; i++){
        chip8->V[i] = chip8->memory[chip8->I + i];
    }
    
    //Condition for quirk
    if(chip8->load_store_increment_i)       chip8->I += (uint16_t)(x + 1);
}

void chip8_execute_00e0(Chip8 *chip8){
    //Initialize the display values to false
    int totalpixelrows = sizeof(chip8->display) / sizeof(chip8->display[0]);
    int totalpixelcol = sizeof(chip8->display[0]) / sizeof(chip8->display[0][0]);
    for (int i = 0; i < totalpixelrows; i++){
        for (int j = 0; j < totalpixelcol; j++){
            chip8->display[i][j] = false;
        }
    }
}
