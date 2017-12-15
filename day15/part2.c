#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned long long genA = 679; // 65;
  unsigned long long genB = 771; // 8921;

  int part2Matches = 0;

  for (int i = 0; i < 5000000; i++) {
    do {
      genA = (genA * 16807) % 2147483647;
    } while ((genA % 4) != 0);

    do {
      genB = (genB * 48271) % 2147483647;
    } while ((genB % 8) != 0);

    if ((genA & 0xFFFF) == (genB & 0xFFFF)) {
      part2Matches++;
    }
  }

  printf("Part 2: number of lower 16 matches: %d\n", part2Matches);

  return 0;
}
