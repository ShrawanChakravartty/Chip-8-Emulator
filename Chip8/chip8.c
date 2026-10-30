#include <stdio.h>
#include "chip8.h"

uint8_t chip8_font[80] = {
    // 0
    0xF0, 0x90, 0x90, 0x90, 0xF0,
    // 1
    0x20, 0x60, 0x20, 0x20, 0x70,
    // 2
    0xF0, 0x10, 0xF0, 0x80, 0xF0,
    // 3
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    // 4
    0x90, 0x90, 0xF0, 0x10, 0x10,
    // 5
    0xF0, 0x80, 0xF0, 0x10, 0xF0,
    // 6
    0xF0, 0x80, 0xF0, 0x90, 0xF0,
    // 7
    0xF0, 0x10, 0x20, 0x40, 0x40,
    // 8
    0xF0, 0x90, 0xF0, 0x90, 0xF0,
    // 9
    0xF0, 0x90, 0xF0, 0x10, 0xF0,
    // A
    0xF0, 0x90, 0xF0, 0x90, 0x90,
    // B
    0xE0, 0x90, 0xE0, 0x90, 0xE0,
    // C
    0xF0, 0x80, 0x80, 0x80, 0xF0,
    // D
    0xE0, 0x90, 0x90, 0x90, 0xE0,
    // E
    0xF0, 0x80, 0xF0, 0x80, 0xF0,
    // F
    0xF0, 0x80, 0xF0, 0x80, 0x80
};

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

    //QUIRKS(1,true) means on and (0, false) means off
    {
        //Initialise the configurable instuction 0x8xy6
        chip8->shift_uses_vy = 0;

        //Reset VF before AND , OR , XOR
        chip8->reset_vf = false;

        //Increase the I by x + 1
        chip8->load_store_increment_i = false;
    }

    //Initialize the keys to false
    int totalkeys = sizeof(chip8->keyboard) / sizeof(chip8->keyboard[0]);
    for(int i = 0; i < totalkeys; i++){
        chip8->keyboard[i] = false;
    }

    
    //Initialize the display values to false
    int totalpixelrows = sizeof(chip8->display) / sizeof(chip8->display[0]);
    int totalpixelcol = sizeof(chip8->display[0]) / sizeof(chip8->display[0][0]);
    for (int i = 0; i < totalpixelrows; i++){
        for (int j = 0; j < totalpixelcol; j++){
            chip8->display[i][j] = false;
        }
    }

    //Insert the font data into memory
    for(int i = 0; i < 80; i++){
        chip8->memory[0x050 + i] = chip8_font[i];
    }
    

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

bool chip8_load_rom(Chip8 *chip8, const char *filename){
    //Make a variable of type file
    FILE *file;

    //store the contains of the rom
    file = fopen(filename, "rb");

    //check if null
    if(file == NULL){
        printf("Error in loading ROM or file name\n");
        return false;
    }

    //Move the pointer to the end of the file
    int end = fseek(file, 0, SEEK_END);

    //Check for error in fseek
    if(end != 0){
        printf("Error in seeking to the end of the file\n");
        fclose(file);
        return false;
    }

    //Store the file size
    long filesize = ftell(file);

    //Check for fail in filesize
    if(filesize < 0){
        printf("Error in calculating size\n");
        fclose(file);
        return false;
    }
    
    //Check for exceding the size of memory
    if(filesize > 3584){
        printf("Memory limit exceeded\n");
        fclose(file);
        return false;
    }

    //Rewind the pointer to the starting of the file
    rewind(file);

    //Write the bytes
    size_t bytes_read = fread(&chip8->memory[0x200], sizeof(uint8_t), filesize, file);

    //Check if bytes read is qual to the filesize
    if(bytes_read != (size_t)filesize){
        printf("Error reading ROM\n");
        fclose(file);
        return false;
    }

    fclose(file);

    return true;
}
