#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse_extras.h"
#include "string_extras.h"
#include "stack.h"

#ifdef FLIP_OFFSET_VAL
#define OFFSET_VAL 0
#else
#define OFFSET_VAL 1
#endif

void initSymbolDataArray(symbolDataArray *a, size_t initialSize)
{
  // Allocate initial space
  a->array = (symbolData *)malloc(initialSize * sizeof(symbolData));

  a->used = 0;           // no elements used
  a->size = initialSize; // available number of elements

  // Initialize all elements of the array at once: they are contiguous
  memset(&a->array[0], 0, sizeof(symbolData) * initialSize);
}

void insertSymbolDataArray(symbolDataArray *a, symbolData element)
{
  if (a->used == a->size) {
      a->size *= 2;
      a->array = (symbolData *)realloc(a->array, a->size * sizeof(symbolData));
      // Initialize the last/new elements of the reallocated array
      memset(&a->array[a->used],0, sizeof(symbolData) * (a->size - a->used));
  }

  a->array[a->used].attribute = (char*)malloc(strlen(element.attribute) + 1);
  strcpy(a->array[a->used].attribute, element.attribute);

  a->array[a->used].offset_pos = element.offset_pos;

  a->used++;
}

void sortHLineDataArray(symbolDataArray *a) {
  int i, j, n = a->used;

  for(i = 1;i < n; i++) {
    for(j = 0;j < n - i; j++) {
      if(a->array[j].offset_pos < a->array[j+1].offset_pos) {
          symbolData temp = a->array[j];
          a->array[j] = a->array[j+1];
          a->array[j+1] = temp;
      }
    }
  }
}

void deleteSymbolDataArray(symbolDataArray *a)
{
  int i;

  // Free all name variables of each array element first
  for(i = 0; i <a->used; i++)
  {
    free(a->array[i].attribute);
    a->array[i].attribute = NULL;
  }

  // Now free the array
  free(a->array);
  a->array = NULL;

  a->used = 0;
  a->size = 0;
}

char * env_replacements(const char *string) {
  stackT array_stack;
  stackElementT stack_item, last_stack_item;

  char *tok = NULL;
  char *new_start = strdup(string);
  char *line = strtok(strdup(string), "\n");
  char *attr_rowlines = "", *attr_rowspacings = "", *em_str, *temp = "";

  const char *from = "\\begin", *until = "\\end", *hline = "\\hline", *hdashline = "\\hdashline",
             *line_separator = "\\\\",
             *em_pattern_begin = "[";

  int start = 0, offset = 0, attr_rowlines_len = 0, attr_rowspacings_len = 0, str_len = 0, i = 0;
  symbolDataArray symbol_data_array;
  symbolData symbol_data;

  // set up the array stack
  StackInit(&array_stack, strlen(new_start));
  initSymbolDataArray(&symbol_data_array, 5);

  // if not an environment, don't both going on
  if ((strstr(string, from) == NULL && strstr(string, until) == NULL))
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
        attr_rowlines_len = strlen(attr_rowlines);
        attr_rowspacings_len = strlen(attr_rowspacings);

        // looking for a line match
        if (strstr(last_stack_item.line, hline) != NULL) {
          if (attr_rowlines_len > 0)
            remove_last_char(attr_rowlines);
          attr_rowlines = join(attr_rowlines, "s");
        }
        else if (strstr(last_stack_item.line, hdashline) != NULL) {
          if (attr_rowlines_len > 0)
            remove_last_char(attr_rowlines);
          attr_rowlines = join(attr_rowlines, "d");
        }
        else {
          attr_rowlines = join(attr_rowlines, "0");
        }

        if (strstr(last_stack_item.line, line_separator) != NULL) {
          if ( (tok = strstr(last_stack_item.line, em_pattern_begin)) != NULL) {
            temp = tok + 1;
            if ( (tok = strstr(temp, "]")) != NULL) {
              offset = (int)(tok - temp);
              em_str = malloc(offset);
              memmove(em_str, temp, offset);
              attr_rowspacings = join(join(attr_rowspacings, em_str), "|");
              free(em_str);
            }
          }
          else {
            attr_rowspacings = join(attr_rowspacings, "~");
          }
        }
      }

      if (!StackIsEmpty(&array_stack)) // should never be empty, assuming appropriately closed array
        last_stack_item = StackPop(&array_stack); // now, modify the starting \begin with the symbol info

      if (attr_rowlines_len != 0) {
        // array is form of \begin{array}[t]{cc..c}
        if ( (tok = strstr(last_stack_item.line, "]{")) == NULL) {
          tok = strstr(last_stack_item.line, "}{"); // array is form of \begin{array}{cc..c}
        }

        offset = last_stack_item.line_pos + (tok - last_stack_item.line);
        // we cut the last char because we can skip the first row
        remove_last_char(attr_rowlines);
        // we reverse the string, because we're going backwards
        strrev(attr_rowlines);
        attr_rowlines = join(join("(", attr_rowlines), ")");
        symbol_data.attribute = strdup(attr_rowlines);
        symbol_data.offset_pos = offset + OFFSET_VAL;
        insertSymbolDataArray(&symbol_data_array, symbol_data);
      }

      attr_rowlines = "";
      attr_rowlines_len = 0;
    }

    line = strtok(NULL, "\n");
  }

  // sort array by highest values first, so that we can insert to new_start from the
  // bottom to the top (ensuring line numbers don't shift)
  sortHLineDataArray(&symbol_data_array);
  for (i = 0; i < symbol_data_array.used; i++) {
    insert_substring(&new_start, symbol_data_array.array[i].attribute, symbol_data_array.array[i].offset_pos);
    printf("Row lines %s\n", new_start);
  }

  StackDestroy(&array_stack);
  deleteSymbolDataArray(&symbol_data_array);

  return new_start;
}

const char *vertical_pipe_extract(const char *string) {
  char *orig = strdup(string);
  char *columnlines = "", *previous_column = "";
  int i = 0;

  if (strncmp(orig, "s", 1) == 0) {
    columnlines = "frame=\"solid\" columnlines=\"";
    remove_first_char(orig);
  }
  else if (strncmp(orig, "d", 1) == 0) {
    columnlines = "frame=\"dashed\" columnlines=\"";
    remove_first_char(orig);
  }
  else {
    columnlines = "columnlines=\"";
  }

  char *token = strtok(orig, " ");

  while (token != NULL) {
    if (strncmp(token, "s", 1) == 0) {
      previous_column = "s";
      columnlines = join(columnlines, "solid ");
    }
    else if (strncmp(token, "d", 1) == 0) {
      previous_column = "d";
      columnlines = join(columnlines, "dashed ");
    }
    else {
      if (i >= 1) { // we must skip the first blank col
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

  // an empty string here angers Lasem
  if (strncmp(columnlines, "columnlines=\"\0", 14) == 0)
    columnlines = "columnlines=\"none";
  // an empty space also angers Lasem
  else
    remove_last_char(columnlines);

  return columnlines;
}

const char *remove_excess_pipe_chars(const char *string) {
  char *dup = strdup(string);

  dup = replace_str(dup, "s", "");
  dup = replace_str(dup, "d", "");

  return dup;
}
