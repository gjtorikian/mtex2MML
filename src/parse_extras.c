#include <stdlib.h>
#include <string.h>

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

char *substring(char *inpStr, int startPos, int strLen) {
  /* Cannot do anything with NULL. */

  if (inpStr == NULL) return NULL;

  char *buff;

  /* All negative positions to go from end, and cannot
     start before start of string, force to start. */

  if (startPos < 0)
      startPos = strlen (inpStr) + startPos;
  if (startPos < 0)
      startPos = 0;

  /* Force negative lengths to zero and cannot
     start after end of string, force to end. */

  if (strLen < 0)
      strLen = 0;
  if (startPos >strlen (inpStr))
      startPos = strlen (inpStr);

  /* Adjust length if source string too short. */

  if (strLen > strlen (&inpStr[startPos]))
      strLen = strlen (&inpStr[startPos]);

  /* Get long enough string from heap, return NULL if no go. */

  if ((buff = malloc(strLen + 1)) == NULL)
      return NULL;

  /* Transfer string section and return it. */

  memcpy (buff, &(inpStr[startPos]), strLen);
  buff[strLen] = '\0';

  return buff;
}

char *join(char* s1, char* s2) {
  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);
  char *result = malloc(len1 + len2 + 1); // +1 for the zero-terminator

  memcpy(result, s1, len1);
  memcpy(result+len1, s2, len2 + 1); // +1 to copy the null-terminator

  return result;
}

void remove_last_char(char* str) {
  size_t len = strlen(str);
  memmove(str, str, len-1);
  str[len-1] = 0;
}

void insert_substring(char *str, char *new_str, int position) {
   char *f, *e;
   size_t length = strlen(str);

   f = substring(str, 1, position - 1 );
   e = substring(str, position, length-position+1);

   strcpy(str, "");
   strcat(str, f);
   free(f);
   strcat(str, new_str);
   strcat(str, e);
   free(e);
}

char * hline_replace(const char *string) {
  char *tok = NULL, *chunk = NULL;
  char *newstr = strdup(string);
  const char *from = "\\begin", *until = "\\end", *hline = "\\hline", *hdashline = "\\hdashline";
  char *s = newstr, *e = newstr, *attr_strings = "";
  int substr_count = 0, n_count = 0, start = 0, end = 0, i = 0, offset = 0, attr_strings_len = 0;

  while (1) {
    // find the starting match
    s = strstr(s, from);
    if (!s) break;
    start = (int)(newstr - s);

    // find the ending match
    e = strstr(e, until);
    if (!e) break;
    end = (int)(newstr - e);

    // how big is this string?
    int array_length = abs(end - start);

    // this is just the "from - until" string chunk
    chunk = substring(newstr, abs(start), array_length);

    char *line = strtok(chunk, "\n");
    while(line != NULL)
    {
      if (n_count >= 2) {
        attr_strings_len = strlen(attr_strings);

        // looking for a line match
        if (strstr(line, hline) != NULL) {
          if (attr_strings_len > 0)
            remove_last_char(attr_strings);
          attr_strings = join(attr_strings, "s");
        }
        else if (strstr(line, hdashline) != NULL) {
          if (attr_strings_len > 0)
            remove_last_char(attr_strings);
          attr_strings = join(attr_strings, "d");
        }
        else {
          attr_strings = join(attr_strings, "0");
        }
      }
      else
        n_count++;

      line = strtok(NULL, "\n");
    }

    // array is form of \begin{array}[t]{cc..c}
    if ( (tok = strstr(chunk, "]{")) != NULL && strncmp(attr_strings, "", 1) != 0) {
      offset = (int)(tok - chunk) + 1;
      attr_strings = join(join("(", attr_strings), ")");
      insert_substring(newstr, attr_strings, -start + offset);
    }
    // array is form of \begin{array}{cc..c}
    else if ( (tok = strstr(chunk, "}{")) != NULL && strncmp(attr_strings, "", 1) != 0) {
      offset = (int)(tok - chunk) + 1;
      attr_strings = join(join("(", attr_strings), ")");
      insert_substring(newstr, attr_strings, -start + offset);
    }

    s = e + 1;
  }

  return newstr;
}

const char *vertical_pipe_replace(const char *string) {
  return string;
}
