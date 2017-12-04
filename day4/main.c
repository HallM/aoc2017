#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *fp = fopen("passphrases.txt", "r");
  if (fp == NULL) {
    return -1;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int numValid = 0;

  while ((read = getline(&line, &len, fp)) != -1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }

    int isValid = 1;
    char *words[32];
    int usedSlots = 0;
    memset(words, 0, sizeof(words[0]) * 32);

    char *tok = strtok(line, " ");
    while (tok != NULL) {
      int toklen = strlen(tok);
      char *cpy = malloc(toklen + 1);
      // part 1:
      // strcpy(cpy, tok);

      // part 2:
      // manual copy, so that we can order things
      for (int nextCharIndex = 0; nextCharIndex < toklen; nextCharIndex++) {
        char nextChar = tok[nextCharIndex];
        int insertIndex = 0;

        for (; insertIndex < nextCharIndex; insertIndex++) {
          char thisChar = cpy[insertIndex];
          if (nextChar < thisChar) {
            // shift things down before inserting here
            for (int idx = nextCharIndex; idx > insertIndex; idx--) {
              cpy[idx] = cpy[idx - 1];
            }
            break;
          }
        }

        cpy[insertIndex] = nextChar;
      }

      // gotta end it in the NULL char
      cpy[toklen] = '\0';

      for (int i = 0; i < usedSlots; i++) {
        if (strcmp(cpy, words[i]) == 0) {
          // then they are equal and we have a duplicate
          isValid = 0;
          break;
        }
      }

      if (isValid == 0) {
        break;
      }

      words[usedSlots] = cpy;
      usedSlots++;

      tok = strtok(NULL, " ");
    }

    if (isValid == 1) {
      numValid++;
    }

    for (int i = 0; i < usedSlots; i++) {
      free(words[i]);
    }
  }

  printf("Number of valid passphrases: %d\n", numValid);

  fclose(fp);
  if (line) {
    free(line);
  }

  return 0;
}
