#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse_extras.h"
#include "stack.h"

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
  if (startPos > strlen (inpStr))
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

char *join(char* first, char* second) {
  int  first_length =  strlen(first);
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
  if( str == NULL || !(*str) )
    return;

  end_ptr = str + strlen(str) - 1;

  /* Swap the chars */
  while( end_ptr > str ) {
    temp = *str;
    *str = *end_ptr;
    *end_ptr = temp;
    str++;
    end_ptr--;
  }
}

void initHlineDataArray(hlineDataArray *a, size_t initialSize)
{
  // Allocate initial space
  a->array = (hlineData *)malloc(initialSize * sizeof(hlineData));

  a->used = 0;           // no elements used
  a->size = initialSize; // available number of elements

  // Initialize all elements of the array at once: they are contiguous
  memset(&a->array[0], 0, sizeof(hlineData) * initialSize);
}

void insertHlineDataArray(hlineDataArray *a, hlineData element)
{
  if (a->used == a->size) {
      a->size *= 2;
      a->array = (hlineData *)realloc(a->array, a->size * sizeof(hlineData));
      // Initialize the last/new elements of the reallocated array
      memset(&a->array[a->used],0, sizeof(hlineData) * (a->size - a->used));
  }

  a->array[a->used].attr_strings = (char*)malloc(strlen(element.attr_strings) + 1);
  strcpy(a->array[a->used].attr_strings, element.attr_strings);

  a->array[a->used].offset_pos = element.offset_pos;

  a->used++;
}

void sortHLineDataArray(hlineDataArray *a) {
  int i, j, n = a->used;

  for(i = 1;i < n; i++) {
    for(j = 0;j < n - i; j++) {
      if(a->array[j].offset_pos < a->array[j+1].offset_pos) {
          hlineData temp = a->array[j];
          a->array[j] = a->array[j+1];
          a->array[j+1] = temp;
      }
    }
  }
}

void deleteHlineDataArray(hlineDataArray *a)
{
  // Free all name variables of each array element first
  for(int i = 0; i <a->used; i++)
  {
    free(a->array[i].attr_strings);
    a->array[i].attr_strings = NULL;
  }

  // Now free the array
  free(a->array);
  a->array = NULL;

  a->used = 0;
  a->size = 0;
}

char * hline_replace(const char *string) {
  stackT array_stack;
  char *tok = NULL, *chunk = NULL;
  char *newstr = strdup(string);
  char *line = strtok(strdup(string), "\n");
  const char *from = "\\begin", *until = "\\end", *hline = "\\hline", *hdashline = "\\hdashline";
  char *s = newstr, *e = newstr, *attr_strings = "";
  stackElementT stack_item, last_stack_item;
  int n_count = 0, start = 0, end = 0, offset = 0, attr_strings_len = 0, str_len = 0;
  hlineDataArray hline_data_array;
  hlineData hline_data;

  // set up the array stack
  StackInit(&array_stack, strlen(newstr));
  initHlineDataArray(&hline_data_array, 5);

  // if none of the array environments, or hline/hdashline, exist, don't bother going on
  if ((strstr(string, from) == NULL && strstr(string, until) == NULL) || (strstr(string, hline) == NULL && strstr(string, hdashline) == NULL))
    return string;

  while (line != NULL) {
    str_len = strlen(line) + 1;

    stack_item.line = line;
    stack_item.line_pos = start + 1;

    start += str_len;

    StackPush(&array_stack, stack_item);

    if (strstr(line, until) != NULL) {
      while (!StackIsEmpty(&array_stack) && strstr(StackTop(&array_stack).line, from) == NULL) {
        last_stack_item = StackPop(&array_stack);
        attr_strings_len = strlen(attr_strings);

        // looking for a line match
        if (strstr(last_stack_item.line, hline) != NULL) {
          if (attr_strings_len > 0)
            remove_last_char(attr_strings);
          attr_strings = join(attr_strings, "s");
        }
        else if (strstr(last_stack_item.line, hdashline) != NULL) {
          if (attr_strings_len > 0)
            remove_last_char(attr_strings);
          attr_strings = join(attr_strings, "d");
        }
        else {
          attr_strings = join(attr_strings, "0");
        }
      }

      if (!StackIsEmpty(&array_stack)) // should never be empty, assuming appropriately closed array
        last_stack_item = StackPop(&array_stack); // now, modify the starting \begin with the hline info

      if (attr_strings_len != 0) {
        // array is form of \begin{array}[t]{cc..c}
        if ( (tok = strstr(last_stack_item.line, "]{")) != NULL && strncmp(attr_strings, "", 1) != 0) {
          offset = last_stack_item.line_pos + (tok - last_stack_item.line);
          // we cut the last char because we can skip the first row
          remove_last_char(attr_strings);
          // we reverse the string, because we're going backwards
          strrev(attr_strings);
          attr_strings = join(join("(", attr_strings), ")");
          hline_data.attr_strings = strdup(attr_strings);
          hline_data.offset_pos = offset + 1;
          insertHlineDataArray(&hline_data_array, hline_data);
        }
        // array is form of \begin{array}{cc..c}
        else if ( (tok = strstr(last_stack_item.line, "}{")) != NULL && strncmp(attr_strings, "", 1) != 0) {
          offset = last_stack_item.line_pos + (tok - last_stack_item.line);
          // we cut the last char because we can skip the first row
          remove_last_char(attr_strings);
          // we reverse the string, because we're going backwards
          strrev(attr_strings);
          attr_strings = join(join("(", attr_strings), ")");
          hline_data.attr_strings = strdup(attr_strings);
          hline_data.offset_pos = offset + 1;
          insertHlineDataArray(&hline_data_array, hline_data);
        }
      }

      attr_strings = "";
      attr_strings_len = 0;
    }

    line = strtok(NULL, "\n");
  }

  // sort array by highes value first, so that we can insert to newstr from the
  // bottom to the top (ensuring line numbers stay accurate)
  sortHLineDataArray(&hline_data_array);
  for (int i = 0; i < hline_data_array.used; i++) {
    insert_substring(&newstr, hline_data_array.array[i].attr_strings, hline_data_array.array[i].offset_pos);
  }

  StackDestroy(&array_stack);
  deleteHlineDataArray(&hline_data_array);

  return newstr;
}

const char *vertical_pipe_extract(const char *string) {
  char *orig = strdup(string), *token = strtok(orig, " ");
  char *columnlines = "", *previous_column = "";
  int i = 0;

  while (token != NULL) {
    if (strncmp(token, "s", 1) == 0) {
      if (i == 0)
        columnlines = "frame=\"solid\" columnlines=\"";
      else {
        previous_column = "s";
        columnlines = join(columnlines, "solid ");
      }
    }
    else if (strncmp(token, "d", 1) == 0) {
      if (i == 0)
        columnlines = "frame=\"dashed\" columnlines=\"";
      else {
        previous_column = "d";
        columnlines = join(columnlines, "dashed ");
      }
    }
    else {
      if (i == 0) // we must skip the first blank col
        columnlines = "columnlines=\"";
      else if (i > 1) {
        // only if there is no previous border should a border be considered, eg. "cc", not "c|c"
        if (strncmp(previous_column, "s", 1) != 0 && strncmp(previous_column, "d", 1) != 0) {
          columnlines = join(columnlines, "none ");
        }
        previous_column = "0";
      }
    }

    i++;
    token = strtok(NULL, " ");
  }

  return columnlines;
}

const char *remove_excess_pipe_chars(const char *string) {
  char *dup = strdup(string);

  dup = replace_str(dup, "s", "");
  dup = replace_str(dup, "d", "");

  return dup;
}
