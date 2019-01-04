#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"
#include "riscv.h"

void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_jalr(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_lui(Instruction, Processor *);
void execute_auipc(Instruction, Processor *);

void execute_instruction(uint32_t instruction_bits, Processor *processor,Byte *memory) {
    Instruction instruction = parse_instruction(instruction_bits); // Look in utils.c

    switch(instruction.opcode) {

        case 0x33:
            /* YOUR CODE HERE */

            execute_rtype(instruction, processor);
            break;
        case 0x13:
            /* YOUR CODE HERE */

            execute_itype_except_load(instruction, processor);
            break;
        case 0x3:
            /* YOUR CODE HERE */

            execute_load(instruction, processor, memory);
            break;
        case 0x67:
            /* YOUR CODE HERE */
            execute_jalr(instruction, processor);
            break;
        case 0x23:
            /* YOUR CODE HERE */

            execute_store(instruction, processor, memory);
            break;
        case 0x63:
            /* YOUR CODE HERE */

            execute_branch(instruction, processor);
            break;
        case 0x37:
            /* YOUR CODE HERE */

            execute_lui(instruction, processor);
            break;
        case 0x17:
            /* YOUR CODE HERE */

            execute_auipc(instruction, processor);
            break;
        case 0x6F:
            /* YOUR CODE HERE */

            execute_jal(instruction, processor);
            break;
        case 0x73:
            /* YOUR CODE HERE */
            //where should I change ecall?
            execute_ecall(processor, memory);
            break;
        default: // undefined opcode
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_rtype(Instruction instruction, Processor *processor) {
    switch (instruction.rtype.funct3){

        case 0x0:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7){
                case 0x00:
                    processor->R[instruction.rtype.rd] = (processor->R[instruction.rtype.rs1]) + (processor->R[instruction.rtype.rs2]);
                    processor->PC += 4;
                    break;
                case 0x01:
                //[31:0] mul
                    processor->R[instruction.rtype.rd] = ((sDouble)(processor->R[instruction.rtype.rs1]) * (sDouble)(processor->R[instruction.rtype.rs2])) & 0xFFFFFFFF;
                    processor->PC += 4;
                    break;
                case 0x20:
                    processor->R[instruction.rtype.rd] = ((processor->R[instruction.rtype.rs1])) - ((processor->R[instruction.rtype.rs2]));
                    processor->PC += 4;
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    exit(-1);
                    break;
                }
            break;
        case 0x1:
            /* YOUR CODE HERE */
            if (instruction.rtype.funct7 == 0x00){
                //sll
                processor->R[instruction.rtype.rd] = (Word)processor->R[instruction.rtype.rs1] << (Word)processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            else if (instruction.rtype.funct7 == 0x01){
                // why[63:32]? mulh

                sDouble rs1 = processor->R[instruction.rtype.rs1];
                sDouble rs2 = processor->R[instruction.rtype.rs2];
                rs1 = (rs1 << 32) >> 32;
                rs2 = (rs2 << 32) >> 32;
                sDouble product = rs1 * rs2 >> 32;

                processor->R[instruction.rtype.rd] = (sWord) product & 0x00000000FFFFFFFF;
                processor->PC += 4;
            }
            break;
        case 0x2:
            /* YOUR CODE HERE */
            processor->R[instruction.rtype.rd] = ((sWord)processor->R[instruction.rtype.rs1] < (sWord)processor->R[instruction.rtype.rs2]) ? 1 : 0;
            processor->PC += 4;
            break;
        case 0x3:
            /* YOUR CODE HERE */
            // unsigned
            if(instruction.rtype.funct7 == 0x00){
                processor->R[instruction.rtype.rd] = ((Word)processor->R[instruction.rtype.rs1] < (Word)processor->R[instruction.rtype.rs2]) ? 1 : 0;
                processor->PC += 4;
            }
            else if(instruction.rtype.funct7 == 0x01){
                //[63:32] unsigned mulhu
                // shift 32 bits
                Double rs1 = processor->R[instruction.rtype.rs1];
                Double rs2 = processor->R[instruction.rtype.rs2];
                rs1 = (rs1 << 32) >> 32;
                rs2 = (rs2 << 32) >> 32;
                Double product = rs1 * rs2 >> 32;

                processor->R[instruction.rtype.rd] = (Word) product & 0x00000000FFFFFFFF;

                processor->PC += 4;
            }
            break;
        case 0x4:
            /* YOUR CODE HERE */
            if(instruction.rtype.funct7 == 0x00){
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] ^ processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            else if(instruction.rtype.funct7 == 0x01){
                //div
                processor->R[instruction.rtype.rd] = (sWord)processor->R[instruction.rtype.rs1] / (sWord)processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            break;
        case 0x5:
            /* YOUR CODE HERE */
            if(instruction.rtype.funct7 == 0x00){
                //srl
                processor->R[instruction.rtype.rd] = (Word)processor->R[instruction.rtype.rs1] >> (Word)processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            else if(instruction.rtype.funct7 == 0x01){
                //divu
                processor->R[instruction.rtype.rd] = (Word)processor->R[instruction.rtype.rs1] / (Word)processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            else if(instruction.rtype.funct7 == 0x20){
                //sra
                processor->R[instruction.rtype.rd] = (sWord)(processor->R[instruction.rtype.rs1]) >> (sWord)(processor->R[instruction.rtype.rs2]);
                processor->PC += 4;
            }
            break;
        case 0x6:
            /* YOUR CODE HERE */
            if(instruction.rtype.funct7 == 0x00){
                //or
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] | processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            else if(instruction.rtype.funct7 == 0x01){
                //rem
                processor->R[instruction.rtype.rd] = (sWord)(processor->R[instruction.rtype.rs1]) % (sWord)(processor->R[instruction.rtype.rs2]);
                processor->PC += 4;
            }
            break;
        case 0x7:
            /* YOUR CODE HERE */
            if(instruction.rtype.funct7 == 0x00){
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] & processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            else if(instruction.rtype.funct7 == 0x01){
                processor->R[instruction.rtype.rd] = (Word)processor->R[instruction.rtype.rs1] % (Word)processor->R[instruction.rtype.rs2];
                processor->PC += 4;
            }
            break;
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_itype_except_load(Instruction instruction, Processor *processor) {
    switch (instruction.itype.funct3) {

        case 0x0:
            /* YOUR CODE HERE */
            //addi
            processor->R[instruction.itype.rd] = (processor->R[instruction.itype.rs1]) + sign_extend_number(instruction.itype.imm, 12);
            processor->PC += 4;
            break;
        case 0x1:
            /* YOUR CODE HERE */
            //slli
            processor->R[instruction.itype.rd] = (Word)processor->R[instruction.itype.rs1] << (Word)(instruction.itype.imm&0b11111);
            processor->PC += 4;
            break;
        case 0x2:
            /* YOUR CODE HERE */
            //slti
            processor->R[instruction.itype.rd] = ((sWord)processor->R[instruction.itype.rs1] < sign_extend_number(instruction.itype.imm, 12)) ? 1 : 0;
            processor->PC += 4;
            break;
        case 0x3:
            /* YOUR CODE HERE */
            //sltiu
            processor->R[instruction.itype.rd] = ((Word)processor->R[instruction.itype.rs1] < (Word)instruction.itype.imm) ? 1 : 0;
            processor->PC += 4;
            break;
        case 0x4:
            /* YOUR CODE HERE */
            //xori
            processor->R[instruction.itype.rd] = (processor->R[instruction.itype.rs1] ^ sign_extend_number(instruction.itype.imm, 12));
            processor->PC += 4;
            break;
        case 0x5:
            /* YOUR CODE HERE */

            if((instruction.itype.imm & 0x400) != 0x400){
                //srli
		        processor->R[instruction.itype.rd] = (Word)(processor->R[instruction.itype.rs1]) >> (instruction.itype.imm & 0b11111);
                processor->PC += 4;
                  }
            else{
                //srai
                processor->R[instruction.itype.rd] = (sWord)(processor->R[instruction.itype.rs1]) >> (instruction.itype.imm&0b11111);
                processor->PC += 4;
            }
            break;
        case 0x6:
            /* YOUR CODE HERE */
            //ori
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] | sign_extend_number(instruction.itype.imm, 12);
            processor->PC += 4;
            break;
        case 0x7:
            /* YOUR CODE HERE */
            //andi
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] & sign_extend_number(instruction.itype.imm, 12);
            processor->PC += 4;
            break;
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_ecall(Processor *p, Byte *memory) {

    Register i;


    // What do we switch on?
    switch(/* YOUR CODE HERE */p->R[10]) {
        case 1: // print an integer
            p->PC += 4;
            printf("%d",p->R[11]);
            break;
        case 4: // print a string
            for(i = p->R[11]; i < MEMORY_SPACE && load(memory, i, LENGTH_BYTE); i++) {
                printf("%c",load(memory,i,LENGTH_BYTE));
                p->PC += 4;
            }
            break;
        case 10: // exit
            printf("exiting the simulator\n");
            p->PC += 4;
            exit(0);
            break;
        case 11: // print a character
            printf("%c",p->R[11]);
            p->PC += 4;
            break;
        default: // undefined ecall
            printf("Illegal ecall number %d\n", p->R[10]);
            exit(-1);
            break;
    }
}

void execute_branch(Instruction instruction, Processor *processor) {
    switch (instruction.sbtype.funct3) {

        case 0x0:
            /* YOUR CODE HERE */
            if((sWord)processor->R[instruction.sbtype.rs1] == (sWord)processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
            }
            else{
                processor->PC += 4;
            }
            break;
        case 0x1:
            /* YOUR CODE HERE */
            if((sWord)processor->R[instruction.sbtype.rs1] != (sWord)processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
            }
            else{
                processor->PC += 4;
            }
            break;
        case 0x4:
            /* YOUR CODE HERE */
            if((sWord)processor->R[instruction.sbtype.rs1] < (sWord)processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
            }
            else{
                processor->PC += 4;
            }
            break;
        case 0x5:
            /* YOUR CODE HERE */
            if((sWord)processor->R[instruction.sbtype.rs1] >= (sWord)processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
            }
            else{
                processor->PC += 4;
            }
            break;
        case 0x6:
            /* YOUR CODE HERE */
            //(unsigned int)
            if((Word)processor->R[instruction.sbtype.rs1] < (Word)processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
            }
            else{
                processor->PC += 4;
            }
            break;
        case 0x7:
            /* YOUR CODE HERE */
            //unsigned int
            if((Word)processor->R[instruction.sbtype.rs1] >= (Word)processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
            }
            else{
                processor->PC += 4;
            }
            break;
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
    switch (instruction.itype.funct3) {

        case 0x0:
            /* YOUR CODE HERE */
            // lb
            processor->R[instruction.itype.rd] = sign_extend_number(load(memory, (processor->R[instruction.itype.rs1]+instruction.itype.imm), LENGTH_BYTE), 8);
            processor->PC += 4;
            break;
        case 0x1:
            /* YOUR CODE HERE */
            //lh
            processor->R[instruction.itype.rd] = sign_extend_number(load(memory, (processor->R[instruction.itype.rs1]+instruction.itype.imm), LENGTH_HALF_WORD), 16);
            processor->PC += 4;
            break;
        case 0x2:
            /* YOUR CODE HERE */
            // lw
            processor->R[instruction.itype.rd] = load(memory, (processor->R[instruction.itype.rs1]+instruction.itype.imm), LENGTH_WORD);
            processor->PC += 4;
            break;
        case 0x4:
            /* YOUR CODE HERE */
            //lbu
            processor->R[instruction.itype.rd] = (Word)(load(memory, (processor->R[instruction.itype.rs1]+(Word)instruction.itype.imm), LENGTH_BYTE));
            processor->PC += 4;
            break;
        case 0x5:
            /* YOUR CODE HERE */
            //lhu
            processor->R[instruction.itype.rd] = (Word)(load(memory, (processor->R[instruction.itype.rs1]+(Word)instruction.itype.imm), LENGTH_HALF_WORD));
            processor->PC += 4;
            break;
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_store(Instruction instruction, Processor *processor, Byte *memory) {
    switch (instruction.stype.funct3) {


        case 0x0:
            /* YOUR CODE HERE */
            //sb
            store(memory, (processor->R[instruction.stype.rs1])+get_store_offset(instruction), LENGTH_BYTE, processor->R[instruction.stype.rs2]);// & 0xFF));
            processor->PC += 4;
            break;
        case 0x1:
            /* YOUR CODE HERE */
            //sh
            store(memory, (processor->R[instruction.stype.rs1])+get_store_offset(instruction), LENGTH_HALF_WORD, processor->R[instruction.stype.rs2]);// & 0xFFFF));
            processor->PC += 4;
            break;
        case 0x2:
            /* YOUR CODE HERE */
            //sw
            store(memory, (processor->R[instruction.stype.rs1])+get_store_offset(instruction), LENGTH_WORD, processor->R[instruction.stype.rs2]);
            processor->PC += 4;
            break;
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_jal(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */



    processor->R[instruction.ujtype.rd] = processor->PC + 4;
    processor->PC += get_jump_offset(instruction);
}

void execute_jalr(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */

    processor->R[instruction.itype.rd] = processor->PC + 4;
    processor->PC = (sWord)processor->R[instruction.itype.rs1] + (sWord)instruction.itype.imm;

}

void execute_lui(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */

    processor->R[instruction.utype.rd] = (Word)instruction.utype.imm << 12;
    processor->PC += 4;

}

void execute_auipc(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */

    processor->R[instruction.utype.rd] = processor->PC + ((Word)instruction.utype.imm << 12);
    processor->PC += 4;
}


void store(Byte *memory, Address address, Alignment alignment, Word value) {
    /* YOUR CODE HERE */
    // for(int i = 0; i<alignment; i ++){
    //     *(memory + address + i) = value & 0xFF;
    //     value = value >> 8;
    //     }
    switch(alignment){
        case LENGTH_BYTE:
            memory[address + 0] = value & 0xFF;
            break;
        case LENGTH_HALF_WORD:
            memory[address + 0] = value & 0xFF;
            memory[address + 1] = (value >> 8) & 0xFF;
            break;
        case LENGTH_WORD:
            memory[address + 0] = value & 0xFF;
            memory[address + 1] = (value >> 8) & 0xFF;
            memory[address + 2] = (value >> 16) & 0xFF;
            memory[address + 3] = (value >> 24) & 0xFF;
            break;
        default:

            exit(-1);
            break;
    }

    // if(alignment == 1){
    //     *(memory + address) = value;
    // }
    // else if(alignment == 2){
    //     *(memory + address) = value;
    // }
    // else if(alignment == 4){
    //     *(memory + address) = value;
    // }


}

Word load(Byte *memory, Address address, Alignment alignment) {
    /* YOUR CODE HERE */

    if (alignment == 1){
        return *(Byte *)(memory+address);
    }
    else if (alignment == 2){
        // byte by byte
        return *(Half *)(memory+address);
    }
    else if (alignment == 4){
        return *(Word *)(memory+address);
    }

}
