#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_PROGS 1454

struct Program {
  char* name;
  struct Program* parent;
  struct Program* children[8];
  int childrenLength;
  int weight;
  int totalWeight;

  // this is a bitfield.
  // bit 0 is this node. bit 1-9 are if children nodes were finished
  // this is 1 if all children were processed
  int needProcessing;
};

void freeprogram(struct Program* prog) {
  if (prog != NULL) {
    if (prog->name != NULL) {
      free(prog->name);
    }
  }
}

struct Program* findOrMake(struct Program* progs[NUM_OF_PROGS], char* name) {
  // ideally, would use a hash or binary search for this
  int i = 0;
  struct Program* p = NULL;

  for (; i < NUM_OF_PROGS; i++) {
    p = progs[i];
    if (p == NULL) {
      // "i" is now the index to insert at
      break;
    }

    if (strcmp(p->name, name) == 0) {
      // was malloc'd so lets send it free fallin
      free(name);
      return p;
    }
  }

  // never found anything, create a new one
  p = malloc(sizeof(struct Program));
  p->name = name;
  p->parent = NULL;
  p->children[0] = NULL;
  p->children[1] = NULL;
  p->children[2] = NULL;
  p->children[3] = NULL;
  p->children[4] = NULL;
  p->children[5] = NULL;
  p->children[6] = NULL;
  p->children[7] = NULL;
  p->childrenLength = 0;
  p->weight = 0;
  p->totalWeight = 0;
  p->needProcessing = 1;

  progs[i] = p;

  return p;
}

int main() {
  // the index is the program number, the int is the index+1 of the parent
  // then PART1: we just find the only one with no parent
  struct Program* progs[NUM_OF_PROGS];
  memset(progs, 0, sizeof(progs[0]) * NUM_OF_PROGS);

  FILE* fp = fopen("input.txt", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;

  while((read = getline(&line, &len, fp)) != -1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    // find space
    // 0->i is name
    // find (, then next ptr
    // find ) and atoi up to that
    // find >, then next ptr
    // while can keep finding a comma, that is a child
    char* startPtr = line;
    char* endPtr = line + 1;

    while (*endPtr != '\0' && *endPtr != ' ') {
      endPtr++;
    }

    int nameLength = endPtr - startPtr;
    char* name = malloc(sizeof(char) * nameLength + 1);
    strncpy(name, startPtr, nameLength);
    name[nameLength] = '\0';

    struct Program* prog = findOrMake(progs, name);

    int weight = 0;

    startPtr = endPtr + 2; // just past the open paren
    while (*endPtr != '\0' && *endPtr != ')') {
      endPtr++;
    }
    if (*endPtr == ')') {
      // just set it to NULL char to make atoi easy
      *endPtr = '\0';
      weight = atoi(startPtr);

      // and change back
      *endPtr = ')';
    }

    prog->weight = weight;
    prog->totalWeight = weight;

    int childrenLength = 0;

    startPtr = endPtr + 1;
    endPtr = endPtr + 2;

    if (*startPtr != '\0' && *endPtr == '-') {
      startPtr = endPtr + 3;
      endPtr = startPtr + 1;

      while (*startPtr != '\0') {
        while (*endPtr != '\0' && *endPtr != ',') {
          endPtr++;
        }

        int nameLength = endPtr - startPtr;
        char* name = malloc(sizeof(char) * nameLength + 1);
        strncpy(name, startPtr, nameLength);
        name[nameLength] = '\0';
        // printf("read in child named: '%s'\n", name);

        struct Program* child = findOrMake(progs, name);
        prog->children[childrenLength] = child;
        childrenLength++;
        prog->needProcessing |= (1 << childrenLength);
        child->parent = prog;

        if (*endPtr == '\0') {
          startPtr = endPtr;
        } else {
          startPtr = endPtr + 2; // skip ',' and ' '
          endPtr = startPtr + 1;
        }
      }

    }
    prog->childrenLength = childrenLength;

    // printf("created prog named: '%s' %d, %d %d\n", prog->name, prog->weight, prog->childrenLength, prog->needProcessing);
  }

  fclose(fp);
  if (line != NULL) {
    free(line);
    line = NULL;
  }

  // logic go here
  for (i = 0; i < NUM_OF_PROGS; i++) {
    if (progs[i] != NULL) {
      if (progs[i]->parent == NULL) {
        printf("Part 1: this node is root node: %s\n", progs[i]->name);
      }
    }
  }

  int keepScanning = 1;
  struct Program* prog = NULL;

  while (keepScanning > 0) {
    keepScanning = 0;

    for (i = 0; i < NUM_OF_PROGS; i++) {
      prog = progs[i];

      if (prog->needProcessing == 1) {
        keepScanning++;

        if (prog->childrenLength > 0) {
          int compareWeight = prog->children[0]->totalWeight;
          int childrenWeight = compareWeight;
          int perNodeWeight = compareWeight;
          struct Program* differentProg = NULL;

          // we know only, exactly, one is different, so we can take shortcuts
          for (int j = 1; j < prog->childrenLength; j++) {
            childrenWeight += prog->children[j]->totalWeight;

            if (prog->children[j]->totalWeight != compareWeight) {
              if (differentProg == NULL) {
                differentProg = prog->children[j];
                perNodeWeight = compareWeight;
              } else {
                differentProg = prog->children[0];
                perNodeWeight = prog->children[j]->totalWeight;
              }
            }
          }

          if (differentProg != NULL) {
            childrenWeight = perNodeWeight * prog->childrenLength;

            int diff = differentProg->totalWeight - perNodeWeight;
            int newWeight = differentProg->weight - diff;

            printf("Part 2: Found wrong weight program: '%s' %d should be %d\n", differentProg->name, differentProg->weight, newWeight);

            differentProg->weight = newWeight;
            differentProg->totalWeight = perNodeWeight;

            keepScanning = 0;
            break;
          }

          prog->totalWeight = prog->weight + childrenWeight;
        }

        prog->needProcessing = 0;
        if (prog->parent != NULL) {
          // find index and remove as needs processing
          for (int cIndex = 0; cIndex < prog->parent->childrenLength; cIndex++) {
            if (prog->parent->children[cIndex] == prog) {
              int newBitField = prog->parent->needProcessing & ~(1 << (cIndex + 1));
              prog->parent->needProcessing = newBitField;
              break;
            }
          }
        }
      }
    }
  }


  for (i = 0; i < NUM_OF_PROGS; i++) {
    if (progs[i] != NULL) {
      freeprogram(progs[i]);
      free(progs[i]);
      progs[i] = NULL;
    }
  }

  return 0;
}
