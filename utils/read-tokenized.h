#ifndef READ_TOKENIZED_H
#define READ_TOKENIZED_H 1

#include <stdio.h>
#include <stdlib.h>

struct TokenizedReader {
  FILE* fp;
  const char* delim;
  char* currentLine;
  char* currentToken;
};

struct TokenizedReader* makereader(const char* filePath, const char* delim) {
  FILE* fp = fopen(filePath, "r");

  struct TokenizedReader* reader = malloc(sizeof(struct TokenizedReader));
  reader->fp = fp;
  reader->delim = delim;
  reader->currentLine = NULL;
  reader->currentToken = NULL;

  return reader;
}

ssize_t nextline(struct TokenizedReader* reader) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  reader->currentToken = NULL;
  read = getline(&line, &len, reader->fp);

  if (read > 1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }
  }
  reader->currentLine = line;

  return read;
}

char* nexttoken(struct TokenizedReader* reader) {
  reader->currentToken = strtok(reader->currentToken == NULL ? reader->currentLine : NULL, reader->delim);
  return reader->currentToken;
}

void freereader(struct TokenizedReader* reader) {
  if (reader->currentLine != NULL) {
    free(reader->currentLine);
  }

  fclose(reader->fp);
  free(reader);
}

#endif
