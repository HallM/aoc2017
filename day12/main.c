#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_PROGS 2000
#define QUEUE_SIZE 1024

typedef struct Program {
  int connects[16];
  int numOfConnects;
  int visited;
} Program;

int main() {
  Program progs[NUM_OF_PROGS];
  memset(progs, 0, sizeof(progs[0]) * NUM_OF_PROGS);

  FILE* fp = fopen("input.txt", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  // first going to read all the lines in
  while((read = getline(&line, &len, fp)) != -1) {
    // 0 <-> 122, 874, 1940

    char* start = line;
    char* end = line + 1;

    while (*end != ' ') {
      end++;
    }
    *end = '\0';
    int progIndex = atoi(start);
    *end = ' ';

    start = end + 5;

    while (*end != '\n' && *end != '\0') {
      end = start + 1;

      while (*end != ',' && *end != '\n' && *end != '\0') {
        end++;
      }
      char keep = *end;
      *end = '\0';
      int connectIndex = atoi(start);
      progs[progIndex].connects[progs[progIndex].numOfConnects++] = connectIndex;
      *end = keep;

      start = end + 2;
    }
  }

  // set up a BFS queues
  int searchQueue[QUEUE_SIZE];
  int searchQueueLength = 1;
  memset(searchQueue, 0, sizeof(searchQueue[0]) * QUEUE_SIZE);
  searchQueue[0] = 0;

  int nextQueue[QUEUE_SIZE];
  int nextQueueLength = 0;
  memset(nextQueue, 0, sizeof(nextQueue[0]) * QUEUE_SIZE);

  // now start counting from node 0
  int totalVisited = 0;
  int totalGroups = 0;
  while (totalVisited < NUM_OF_PROGS) {
    // find an unvisited node to start scanning from
    int searchStart = 0;
    int totalCount = 0;
    for (; searchStart < NUM_OF_PROGS; searchStart++) {
      if (progs[searchStart].visited == 0) {
        // now start searching!
        searchQueueLength = 1;
        searchQueue[0] = searchStart;
        totalGroups++;
        break;
      }
    }

    while (searchQueueLength > 0) {
      for (int i = 0; i < searchQueueLength; i++) {
        Program* prog = &progs[searchQueue[i]];
        if (prog->visited == 0) {
          prog->visited = 1;
          totalCount++;
          totalVisited++;
        }

        for (int j = 0; j < prog->numOfConnects; j++) {
          int index = prog->connects[j];
          if (progs[index].visited == 0) {
            nextQueue[nextQueueLength++] = index;
          }
        }
      }

      // copy the next queue into the now search queue
      memcpy(searchQueue, nextQueue, sizeof(nextQueue[0]) * QUEUE_SIZE);
      memset(nextQueue, 0, sizeof(nextQueue[0]) * QUEUE_SIZE);
      searchQueueLength = nextQueueLength;
      nextQueueLength = 0;
    }

    if (searchStart == 0) {
      printf("Part 1: number in group with id %d: %d\n", searchStart, totalCount);
    }
  }

  printf("Part 2: number of groups: %d\n", totalGroups);

  fclose(fp);
  if (line) {
    free(line);
  }

  return 0;
}
