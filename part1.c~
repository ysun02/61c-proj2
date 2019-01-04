#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void print_utype(char*, Instruction);
void print_jal(Instruction);
void print_ecall(Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction); 
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);


void decode_instruction(uint32_t instruction_bits) {
    Instruction instruction = parse_instruction(instruction_bits); // Look in utils.c
    switch(instruction.opcode) {
        case 0x33:
            /* YOUR CODE HERE */
	    write_rtype(instruction);
            break;
        case 0x13:
            /* YOUR CODE HERE */
	    write_itype_except_load(instruction);
            break;
        case 0x3:
            /* YOUR CODE HERE */
	    write_load(instruction);
            break;
        case 0x67:
            /* YOUR CODE HERE */
	    print_itype_except_load("jalr", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x23:
            /* YOUR CODE HERE */
	    write_store(instruction);
            break;
        case 0x63:
            /* YOUR CODE HERE */
	    write_branch(instruction);
            break;
        case 0x37:
            /* YOUR CODE HERE */
	    print_utype("lui", instruction);
            break;
        case 0x17:
            /* YOUR CODE HERE */
	    print_utype("auipc", instruction);
      	    break;
        case 0x6F:
            /* YOUR CODE HERE */
	    print_jal(instruction);
            break;
        case 0x73:
            /* YOUR CODE HERE */
	    print_ecall(instruction);
	    break;
        default: // undefined opcode
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_rtype(Instruction instruction) {
    /* HINT: Hmmm, it's seems that there's way more R-Type instructions that funct3 possibilities... */
    switch (instruction.rtype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
	    
	    if(instruction.rtype.funct7==0b0000000){
		print_rtype("add", instruction);
	    }
	    else if(instruction.rtype.funct7==0x20){
		print_rtype("sub", instruction);
	    }
	    else if(instruction.rtype.funct7==0x01){
		print_rtype("mul", instruction);
	    }
	    break;
        case 0x1:
            /* YOUR CODE HERE */
	    if(instruction.rtype.funct7 == 0x01){
		print_rtype("mulh", instruction);
	    }
	    else{
		print_rtype("sll", instruction);
	    }
	    break;
        case 0x2:
            /* YOUR CODE HERE */
	    print_rtype("slt", instruction);
            break;
        case 0x3:
            /* YOUR CODE HERE */
	    if(instruction.rtype.funct7 == 0x01){
		print_rtype("mulhu", instruction);
	    }
	    else{
		print_rtype("sltu", instruction);
	    }
            break;
        case 0x4:
            /* YOUR CODE HERE */
	    if(instruction.rtype.funct7 == 0x01){
		print_rtype("div", instruction);
	    }
	    else{
		print_rtype("xor", instruction);
	    }
	    
            break;
        case 0x5:
            /* YOUR CODE HERE */
	    
	    if (instruction.rtype.funct7 == 0x0) {
		print_rtype("srl", instruction);
	    }
	    else if (instruction.rtype.funct7 == 0x20) {
		print_rtype("sra", instruction);
	    }
	    else if (instruction.rtype.funct7 == 0x01){
		print_rtype("divu", instruction);
	    }
	    break;
        case 0x6:
            /* YOUR CODE HERE */
	    if(instruction.rtype.funct7 == 0x01){
		print_rtype("rem", instruction);
	    }
	    else{
		print_rtype("or", instruction);
	    }
	    
	    break;
        case 0x7:
            /* YOUR CODE HERE */
	    if(instruction.rtype.funct7 == 0x01){
		print_rtype("remu", instruction);
	    }
	    else{
		print_rtype("and", instruction);
	    }
	    break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_itype_except_load(Instruction instruction) {
    switch (instruction.itype.funct3) {
	
        case 0x0:
            /* YOUR CODE HERE */
	    print_itype_except_load("addi", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x1:
            /* YOUR CODE HERE */
	    print_itype_except_load("slli", instruction, sign_extend_number(instruction.itype.imm, 12));
	    break;
        case 0x2:
            /* YOUR CODE HERE */
	    print_itype_except_load("slti", instruction, sign_extend_number(instruction.itype.imm, 12));
      	    break;
        case 0x3:
            /* YOUR CODE HERE */
	    print_itype_except_load("sltiu", instruction, sign_extend_number(instruction.itype.imm,12));
            break;
        case 0x4:
            /* YOUR CODE HERE */
	    print_itype_except_load("xori", instruction, sign_extend_number(instruction.itype.imm, 12));
	    break;
        case 0x5:
            /* HINT: What makes the immediate here special? */
            /* YOUR CODE HERE */
	    
	    if((instruction.itype.imm & 0b010000000000) != 0b010000000000){
		print_itype_except_load("srli", instruction, sign_extend_number(instruction.itype.imm&0b11111, 12));
	    }
	    else{
      		print_itype_except_load("srai", instruction, sign_extend_number(instruction.itype.imm&0b11111, 12));
	    }
	    break;
        case 0x6:
            /* YOUR CODE HERE */
	    print_itype_except_load("ori", instruction, sign_extend_number(instruction.itype.imm, 12));
	    break;
        case 0x7:
            /* YOUR CODE HERE */
	    print_itype_except_load("andi", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        default:
            handle_invalid_instruction(instruction);
            break;  
    }
}

void write_load(Instruction instruction) {
    switch (instruction.itype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
	    print_load("lb", instruction);
            break;
        case 0x1:
            /* YOUR CODE HERE */
	    print_load("lh", instruction);
	    break;
        case 0x2:
            /* YOUR CODE HERE */
	    print_load("lw", instruction);
	    break;
        case 0x4:
            /* YOUR CODE HERE */
	    print_load("lbu", instruction);
	    break;
        case 0x5:
            /* YOUR CODE HERE */
	    print_load("lhu", instruction);
	    break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_store(Instruction instruction) {
    switch (instruction.stype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
	    print_store("sb", instruction);
	    break;
        case 0x1:
            /* YOUR CODE HERE */
	    print_store("sh", instruction);
	    break;
        case 0x2:
            /* YOUR CODE HERE */
	    print_store("sw", instruction);
	    break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_branch(Instruction instruction) {
    switch (instruction.sbtype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
	    print_branch("beq", instruction);
	    break;
        case 0x1:
            /* YOUR CODE HERE */
	    print_branch("bne", instruction);
            break;
        case 0x4:
            /* YOUR CODE HERE */
	    print_branch("blt", instruction);
            break;
        case 0x5:
            /* YOUR CODE HERE */
	    print_branch("bge", instruction);
	    break;
        case 0x6:
            /* YOUR CODE HERE */
	    print_branch("bltu", instruction);
	    break;
        case 0x7:
            /* YOUR CODE HERE */
	    print_branch("bgeu", instruction);
	    break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

/* utils.c and utils.h might be useful here... */

void print_utype(char* name, Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int rd = instruction.utype.rd;
    unsigned int imm = instruction.utype.imm;
    printf(UTYPE_FORMAT, name, rd, imm);
}

void print_jal(Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int rd = instruction.ujtype.rd;
    int offset = get_jump_offset(instruction);
    printf(JAL_FORMAT, rd, offset);
}

void print_ecall(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(ECALL_FORMAT);
}

void print_rtype(char *name, Instruction instruction) {
    /* YOUR CODE HERE */

    unsigned int rd = instruction.rtype.rd;
    unsigned int rs1 = instruction.rtype.rs1;
    unsigned int rs2 = instruction.rtype.rs2;
    printf(RTYPE_FORMAT, name, rd, rs1, rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
    /* YOUR CODE HERE */
    unsigned int rd = instruction.itype.rd;
    unsigned int rs1 = instruction.itype.rs1;
    printf(ITYPE_FORMAT, name, rd, rs1, imm);
}

void print_load(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int rd = instruction.itype.rd;
    unsigned int rs1 = instruction.itype.rs1;
    unsigned int imm = instruction.itype.imm;
    printf(MEM_FORMAT, name, rd, sign_extend_number(imm, 12), rs1);
}

void print_store(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int rs1 = instruction.stype.rs1;
    unsigned int rs2 = instruction.stype.rs2;
    int offset = get_store_offset(instruction);
    printf(MEM_FORMAT, name, rs2, offset, rs1);
}

void print_branch(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    int offset = get_branch_offset(instruction);
    unsigned int rs1 = instruction.sbtype.rs1;
    unsigned int rs2 = instruction.sbtype.rs2;
    printf(BRANCH_FORMAT, name, rs1, rs2, offset);
}
