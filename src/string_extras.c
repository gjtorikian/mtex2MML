#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_extras.h"

char *replace_str(const char *str, const char *old, const char *new) {
  char *ret, *r;
  const char *p, *q;
  size_t oldlen = strlen(old);
  size_t count, retlen, newlen = strlen(new);

  if (oldlen != newlen) {
    for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
      count++;
    /* this is undefined if p - str > PTRDIFF_MAX */
    retlen = p - str + strlen(p) + count * (newlen - oldlen);
  } else
    retlen = strlen(str);

  if ((ret = malloc(retlen + 1)) == NULL)
    return NULL;

  for (r = ret, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen) {
    /* this is undefined if q - p > PTRDIFF_MAX */
    int l = q - p;
    memcpy(r, p, l);
    r += l;
    memcpy(r, new, newlen);
    r += newlen;
  }
  strcpy(r, p);

  return ret;
}

char *join(char* first, char* second) {
  int first_length  =  strlen(first);
  int second_length = strlen(second);

  char * copy = (char *) malloc(first_length + second_length  + 1); // +1 for the zero-terminator

  if (copy) {
    strcpy(copy, first);
    strcat(copy, second);
  }

  return copy;
}

void remove_last_char(char* str) {
  size_t len = strlen(str);
  memmove(str, str, len-1);
  str[len-1] = 0;
}

void insert_substring(char **dest, char *ins, size_t location) {
  size_t origsize = 0;
  size_t resize = 0;
  size_t inssize = 0;
  size_t destsize = strlen(&dest) + 1;

  if (!dest || !ins)
      return;  // invalid parameter

  if (strlen(ins) == 0)
    return; // invalid parameter

  origsize = strlen(*dest);
  inssize = strlen(ins);
  resize = strlen(*dest) + inssize + 1; // 1 for the null terminator

  if (location > origsize)
    return; // invalid location, out of original string

  // resize string to accommodate inserted string if necessary
  if (destsize < resize)
    *dest = (char*)realloc(*dest, resize);

  // move string to make room for insertion
  memmove(&(*dest)[location+inssize], &(*dest)[location], origsize - location);
  (*dest)[origsize + inssize] = '\0'; // null terminate string

  // insert string
  memcpy(&(*dest)[location], ins, inssize);
}

void strrev(char *str) {
  char temp, *end_ptr;

  /* If str is NULL or empty, do nothing */
  if (str == NULL || !(*str) )
    return;

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
