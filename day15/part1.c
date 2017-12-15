#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned long long genA = 679; // 65;
  unsigned long long genB = 771; // 8921;

  int part1Matches = 0;

  for (int i = 0; i < 40000000; i++) {
    genA = (genA * 16807) % 2147483647;
    genB = (genB * 48271) % 2147483647;

    if ((genA & 0xFFFF) == (genB & 0xFFFF)) {
      part1Matches++;
    }
  }

  printf("Part 1: number of lower 16 matches: %d\n", part1Matches);

  return 0;
}
