#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char kTokenOr[] = "OR";
const char kTokenAnd[] = "AND";
const char kTokenParenOpen[] = "(";
const char kTokenParenClose[] = ")";
const char kWhitespace[] = "\t\n\r ";
const char kTokenSeparators[] = "\t\n\r ()";

void WriteToken(const char* token_start, size_t token_size) {
  char* token = strndup(token_start, token_size);
  printf("%s\n", token);
  free(token);
}

size_t EatToken(const char* text) {
  // Skip whitespace
  size_t next_token = strspn(text, kWhitespace);
  if (next_token > 0)
    return next_token;

  // Check for separator tokens
  if (strncmp(text, kTokenParenOpen, 1) == 0) {
    WriteToken(kTokenParenOpen, 1);
    return 1;
  }
  if (strncmp(text, kTokenParenClose, 1) == 0) {
    WriteToken(kTokenParenClose, 1);
    return 1;
  }

  size_t token_size = strcspn(text, kTokenSeparators);

  if (token_size == 2 && strncmp(text, kTokenOr, 2) == 0) {
    WriteToken(kTokenOr, 2);
  } else if (token_size == 3 && strncmp(text, kTokenAnd, 3) == 0) {
    WriteToken(kTokenAnd, 3);
  } else {
    WriteToken(text, token_size);
  }

  return token_size;
}

void Tokenize(const char* line) {
  for (const char *current = line, *next = line; *current != '\0';
       current = next) {
    next = current + EatToken(current);
  }
}

int main() {
  // C-style version
  char *input_line = nullptr;
  size_t input_line_size = 0;
  while (getline(&input_line, &input_line_size, stdin) > 0) {
    Tokenize(input_line);
  }
  free(input_line);
}
