#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_BANKS 16
#define SEEN_GUESS 4096

void copyCurrentIntoSlot(int current[NUM_OF_BANKS], int seenTables[SEEN_GUESS][NUM_OF_BANKS], int slot) {
  for (int i = 0; i < NUM_OF_BANKS; i++) {
    seenTables[slot][i] = current[i];
  }
}

int hasSeenCurrent(int current[NUM_OF_BANKS], int seenTables[SEEN_GUESS][NUM_OF_BANKS], int nextSlot) {
  for (int j = 0; j < nextSlot; j++) {
    int matches = 0;

    for (int i = 0; i < NUM_OF_BANKS; i++) {
      if (seenTables[j][i] == current[i]) {
        matches++;
      }
    }

    if (matches == NUM_OF_BANKS) {
      return j;
    }
  }

  return -1;
}

int main() {
  int current[NUM_OF_BANKS] = {
    // 0, 2, 7, 0
    2, 8, 8, 5, 4, 2, 3, 1, 5, 5, 1, 2, 15, 13, 5, 14
  };

  int seenTables[SEEN_GUESS][NUM_OF_BANKS];
  memset(seenTables, 0, sizeof(int) * NUM_OF_BANKS * SEEN_GUESS);

  int nextSlot = 0;
  int lastSeen = -1;

  while (nextSlot < SEEN_GUESS && (lastSeen = hasSeenCurrent(current, seenTables, nextSlot)) == -1) {
    // copy the current state in
    copyCurrentIntoSlot(current, seenTables, nextSlot);
    nextSlot++;

    // find the max
    int indexOfMax = NUM_OF_BANKS - 1;
    int numToDist = current[indexOfMax];

    for (int i = indexOfMax - 1; i >= 0; i--) {
      int val = current[i];
      if (val >= numToDist) {
        indexOfMax = i;
        numToDist = val;
      }
    }

    // do the distribution
    current[indexOfMax] = 0;
    while (numToDist > 0) {
      indexOfMax = (indexOfMax + 1) % NUM_OF_BANKS;
      current[indexOfMax]++;
      numToDist--;
    }
  }

  printf("Part1 answer: %d\n", nextSlot);
  printf("Part2 answer: %d\n", (nextSlot - lastSeen));

  return 0;
}

