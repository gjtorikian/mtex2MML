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
  memmove(str, str, len-1);
  str[len-1] = 0;
}

void remove_first_char(char* str)
{
  size_t len = strlen(str);
  memmove(str, str + 1, len);
}

void insert_substring(char **dest, char *ins, size_t location)
{
  size_t origsize = 0;
  size_t resize = 0;
  size_t inssize = 0;
  size_t destsize = strlen(&dest) + 1;

  if (!dest || !ins) {
    return;  // invalid parameter
  }

  if (strlen(ins) == 0) {
    return;  // invalid parameter
  }

  origsize = strlen(*dest);
  inssize = strlen(ins);
  resize = strlen(*dest) + inssize + 1; // 1 for the null terminator

  if (location > origsize) {
    return;  // invalid location, out of original string
  }

  // resize string to accommodate inserted string if necessary
  if (destsize < resize) {
    *dest = (char*)realloc(*dest, resize);
  }

  // move string to make room for insertion
  memmove(&(*dest)[location+inssize], &(*dest)[location], origsize - location);
  (*dest)[origsize + inssize] = '\0'; // null terminate string

  // insert string
  memcpy(&(*dest)[location], ins, inssize);
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

int empty_row_spacings(char *str)
{
  int len = strlen(str), i = 0;

  // Looking for a repeating pattern of "0em|", so bail if this fails
  if (len % 4 != 0) {
    return 0;
  }

  for (i = 0; i < len; i += 4) {
    if (str[i] != '0' || str[i + 1] != 'e' || str[i + 2] != 'm' || str[i + 3] != '|') {
      break;
    }
  }

  return i == len ? 1 : 0;
}

char * dupe_string(const char * s)
{
  size_t len = 1+strlen(s);
  char *p = malloc(len);

  return p ? memcpy(p, s, len) : NULL;
}

char *dupe_string_n(const char *s, size_t n)
{
  size_t l = strlen(s);

  if (l <= n) { return strdup(s); }

  char *rv = (char *)malloc(n + 1);
  strncpy(rv, s, n);
  rv[n] = 0;
  return rv;
}
