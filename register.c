#include "register.h"

const char* REGISTER_NAME[NUM_OF_REGS] = {
	"x0",
	"x1",
	"x2",
	"x3",
	"x4",
	"x5",
	"x6",
	"x7",
	"x8",
	"x9",
	"x10",
	"x11",
	"x12",
	"x13",
	"x14",
	"x15",
	"x16",
	"x17",
	"x18",
	"x19",
	"x20",
	"x21",
	"x22",
	"x23",
	"x24",
	"x25",
	"x26",
	"x27",
	"x28",
	"x29",
	"x30",
	"x31",
	"f0",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	"f13",
	"f14",
	"f15",
	"f16",
	"f17",
	"f18",
	"f19",
	"f20",
	"f21",
	"f22",
	"f23",
	"f24",
	"f25",
	"f26",
	"f27",
	"f28",
	"f29",
	"f30",
	"f31"
};

// TODO: Make this function use a hash map instead
unsigned int parseRegister(const char *register_str)
{
	unsigned int i;
	for (i = 0; i < NUM_OF_REGS; i++)
	{
		if (strcmp(REGISTER_NAME[i], register_str) == 0)
		{
			break;
		}
	}

	return i;
}