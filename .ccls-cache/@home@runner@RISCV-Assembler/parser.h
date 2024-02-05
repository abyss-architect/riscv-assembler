#ifndef __PARSER_H__
#define __PARSER_H__

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction_memory.h"
#include "register.h"

void loadInstructions(Instruction_Memory *instructions, FILE *file);
int parseInstruction(Instruction *instruction, const char *instruction_str);
unsigned int parseRType(const char *instruction_str);
unsigned int parseIType(const char *instruction_str);
unsigned int parseSBType(const char *instruction_str);
unsigned int parseRegister(const char *register_str);

#endif

#ifndef __PARSER_DEBUG__
#define __PARSER_DEBUG__ 1
#endif