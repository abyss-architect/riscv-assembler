#include "parser.h"

void loadInstructions(Instruction_Memory *instructions, FILE *file) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  Address PC = 0;
  unsigned int IMEM_index = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    printf("read: %s", line);
    Instruction temp_instruction;
    parseInstruction(&temp_instruction, line);
  }
}

int parseInstruction(Instruction *instruction_struct,
                     const char *instruction_str) {
  char *saveptr = NULL;
  char *__instruction_str__ =
      malloc(sizeof(char) * (strlen(instruction_str) + 1));
  strcpy(__instruction_str__, instruction_str);
  char *op_str = strtok_r(__instruction_str__, " ", &saveptr);
  unsigned int instruction, instruction_type = instructionType(op_str);

#if __PARSER_DEBUG__

  printf("op_str: %s\n", op_str);

#endif

  switch (instruction_type) {
  case RTYPE_MASK:
#if __PARSER_DEBUG__

    printf("R-type\n");

#endif
    instruction = parseRType(instruction_str);
    break;
  case ITYPE_MASK:
#if __PARSER_DEBUG__

    printf("I-type\n");

#endif
    instruction = parseIType(instruction_str);
    break;
  case SBTYPE_MASK:
#if __PARSER_DEBUG__

    printf("SB-type\n");

#endif
		instruction = parseSBType(instruction_str);
    break;
  default:
#if __PARSER_DEBUG__

    printf("Unknown instruction type\n");

#endif
    return -1;
  }

  instruction_struct->instruction = instruction;

  free(__instruction_str__);

  return 0;
}

unsigned int parseRType(const char *instruction_str) {
  unsigned int instruction = 0;
  unsigned int opcode = 0;
  unsigned int funct3 = 0;
  unsigned int funct7 = 0;

  char *saveptr = NULL;
  char *__instruction_str__ =
      malloc(sizeof(char) * (strlen(instruction_str) + 1));
  strcpy(__instruction_str__, instruction_str);
  char *op_str = strtok_r(__instruction_str__, " ", &saveptr);

  if (strcmp(op_str, "add") == 0) {
    opcode = 0b0110011;
    funct3 = 0b000;
    funct7 = 0b0000000;
  } else
    return instruction;

  char *reg_str = strtok_r(NULL, ", ", &saveptr);
  printf("rd: %s\n", reg_str);
  unsigned int rd = parseRegister(reg_str);

  reg_str = strtok_r(NULL, ", ", &saveptr);
  printf("rs_1: %s\n", reg_str);
  unsigned int rs_1 = parseRegister(reg_str);

  reg_str = strtok_r(NULL, ", ", &saveptr);
  printf("rs_2: %s\n", reg_str);
  unsigned int rs_2 = parseRegister(reg_str);

  instruction |= opcode;
  instruction |= (rd << 7);
  instruction |= (funct3 << (7 + 5));
  instruction |= (rs_1 << (7 + 5 + 3));
  instruction |= (rs_2 << (7 + 5 + 3 + 5));
  instruction |= (funct7 << (7 + 5 + 3 + 5 + 5));

  free(__instruction_str__);

  return instruction;
}

unsigned int parseIType(const char *instruction_str) {
  unsigned int instruction = 0;
  unsigned int opcode = 0;
  unsigned int funct3 = 0;
  unsigned int rd, rs_1;
  int imm;

  char *saveptr = NULL;
  char *__instruction_str__ =
      malloc(sizeof(char) * (strlen(instruction_str) + 1));
  strcpy(__instruction_str__, instruction_str);
  char *op_str = strtok_r(__instruction_str__, " ", &saveptr);

  if (strcmp(op_str, "ld") == 0) {
    opcode = 0b0000011;
    funct3 = 0b011;

    char *reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rd: %s\n", reg_str);
    rd = parseRegister(reg_str);

    char *imm_str = strtok_r(NULL, "(", &saveptr);
    printf("imm: %s\n", imm_str);
    imm = atoi(imm_str);

    reg_str = strtok_r(NULL, ")", &saveptr);
    printf("rs_1: %s\n", reg_str);
    rs_1 = parseRegister(reg_str);
  } else if (strcmp(op_str, "addi") == 0) {
    opcode = 0b0010011;
    funct3 = 0b000;

    char *reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rd: %s\n", reg_str);
    rd = parseRegister(reg_str);

    reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rs_1: %s\n", reg_str);
    rs_1 = parseRegister(reg_str);

    char *imm_str = strtok_r(NULL, ", ", &saveptr);
    printf("imm: %s\n", imm_str);
    imm = atoi(imm_str);
  } else if (strcmp(op_str, "slli") == 0) {
    opcode = 0b0010111;
    funct3 = 0b001;

    char *reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rd: %s\n", reg_str);
    rd = parseRegister(reg_str);

    reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rs_1: %s\n", reg_str);
    rs_1 = parseRegister(reg_str);

    char *imm_str = strtok_r(NULL, ", ", &saveptr);
    printf("imm: %s\n", imm_str);
    imm = atoi(imm_str);
  } else
    return instruction;

  instruction |= opcode;
  instruction |= (rd << 7);
  instruction |= (funct3 << (7 + 5));
  instruction |= (rs_1 << (7 + 5 + 3));
  instruction |= (imm << (7 + 5 + 3 + 5));

  free(__instruction_str__);

  return instruction;
}

unsigned int parseSBType(const char *instruction_str) {
  unsigned int instruction = 0;
  unsigned int opcode = 0;
  unsigned int funct3 = 0;
  unsigned int rd, rs_1;
  int imm;

  char *saveptr = NULL;
  char *__instruction_str__ =
      malloc(sizeof(char) * (strlen(instruction_str) + 1));
  strcpy(__instruction_str__, instruction_str);
  char *op_str = strtok_r(__instruction_str__, " ", &saveptr);

  if (strcmp(op_str, "bne") == 0) {
    opcode = 0b1101111;
    funct3 = 0b001;

    char *reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rd: %s\n", reg_str);
    rd = parseRegister(reg_str);

    reg_str = strtok_r(NULL, ", ", &saveptr);
    printf("rs_1: %s\n", reg_str);
    rs_1 = parseRegister(reg_str);

    char *imm_str = strtok_r(NULL, ", ", &saveptr);
    printf("imm: %s\n", imm_str);
    imm = atoi(imm_str);
  } else
    return instruction;

  unsigned int imm_4_1  =  imm & 0b000000001111;
  unsigned int imm_11   = (imm & 0b010000000000) >> 10;
  unsigned int imm_10_5 = (imm & 0b001111110000) >> 4;
  unsigned int imm_12   = (imm & 0b100000000000) >> 11;

  instruction |= opcode;
  instruction |= (((imm_4_1 << 1) | imm_11) << 7);
  instruction |= (funct3 << (7 + 5));
  instruction |= (rs_1 << (7 + 5 + 3));
  instruction |= (0 << (7 + 5 + 3 + 5));
  instruction |= (((imm_12 << 6) | imm_10_5) << (7 + 5 + 3 + 5 + 5));

  free(__instruction_str__);

  return instruction;
}