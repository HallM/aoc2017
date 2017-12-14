#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_SIZE 256
#define NUM_ROWS 128

typedef struct {
  unsigned char hash[16];
} KnotHash;

int bitsSetInByte(unsigned char thebyte) {
  int bits = 0;
  if (thebyte & (1)) {
    bits++;
  }
  if (thebyte & (1 << 1)) {
    bits++;
  }
  if (thebyte & (1 << 2)) {
    bits++;
  }
  if (thebyte & (1 << 3)) {
    bits++;
  }
  if (thebyte & (1 << 4)) {
    bits++;
  }
  if (thebyte & (1 << 5)) {
    bits++;
  }
  if (thebyte & (1 << 6)) {
    bits++;
  }
  if (thebyte & (1 << 7)) {
    bits++;
  }
  return bits;
}

int bitsSetInHash(KnotHash* hash) {
  return
    bitsSetInByte(hash->hash[0])
    + bitsSetInByte(hash->hash[1])
    + bitsSetInByte(hash->hash[2])
    + bitsSetInByte(hash->hash[3])
    + bitsSetInByte(hash->hash[4])
    + bitsSetInByte(hash->hash[5])
    + bitsSetInByte(hash->hash[6])
    + bitsSetInByte(hash->hash[7])
    + bitsSetInByte(hash->hash[8])
    + bitsSetInByte(hash->hash[9])
    + bitsSetInByte(hash->hash[10])
    + bitsSetInByte(hash->hash[11])
    + bitsSetInByte(hash->hash[12])
    + bitsSetInByte(hash->hash[13])
    + bitsSetInByte(hash->hash[14])
    + bitsSetInByte(hash->hash[15])
  ;
}

KnotHash computeHash(const char* input) {
  int list[LIST_SIZE];
  int lengthIndex = 0;
  int curPos = 0;
  int skip = 0;
  int rounds = 64;

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

  KnotHash hashToReturn;
  int hashIndex = 0;
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

    unsigned char thebyte = (unsigned char)(num & 0xFF);
    hashToReturn.hash[hashIndex++] = thebyte;
  }

  return hashToReturn;
}

void unsetGroup(unsigned char bitmap[NUM_ROWS][NUM_ROWS], int i, int j) {
  if (bitmap[i][j] == 0) {
    return;
  }

  bitmap[i][j] = 0;

  if (j > 0) {
    unsetGroup(bitmap, i, j - 1);
  }
  if (j < (NUM_ROWS - 1)) {
    unsetGroup(bitmap, i, j + 1);
  }
  if (i > 0) {
    unsetGroup(bitmap, i - 1, j);
  }
  if (i < (NUM_ROWS - 1)) {
    unsetGroup(bitmap, i + 1, j);
  }
}

int main() {
  const char* rowHashes[NUM_ROWS] = {
    "jxqlasbh-0",
    "jxqlasbh-1",
    "jxqlasbh-2",
    "jxqlasbh-3",
    "jxqlasbh-4",
    "jxqlasbh-5",
    "jxqlasbh-6",
    "jxqlasbh-7",
    "jxqlasbh-8",
    "jxqlasbh-9",
    "jxqlasbh-10",
    "jxqlasbh-11",
    "jxqlasbh-12",
    "jxqlasbh-13",
    "jxqlasbh-14",
    "jxqlasbh-15",
    "jxqlasbh-16",
    "jxqlasbh-17",
    "jxqlasbh-18",
    "jxqlasbh-19",
    "jxqlasbh-20",
    "jxqlasbh-21",
    "jxqlasbh-22",
    "jxqlasbh-23",
    "jxqlasbh-24",
    "jxqlasbh-25",
    "jxqlasbh-26",
    "jxqlasbh-27",
    "jxqlasbh-28",
    "jxqlasbh-29",
    "jxqlasbh-30",
    "jxqlasbh-31",
    "jxqlasbh-32",
    "jxqlasbh-33",
    "jxqlasbh-34",
    "jxqlasbh-35",
    "jxqlasbh-36",
    "jxqlasbh-37",
    "jxqlasbh-38",
    "jxqlasbh-39",
    "jxqlasbh-40",
    "jxqlasbh-41",
    "jxqlasbh-42",
    "jxqlasbh-43",
    "jxqlasbh-44",
    "jxqlasbh-45",
    "jxqlasbh-46",
    "jxqlasbh-47",
    "jxqlasbh-48",
    "jxqlasbh-49",
    "jxqlasbh-50",
    "jxqlasbh-51",
    "jxqlasbh-52",
    "jxqlasbh-53",
    "jxqlasbh-54",
    "jxqlasbh-55",
    "jxqlasbh-56",
    "jxqlasbh-57",
    "jxqlasbh-58",
    "jxqlasbh-59",
    "jxqlasbh-60",
    "jxqlasbh-61",
    "jxqlasbh-62",
    "jxqlasbh-63",
    "jxqlasbh-64",
    "jxqlasbh-65",
    "jxqlasbh-66",
    "jxqlasbh-67",
    "jxqlasbh-68",
    "jxqlasbh-69",
    "jxqlasbh-70",
    "jxqlasbh-71",
    "jxqlasbh-72",
    "jxqlasbh-73",
    "jxqlasbh-74",
    "jxqlasbh-75",
    "jxqlasbh-76",
    "jxqlasbh-77",
    "jxqlasbh-78",
    "jxqlasbh-79",
    "jxqlasbh-80",
    "jxqlasbh-81",
    "jxqlasbh-82",
    "jxqlasbh-83",
    "jxqlasbh-84",
    "jxqlasbh-85",
    "jxqlasbh-86",
    "jxqlasbh-87",
    "jxqlasbh-88",
    "jxqlasbh-89",
    "jxqlasbh-90",
    "jxqlasbh-91",
    "jxqlasbh-92",
    "jxqlasbh-93",
    "jxqlasbh-94",
    "jxqlasbh-95",
    "jxqlasbh-96",
    "jxqlasbh-97",
    "jxqlasbh-98",
    "jxqlasbh-99",
    "jxqlasbh-100",
    "jxqlasbh-101",
    "jxqlasbh-102",
    "jxqlasbh-103",
    "jxqlasbh-104",
    "jxqlasbh-105",
    "jxqlasbh-106",
    "jxqlasbh-107",
    "jxqlasbh-108",
    "jxqlasbh-109",
    "jxqlasbh-110",
    "jxqlasbh-111",
    "jxqlasbh-112",
    "jxqlasbh-113",
    "jxqlasbh-114",
    "jxqlasbh-115",
    "jxqlasbh-116",
    "jxqlasbh-117",
    "jxqlasbh-118",
    "jxqlasbh-119",
    "jxqlasbh-120",
    "jxqlasbh-121",
    "jxqlasbh-122",
    "jxqlasbh-123",
    "jxqlasbh-124",
    "jxqlasbh-125",
    "jxqlasbh-126",
    "jxqlasbh-127"
  };

  unsigned char bitmap[NUM_ROWS][NUM_ROWS];

  int totalBitsSet = 0;

  for (int i = 0; i < NUM_ROWS; i++) {
    KnotHash hash = computeHash(rowHashes[i]);

    for (int j = 0; j < 16; j++) {
      unsigned char thebyte = hash.hash[j];
      int colStart = j * 8;

      bitmap[i][colStart] = thebyte & (1 << 7);
      bitmap[i][colStart + 1] = thebyte & (1 << 6);
      bitmap[i][colStart + 2] = thebyte & (1 << 5);
      bitmap[i][colStart + 3] = thebyte & (1 << 4);
      bitmap[i][colStart + 4] = thebyte & (1 << 3);
      bitmap[i][colStart + 5] = thebyte & (1 << 2);
      bitmap[i][colStart + 6] = thebyte & (1 << 1);
      bitmap[i][colStart + 7] = thebyte & (1);
    }

    int rowBits = bitsSetInHash(&hash);
    totalBitsSet += rowBits;
  }

  int totalRegions = 0;
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_ROWS; j++) {
      if (bitmap[i][j]) {
        totalRegions++;
        unsetGroup(bitmap, i, j);
      }
    }
  }

  printf("Part 1: total bits set: %d\n", totalBitsSet);
  printf("Part 2: number of regions: %d\n", totalRegions);

  return 0;
}
