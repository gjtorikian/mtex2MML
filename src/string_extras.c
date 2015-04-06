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

char *strdup(const char *s)
{
  return strndup(s, strlen(s));
}

char *strndup(const char *s, size_t n)
{
  char* buf = malloc(n + 1);
  if (buf) {
    strncpy(buf, s, n);
    buf[n] = '\0';
  }
  return buf;
}

char * str_replace (char *string, const char *substr, const char *replacement)
{
  char *tok = NULL;
  char *newstr = NULL;
  char *oldstr = NULL;

  /* if either substr or replacement is NULL, duplicate string a let caller handle it */

  if ( substr == NULL || replacement == NULL )
  {
    return strdup(string);
  }

  newstr = strdup(string);

  while ( ( tok = strstr( newstr, substr ) ) )
  {

    oldstr = newstr;
    newstr = malloc ( strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) + 1 );

    /* If failed to alloc mem, free old string and return NULL */
    if ( newstr == NULL )
    {
      free (oldstr);
      return NULL;
    }

    memcpy ( newstr, oldstr, tok - oldstr );
    memcpy ( newstr + (tok - oldstr), replacement, strlen ( replacement ) );
    memcpy ( newstr + (tok - oldstr) + strlen( replacement ), tok + strlen ( substr ), strlen ( oldstr ) - strlen ( substr ) - ( tok - oldstr ) );
    memset ( newstr + strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) , 0, 1 );

    free (oldstr);
  }

  return newstr;
}
