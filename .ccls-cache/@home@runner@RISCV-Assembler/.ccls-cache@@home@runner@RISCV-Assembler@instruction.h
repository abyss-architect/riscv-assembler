#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stdint.h>
#include <string.h>

typedef uint64_t Address;

typedef struct
{
	Address address;
	unsigned int instruction;
} Instruction;

#define RTYPE_MASK  0x1
#define ITYPE_MASK 	0x2
#define SBTYPE_MASK 0x4

unsigned int instructionType(const char *op_str);

#endif