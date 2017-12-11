#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// did someone say HEX GRIDS?! :D CUBE COORDINATE TIME

struct Coordinate {
  int x;
  int y;
  int z;
};

int distance(struct Coordinate start, struct Coordinate end) {
  return (abs(start.x - end.x) + abs(start.y - end.y) + abs(start.z - end.z)) >> 1;
}

int main() {
  struct Coordinate zero = {0, 0, 0};
  struct Coordinate current = {0, 0, 0};
  int furthestDistance = 0;

  FILE* fp = fopen("input.txt", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  while((read = getline(&line, &len, fp)) != -1) {
    if (line[0] == 'n') {
      if (line[1] == 'e') {
        current.x++;
        current.z--;
      } else if (line[1] == 'w') {
        current.x--;
        current.y++;
      } else {
        current.y++;
        current.z--;
      }
    } else if (line[0] == 's') {
      if (line[1] == 'e') {
        current.x++;
        current.y--;
      } else if (line[1] == 'w') {
        current.x--;
        current.z++;
      } else {
        current.y--;
        current.z++;
      }
    }

    int computedDistance = distance(current, zero);
    if (computedDistance > furthestDistance) {
      furthestDistance = computedDistance;
    }
  }

  fclose(fp);
  if (line) {
    free(line);
  }

  int computedDistance = distance(current, zero);

  printf("Part 1: distance aka moves away: %d\n", computedDistance);
  printf("Part 2: furthest distance: %d\n", furthestDistance);

  return 0;
}
