#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_SIZE 256

int main() {
  int list[LIST_SIZE];
  int lengthIndex = 0;
  int curPos = 0;
  int skip = 0;
  int rounds = 64;

  const char* input = "197,97,204,108,1,29,5,71,0,50,2,255,248,78,254,63";
  int inputLength = strlen(input);
  int numOfLengths = inputLength + 5;

  int lengths[numOfLengths];
  for (int i = 0; i < inputLength; i++) {
    lengths[i] = (int)input[i];
  }
  lengths[inputLength] = 17;
  lengths[inputLength + 1] = 31;
  lengths[inputLength + 2] = 73;
  lengths[inputLength + 3] = 47;
  lengths[inputLength + 4] = 23;

  for (curPos = 0; curPos < LIST_SIZE; curPos++) {
    list[curPos] = curPos;
  }

  curPos = 0;

  for (; rounds > 0; rounds--) {
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
  }

  printf("Part 2: ");
  for (curPos = 0; curPos < LIST_SIZE; curPos += 16) {
    int num =
      list[curPos]
      ^ list[curPos + 1]
      ^ list[curPos + 2]
      ^ list[curPos + 3]
      ^ list[curPos + 4]
      ^ list[curPos + 5]
      ^ list[curPos + 6]
      ^ list[curPos + 7]
      ^ list[curPos + 8]
      ^ list[curPos + 9]
      ^ list[curPos + 10]
      ^ list[curPos + 11]
      ^ list[curPos + 12]
      ^ list[curPos + 13]
      ^ list[curPos + 14]
      ^ list[curPos + 15]
      ;

    printf("%02x", num);
  }

  printf("\n");

  return 0;
}
