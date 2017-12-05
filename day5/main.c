#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JUMP_TABLE_SIZE 1043

int main() {
  int jumps[JUMP_TABLE_SIZE];
  memset(jumps, 0, sizeof(jumps[0]) * JUMP_TABLE_SIZE);

  FILE* fp = fopen("jumps.txt", "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;

  while((read = getline(&line, &len, fp)) != -1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    jumps[i] = atoi(line);
    i++;
  }

  fclose(fp);
  if (line != NULL) {
    free(line);
    line = NULL;
  }

  // start at 0
  i = 0;
  int jumpsTaken = 0;

  // keep jumping till we get out
  while (i >= 0 && i < JUMP_TABLE_SIZE) {
    int jumpBy = jumps[i];

    // Part1: increment that slot after using it
    // jumps[i]++;

    // Part2: Now, the jumps are even stranger:
    // after each jump, if the offset was three or more, instead decrease it by 1. Otherwise, increase it by 1 as before.
    if (jumpBy >= 3) {
      jumps[i]--;
    } else {
      jumps[i]++;
    }

    // jump by the amount originally fetched
    i += jumpBy;
    jumpsTaken++;
  }

  printf("Part 1: total number of jumps taken: %d\n", jumpsTaken);

  return 0;
}
