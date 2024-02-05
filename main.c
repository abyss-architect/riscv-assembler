#include <stdio.h>
#include <unistd.h>

#include "parser.h"

#define BUFFER_SIZE 1024

#define DEBUG 0

void binaryToString(char *str, unsigned int value);
void stringToHex(char *hex, const char *str);

int main() {
  char buffer[BUFFER_SIZE];
  while (read(STDIN_FILENO, buffer, BUFFER_SIZE)) {
    char *saveptr = NULL;
    char *line = strtok_r(buffer, "\n", &saveptr);
    do {
      printf("line: %s\n", line);

      // char *hex = malloc(sizeof(char) * (strlen(line) + 1));
      // stringToHex(hex, line);
      // printf("hex: %s\n", hex);
      // free(hex);

      Instruction temp_instruction;
      parseInstruction(&temp_instruction, line);

      char instr_bin_str[INSTRUCTION_SIZE_BITS + 1];
      binaryToString(instr_bin_str, temp_instruction.instruction);

      printf("instruction: %s\n", instr_bin_str);
      printf("\n");
    } while ((line = strtok_r(NULL, "\n", &saveptr)) && *line != EOF);
  }

  return 0;
}

void binaryToString(char *str, unsigned int value) {
  unsigned int i, mask = 1;
  for (i = INSTRUCTION_SIZE_BITS; i > 0; i--) {
    if (value & mask)
      str[i] = '1';
    else
      str[i] = '0';

    mask <<= 1;
  }
  str[INSTRUCTION_SIZE_BITS + 1] = '\0';
}

const char *HEX_CHARS = "0123456789ABCDEF";
void stringToHex(char *hex, const char *str) {
  unsigned int i = 0;
  while (str[i] != '\0') {
    hex[i] = HEX_CHARS[str[i]];
    i++;
  }

  hex[i] = '\0';
}