#include "instruction.h"

unsigned int instructionType(const char *op_str)
{
	if (
			strcmp(op_str, "add") == 0 ||
			strcmp(op_str, "sll") == 0 ||
			strcmp(op_str, "xor") == 0 ||
			strcmp(op_str, "and") == 0
		)
		return RTYPE_MASK;
	else if (
			strcmp(op_str, "ld")   == 0 ||
			strcmp(op_str, "addi") == 0 ||
			strcmp(op_str, "slli") == 0
		)
		return ITYPE_MASK;
	else if (
			strcmp(op_str, "bne") == 0
		)
		return SBTYPE_MASK;

	return 0;
}