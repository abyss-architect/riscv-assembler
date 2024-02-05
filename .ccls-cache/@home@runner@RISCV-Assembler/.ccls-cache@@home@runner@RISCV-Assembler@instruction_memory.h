#ifndef __INSTRUCTION_MEMORY_H__
#define __INSTRUCTION_MEMORY_H__

#include "instruction.h"

#define IMEM_SIZE 256
typedef struct
{
	Instruction instructions[IMEM_SIZE];

	Instruction *last;
} Instruction_Memory;

#endif