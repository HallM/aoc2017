#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 256

int main() {
  int list[LIST_SIZE];
  int lengthIndex = 0;
  int curPos = 0;
  int skip = 0;

  // int lengths[] = {3, 4, 1, 5};
  int lengths[] = {197, 97, 204, 108, 1, 29, 5, 71, 0, 50, 2, 255, 248, 78, 254, 63};
  int numOfLengths = sizeof(lengths) / sizeof(lengths[0]);

  for (curPos = 0; curPos < LIST_SIZE; curPos++) {
    list[curPos] = curPos;
  }

  for (lengthIndex = 0; lengthIndex < numOfLengths; lengthIndex++) {
    int length = lengths[lengthIndex];

    // do the reversals one pair at a time
    for (int i = 0, j = length - 1; i < j; i++, j--) {
      int listI = (i + curPos) % LIST_SIZE;
      int listJ = (j + curPos) % LIST_SIZE;

      int tmp = list[listI];
      list[listI] = list[listJ];
      list[listJ] = tmp;
    }

    curPos = (curPos + length + skip) % LIST_SIZE;
    skip++;
  }

  printf("Part 1: %d\n", (list[0] * list[1]));

  return 0;
}
