#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIREWALL_DEPTH 89
#define MAX_RUN_TIME 4194304
#define SCANNER_GUESS 128

int main() {
  int firewallRanges[FIREWALL_DEPTH];
  memset(firewallRanges, 0, sizeof(firewallRanges[0]) * FIREWALL_DEPTH);
  firewallRanges[0] = 3;
  firewallRanges[1] = 2;
  firewallRanges[2] = 4;
  firewallRanges[4] = 4;
  firewallRanges[6] = 5;
  firewallRanges[8] = 8;
  firewallRanges[10] = 6;
  firewallRanges[12] = 6;
  firewallRanges[14] = 6;
  firewallRanges[16] = 6;
  firewallRanges[18] = 8;
  firewallRanges[20] = 8;
  firewallRanges[22] = 12;
  firewallRanges[24] = 10;
  firewallRanges[26] = 9;
  firewallRanges[28] = 8;
  firewallRanges[30] = 8;
  firewallRanges[32] = 12;
  firewallRanges[34] = 12;
  firewallRanges[36] = 12;
  firewallRanges[38] = 12;
  firewallRanges[40] = 8;
  firewallRanges[42] = 12;
  firewallRanges[44] = 14;
  firewallRanges[46] = 14;
  firewallRanges[48] = 10;
  firewallRanges[50] = 12;
  firewallRanges[52] = 12;
  firewallRanges[54] = 14;
  firewallRanges[56] = 14;
  firewallRanges[58] = 14;
  firewallRanges[62] = 12;
  firewallRanges[64] = 14;
  firewallRanges[66] = 14;
  firewallRanges[68] = 14;
  firewallRanges[70] = 12;
  firewallRanges[74] = 14;
  firewallRanges[76] = 14;
  firewallRanges[78] = 14;
  firewallRanges[80] = 18;
  firewallRanges[82] = 17;
  firewallRanges[84] = 30;
  firewallRanges[88] = 14;

  // to make this easy to track:
  // the position is the absolute value
  // a positive number means it is moving in an increasing manner
  // a negative number means it is moving in a decreasing manner
  int firewallPositions[FIREWALL_DEPTH];
  memset(firewallPositions, 0, sizeof(firewallPositions[0]) * FIREWALL_DEPTH);

  // packets are the things moving and checking if they can make it
  // but it's special and limited. basically just going to wrap
  // it's only 89 steps to the end, so a 128 length array? yeaahh...
  // the index represents the time the scanner started % 1024
  int packets[SCANNER_GUESS];
  memset(packets, 0, sizeof(packets[0]) * SCANNER_GUESS);

  int foundAnswer = -1;
  int part1Severity = 0;
  // iterate
  // the index in the table tells you the start time
  // the value is the severity
  // want the first one with no severity

  for (int t = 0; t < MAX_RUN_TIME; t++) {
    // only move those that have changed
    int minMove = t - FIREWALL_DEPTH;
    if (minMove < 0) {
      minMove = 0;
    }

    for (int p = minMove; p <= t; p++) {
      int packetIndex = p % SCANNER_GUESS;

      // first determine packet position
      // take current time (t) - startTime (p)
      int packetPosition = t - p;

      if (packetPosition < 0) {
        continue;
      }
      if (packetPosition == 0) {
        packets[packetIndex] = 0;
      }

      if (packetPosition >= FIREWALL_DEPTH) {
        if (packets[packetIndex] == 0) {
          foundAnswer = p;
          break;
        } else {
          continue;
        }
      }

      // check for scanner detection
      if (firewallRanges[packetPosition] != 0 && firewallPositions[packetPosition] == 0) {
        // more or less, we track how many times it gets caught.
        if (p == 0) {
          part1Severity += packetPosition * firewallRanges[packetPosition];
        }
        packets[packetIndex]++;
      }
    }

    if (foundAnswer >= 0) {
      break;
    }

    // move scanners after the check
    for (int i = 0; i < FIREWALL_DEPTH; i++) {
      if (firewallRanges[i] == 0) {
        continue;
      }

      if (firewallPositions[i] == (firewallRanges[i] - 1)) {
        // reverse direction and move one
        firewallPositions[i] = (-1 * (firewallPositions[i] - 1));
      } else if (firewallPositions[i] == 0) {
        firewallPositions[i] = 1;
      } else {
        firewallPositions[i]++;
      }
    }

  }

  printf("Part 1: total severity leaving now: %d\n", part1Severity);
  if (foundAnswer != -1) {
    printf("Part 2: start time to make it through: %d: %d\n", foundAnswer, packets[foundAnswer % SCANNER_GUESS]);
  } else {
    printf("Part 2: did not find\n");
  }

  return 0;
}
