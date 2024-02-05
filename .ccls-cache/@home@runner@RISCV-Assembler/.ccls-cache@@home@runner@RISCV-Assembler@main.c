#include <stdio.h>
#include <unistd.h>

#include "parser.h"

#define BUFFER_SIZE 1024

#define DEBUG 0

int main() {
	char buffer[BUFFER_SIZE];
	while (read(STDIN_FILENO, buffer, BUFFER_SIZE))
	{
		char *saveptr = NULL;
		char *line = strtok_r(buffer, "\n", &saveptr);
		do {
			printf("read: %s\n", line);
			
			Instruction temp_instruction;
			parseInstruction(&temp_instruction, line);		

			printf("instruction: %u\n", temp_instruction.instruction);
			printf("\n");
		}
		while ((line = strtok_r(NULL, "\n", &saveptr)));
	}
	
  return 0;
}