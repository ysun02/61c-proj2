#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* Sign extends the given field to a 32-bit integer where field is
 * interpreted an n-bit integer. Look in test_utils.c for examples. */
int sign_extend_number( unsigned int field, unsigned int n) {
    /* YOUR CODE HERE */
    return (int) field<<(32-n)>>(32-n);
}

/* Unpacks the 32-bit machine code instruction given into the correct
 * type within the instruction struct. Look at types.h */
Instruction parse_instruction(uint32_t instruction_bits) {
    Instruction instruction;
    /* YOUR CODE HERE */
    instruction.opcode = instruction_bits & 0b01111111;/*have the last 7bits*/
    switch(instruction.opcode) {
      case 0x33:
      	/* YOUR CODE HERE */

      	instruction.rtype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.rtype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.rtype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.rtype.rs2 = (instruction_bits & 0x1F00000 )>> 20;
      	instruction.rtype.funct7 = (instruction_bits & 0xFE000000 )>> 25;

      	break;
      case 0x13:
  	/* YOUR CODE HERE */

      	instruction.itype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.itype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.itype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.itype.imm = (instruction_bits & 0xFFF00000 )>> 20;
      	break;
      case 0x3:
  	/* YOUR CODE HERE */

      	instruction.itype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.itype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.itype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.itype.imm = (instruction_bits & 0xFFF00000 )>> 20;
      	break;
      case 0x67:
  	/* YOUR CODE HERE */

      	instruction.itype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.itype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.itype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.itype.imm = (instruction_bits & 0xFFF00000 )>> 20;
      	break;
      case 0x23:
  	/* YOUR CODE HERE */

      	instruction.stype.imm5 = (instruction_bits & 0x0F80) >> 7;
      	instruction.stype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.stype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.stype.rs2 = (instruction_bits & 0x1F00000 )>> 20;
      	instruction.stype.imm7 = (instruction_bits & 0xFE000000 )>> 25;
      	break;
      case 0x63:
  	/* YOUR CODE HERE */

      	instruction.sbtype.imm5 = (instruction_bits & 0x0F80) >> 7;
      	instruction.sbtype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.sbtype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.sbtype.rs2 = (instruction_bits & 0x1F00000 )>> 20;
      	instruction.sbtype.imm7 = (instruction_bits & 0xFE000000 )>> 25;
      	break;
      case 0x37:
  	/* YOUR CODE HERE */

      	instruction.utype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.utype.imm = (instruction_bits & 0xFFFFF000 )>> 12;
      	break;
      case 0x17:
  	/* YOUR CODE HERE */

      	instruction.utype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.utype.imm = (instruction_bits & 0xFFFFF000 )>> 12;
      	break;
      case 0x6F:
  	/* YOUR CODE HERE */

      	instruction.ujtype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.ujtype.imm = (instruction_bits & 0xFFFFF000 )>> 12;
      	break;
      case 0x73:
  	/* YOUR CODE HERE */

      	instruction.itype.rd = (instruction_bits & 0x0F80 )>> 7;
      	instruction.itype.funct3 = (instruction_bits & 0x7000 )>> 12;
      	instruction.itype.rs1 = (instruction_bits & 0xF8000 )>> 15;
      	instruction.itype.imm = (instruction_bits & 0xFFF00000 )>> 20;
      	break;
      default: // undefined opcode
      	handle_invalid_instruction(instruction);
      	break;
    }
    return instruction;
}



/* Return the number of bytes (from the current PC) to the branch label using the given
 * branch instruction */
int get_branch_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int imm5 = instruction.sbtype.imm5;
    unsigned int imm7 = instruction.sbtype.imm7;
    unsigned int IMM5 = imm5 &0b11110;
    unsigned int IMM11 = (imm5 & 0b00001) << 11;
    unsigned int IMM10 = (imm7 & 0b0111111) << 5;
    unsigned int IMM12 = (imm7 & 0b1000000) << 6;
    int result = sign_extend_number((IMM12 | IMM11 | IMM10 | IMM5), 13);
    return result;

}

/* Returns the number of bytes (from the current PC) to the jump label using the given
 * jump instruction */
int get_jump_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int imm20 = instruction.ujtype.imm;
    unsigned int IMM10 = (imm20 & 0b01111111111000000000) >> 8;
    unsigned int IMM11 = (imm20 & 0b00000000000100000000) << 3;
    unsigned int IMM19 = (imm20 & 0b00000000000011111111) << 12;
    unsigned int IMM20 = (imm20 & 0b10000000000000000000)<<1;
    int result = sign_extend_number((IMM20 | IMM19 | IMM11 | IMM10), 21);
    return result;
}

/* Returns the byte offset (from the address in rs2) for storing info using the given
 * store instruction */
int get_store_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    unsigned int imm5 = instruction.stype.imm5;
    unsigned int imm7 = instruction.stype.imm7;
    int result = sign_extend_number(imm5 | (imm7<<5), 12);
    return result;
}

void handle_invalid_instruction(Instruction instruction) {

    printf("Invalid Instruction: 0x%08x\n", instruction.bits);
    exit(-1);

}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}
