#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <string.h>

#define NUM_OF_REGS 64

extern const char* REGISTER_NAME[NUM_OF_REGS];

unsigned int parseRegister(const char *register_str);

#endif