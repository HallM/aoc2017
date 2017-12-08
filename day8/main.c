#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// honestly, just an oversized max. got the ram for it.
#define MAX_REGISTERS 1024

struct Register {
  char* name;
  int value;
};

struct Register* findOrMake(struct Register* regs[MAX_REGISTERS], char* name) {
  // ideally, would use a hash or binary search for this
  int i = 0;
  struct Register* r = NULL;

  for (; i < MAX_REGISTERS; i++) {
    r = regs[i];
    if (r == NULL) {
      // "i" is now the index to insert at
      break;
    }

    if (strcmp(r->name, name) == 0) {
      // was malloc'd so lets send it free fallin
      free(name);
      return r;
    }
  }

  // never found anything, create a new one
  r = malloc(sizeof(struct Register));
  r->name = name;
  r->value = 0;

  regs[i] = r;

  return r;
}

int main() {
  struct Register* regs[MAX_REGISTERS];
  memset(regs, 0, sizeof(regs[0]) * MAX_REGISTERS);

  FILE* fp = fopen("input.txt", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  int maxAnytime = -9999;

  while((read = getline(&line, &len, fp)) != -1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    // REG [inc|dec] ## if REG [<|>|>=|<=|==|!=] NUM
    char* startPtr = line;
    char* endPtr = startPtr + 1;

    while (*endPtr != ' ') {
      endPtr++;
    }

    int nameLength = endPtr - startPtr;
    char* regname = malloc(nameLength + 1);
    strncpy(regname, startPtr, nameLength);
    regname[nameLength] = '\0';
    struct Register* reg = findOrMake(regs, regname);

    // -1 for DEC, 1 for INC
    int direction = *(endPtr + 1) == 'i' ? 1 : -1;

    startPtr = endPtr + 5;
    endPtr = startPtr + 1;
    while (*endPtr != ' ') {
      endPtr++;
    }

    *endPtr = '\0';
    int delta = atoi(startPtr) * direction;
    *endPtr = ' ';

    startPtr = endPtr + 4;
    endPtr = startPtr + 1;
    while (*endPtr != ' ') {
      endPtr++;
    }

    nameLength = endPtr - startPtr;
    regname = malloc(nameLength + 1);
    strncpy(regname, startPtr, nameLength);
    regname[nameLength] = '\0';
    struct Register* checkreg = findOrMake(regs, regname);

    startPtr = endPtr + 1;
    endPtr = startPtr + 1;

    /*
    0: >
    1: >=
    2: <
    3: <=
    4: ==
    5: !=
    */
    int operation = -1;

    if (*startPtr == '>') {
      if (*endPtr == '=') {
        operation = 1;
        endPtr++;
      } else {
        operation = 0;
      }
    } else if (*startPtr == '<') {
      if (*endPtr == '=') {
        operation = 3;
        endPtr++;
      } else {
        operation = 2;
      }
    } else if (*startPtr == '=' && *endPtr == '=') {
      operation = 4;
      endPtr++;
    } else if (*startPtr == '!' && *endPtr == '=') {
      operation = 5;
      endPtr++;
    }

    startPtr = endPtr + 1;
    int compareAgainst = atoi(startPtr);
    int isTrue = 0;

    switch (operation) {
      case 0:
        isTrue = checkreg->value > compareAgainst ? 1 : 0;
        break;
      case 1:
        isTrue = checkreg->value >= compareAgainst ? 1 : 0;
        break;
      case 2:
        isTrue = checkreg->value < compareAgainst ? 1 : 0;
        break;
      case 3:
        isTrue = checkreg->value <= compareAgainst ? 1 : 0;
        break;
      case 4:
        isTrue = checkreg->value == compareAgainst ? 1 : 0;
        break;
      case 5:
        isTrue = checkreg->value != compareAgainst ? 1 : 0;
        break;
    }

    if (isTrue == 1) {
      reg->value += delta;
      if (reg->value > maxAnytime) {
        maxAnytime = reg->value;
      }
    }
  }

  fclose(fp);
  if (line != NULL) {
    free(line);
    line = NULL;
  }

  // now determine the largest register
  int maxAtEnd = regs[0]->value;
  for (i = 0; i < MAX_REGISTERS; i++) {
    struct Register* r = regs[i];
    if (r == NULL) {
      break;
    }

    if (r->value > maxAtEnd) {
      maxAtEnd = r->value;
    }

    free(r->name);
    free(r);
  }

  printf("Part 1: max register value at end is: %d\n", maxAtEnd);
  printf("Part 2: max register value at any time is: %d\n", maxAnytime);

  return 0;
}
