#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int findNearestOddRoot(int num) {
  int oddroot = ceil(sqrt(num));
  if ((oddroot & 1) == 0) {
    // make sure it is an odd number
    oddroot += 1;
  }

  return oddroot;
}

int main() {
  const int input = 325489;

  const int size = findNearestOddRoot(input);
  const int sizeOffOne = size - 1;
  const int center = sizeOffOne / 2;
  const int maxNum = size * size;

  printf("minimum supporting size is: %d\n", size);

  // make the table 1 larger, to avoid needing to check bounds
  const int sizeUpOne = size + 1;
  int table[sizeUpOne][sizeUpOne];

  // initialize everything to 0
  // then don't have to track if the field is valid or not. just add all surrounding ones
  memset(table, 0, sizeof(table[0][0]) * sizeUpOne * sizeUpOne);

  table[center][center] = 1;
  table[center][center+1] = 1;
  int ring = 1;
  int direction = 0;
  // 0: up, 1: left, 2: down, 3: right

  int x = center + 1;
  int y = center;
  int lastSum = 0;

  while (lastSum <= input) {
    if (direction == 0) {
      int nexty = y - 1;
      if (nexty < (center - ring)) {
        direction = 1;
      } else {
        y = nexty;
      }
    }
    if (direction == 1) {
      int nextx = x - 1;
      if (nextx < (center - ring)) {
        direction = 2;
      } else {
        x = nextx;
      }
    }
    if (direction == 2) {
      int nexty = y + 1;
      if (nexty > (center + ring)) {
        direction = 3;
      } else {
        y = nexty;
      }
    }
    if (direction == 3) {
      int nextx = x + 1;
      if (nextx > (center + ring + 1)) {
        direction = 0;
        ring += 1;
        // loop back up to hit the first if
        continue;
      } else {
        x = nextx;
      }
    }

    // sum everything around it. anything not computed yet will be 0 any way
    lastSum =
      table[y-1][x-1] +
      table[y-1][x  ] +
      table[y-1][x+1] +
      table[y  ][x-1] +
      table[y  ][x+1] +
      table[y+1][x-1] +
      table[y+1][x  ] +
      table[y+1][x+1];

    table[y][x] = lastSum;
  }

  // for (y = 0; y < size; y++) {
  //   for (x = 0; x < size; x++) {
  //     printf("%5d ", table[y][x]);
  //   }
  //   printf("\n");
  // }

  printf("Part 2 answer: %d\n", lastSum);

  return 0;
}
