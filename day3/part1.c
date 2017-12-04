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

  // cell index is basically the number of cells *before* the maxNum
  // maxNum is located bottom right corner
  const int cellIndex = maxNum - input;
  int row = 0;
  int col = 0;

  printf("bottom right is %d, and cellIndex is %d\n", maxNum, cellIndex);

  if (cellIndex <= sizeOffOne) {
    // then bottom row
    row = sizeOffOne;
    col = sizeOffOne - cellIndex;
    printf("along bottom row\n");
  } else if (cellIndex <= (sizeOffOne * 2)) {
    // along the left side
    col = 0;
    row = (sizeOffOne * 2) - cellIndex;
    printf("along left side\n");
  } else if (cellIndex <= (sizeOffOne * 3)) {
    // along the top row
    row = 0;
    col = cellIndex - (sizeOffOne * 2);
    printf("along top row\n");
  } else {
    // along the right side
    col = sizeOffOne;
    row = cellIndex - (sizeOffOne * 3);
    printf("along right side\n");
  }

  printf("(row, col) => (%d,%d)\n", row, col);

  const int rowMoves = row > center ? (row - center) : (center - row);
  const int colMoves = col > center ? (col - center) : (center - col);
  const int totalMoves = rowMoves + colMoves;

  printf("Part 1: number of moves: (%d + %d) = %d\n", rowMoves, colMoves, totalMoves);

  return 0;
}
