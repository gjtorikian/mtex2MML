#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_extras.h"

char *join(char* first, char* second)
{
  int first_length  =  strlen(first);
  int second_length = strlen(second);

  char * copy = (char *) malloc(first_length + second_length + 1); // +1 for the zero-terminator

  if (copy) {
    strcpy(copy, first);
    strcat(copy, second);
  }

  return copy;
}

void remove_last_char(char* str)
{
  size_t len = strlen(str);
  // XXX: This memmove isn't really doing anything since the source and destination are
  // the same.
  memmove(str, str, len-1);
  str[len-1] = 0;
}

void remove_first_char(char* str)
{
  size_t len = strlen(str);
  memmove(str, str + 1, len);
}

void strrev(char *str)
{
  char temp, *end_ptr;

  /* If str is NULL or empty, do nothing */
  if (str == NULL || !(*str) ) {
    return;
  }

  end_ptr = str + strlen(str) - 1;

  /* Swap the chars */
  while (end_ptr > str) {
    temp = *str;
    *str = *end_ptr;
    *end_ptr = temp;
    str++;
    end_ptr--;
  }
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
  char* buf = malloc(n+1);
  if (buf) {
    strncpy(buf, s, n);
    buf[n] = '\0';
  }
  return buf;
}
