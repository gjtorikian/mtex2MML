#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_extras.h"

void remove_last_char(char* str)
{
  size_t len = strlen(str);
  str[len - 1] = '\0';
}

void remove_first_char(char* str)
{
  size_t len = strlen(str);
  memmove(str, str + 1, len);
}

char *dupe_string(const char * str)
{
  int len = strlen(str) + 1;
  char *buf = malloc(len);
  if (buf) { memcpy(buf, str, len); }
  return buf;
}

char *dupe_string_n(const char *s, size_t n)
{
  char* buf = malloc(n + 1);
  if (buf) {
    strncpy(buf, s, n);
    buf[n] = '\0';
  }
  return buf;
}
