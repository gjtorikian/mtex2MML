#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_extras.h"
#include "string_extras.h"

static const char *BEGIN = "\\begin";
static const char *END = "\\end";
static const char *beginSVG = "begin{svg}";

int determine_environment(const char *environment)
{
  if (strstr(environment, "\\end{smallmatrix}") != NULL) {
    return ENV_SMALLMATRIX;
  } else if (strstr(environment, "\\end{gathered}") != NULL) {
    return ENV_GATHERED;
  } else if (strstr(environment, "\\end{eqnarray") != NULL) {
    return ENV_EQNARRAY;
  } else if (strstr(environment, "\\end{multline") != NULL) {
    return ENV_MULTLINE;
  } else if (strstr(environment, "\\end{alignat") != NULL) {
    return ENV_ALIGNAT;
  } else if (strstr(environment, "\\end{aligned}") != NULL) {
    return ENV_ALIGNED;
  } else if (strstr(environment, "\\end{equation}") != NULL) {
    return ENV_EQUATION;
  } else if (strstr(environment, "\\end{align}") != NULL) {
    return ENV_ALIGN;
  }

  return OTHER;
}

void env_replacements(UT_array **environment_data_stack, encaseType * encase, const char *environment)
{
  // if not an environment, don't bother going on
  if ((strstr(environment, BEGIN) == NULL && strstr(environment, END) == NULL) || strstr(environment, beginSVG)) {
    return;
  }

  UT_array *array_stack;
  UT_array *row_spacing_stack;
  UT_array *rowlines_stack;
  UT_array *eqn_number_stack;

  char *tok = NULL, *at_top = NULL,
        *temp = "", **prev_stack_item,
         *a, *em_str;

  const char *hline = "\\hline", *hdashline = "\\hdashline",
              *line_separator = "\\\\",
               *cr_separator = "\\cr",
                *newline_separator = "\\newline",
                 *em_pattern_begin = "\\[", *em_pattern_end = "]",
                 *notag = "\\notag", *nonumber = "\\nonumber";

  int rowlines_stack_len = 0, em_offset = 0, eqn = 0, i = 0;

  char *dupe_environment = strdup(environment);
  char *line = strtok(dupe_environment, "\n");

  // set up the array stack
  utarray_new(array_stack, &ut_str_icd);
  utarray_new(row_spacing_stack, &ut_str_icd);
  utarray_new(rowlines_stack, &ut_str_icd);
  utarray_new(eqn_number_stack, &ut_int_icd);

  while (line != NULL) {
    utarray_push_back(array_stack, &line);

    if (strstr(line, END) != NULL) {
      envType environment_type = determine_environment(line);

      while (utarray_len(array_stack) > 0) {
        prev_stack_item = (char **)utarray_back(array_stack);

        rowlines_stack_len = utarray_len(rowlines_stack);
        at_top = strstr(*prev_stack_item, BEGIN);

        // we've reached the top, but there looks like there might be some data
        if (at_top != NULL && strstr(*prev_stack_item, line_separator) == NULL && \
            strstr(*prev_stack_item, cr_separator) == NULL && \
            strstr(*prev_stack_item, newline_separator) == NULL) {
          if (strstr(*prev_stack_item, hline) != NULL || strstr(*prev_stack_item, hdashline) != NULL) {
            *encase = TOPENCLOSE;
          }
          break;
        }

        // eqalign/eqalignno is a bit...special. it's a deprecated environment,
        // but it still uses the same line separators, so it tends
        // to mess with "proper" labelled environments. if we find
        // one, erase all the data.
        if (strstr(*prev_stack_item, "\\eqalign") != NULL) {
          for (i = rowlines_stack_len; i > 1; i--) {
            utarray_pop_back(rowlines_stack);
            utarray_pop_back(eqn_number_stack);
          }
        }

        // looking for a hline/hdashline match
        if (strstr(*prev_stack_item, hline) != NULL) {
          if (rowlines_stack_len > 0) {
            utarray_pop_back(rowlines_stack);
          }
          a = "solid";
          utarray_push_back(rowlines_stack, &a);
        } else if (strstr(*prev_stack_item, hdashline) != NULL) {
          if (rowlines_stack_len > 0) {
            utarray_pop_back(rowlines_stack);
          }
          a = "dashed";
          utarray_push_back(rowlines_stack, &a);
        } else {
          a = "none";
          utarray_push_back(rowlines_stack, &a);
        }

        // some environments have labelling for every row.
        // supress it if it has a \notag or \nonumber
        if (environment_type == ENV_EQUATION || \
            environment_type == ENV_ALIGN || \
            environment_type == ENV_ALIGNAT ||
            environment_type == ENV_EQNARRAY) {
          eqn = !(strstr(*prev_stack_item, notag) != NULL || \
                   strstr(*prev_stack_item, nonumber) != NULL);
        }
        else {
          eqn = 0;
        }

        utarray_push_back(eqn_number_stack, &eqn);

        // if there's a line break...
        if (strstr(*prev_stack_item, line_separator) != NULL || \
            strstr(*prev_stack_item, cr_separator) != NULL || \
            strstr(*prev_stack_item, newline_separator) != NULL) {
          // ...with an emphasis match, add it...
          if ( (tok = strstr(*prev_stack_item, em_pattern_begin)) != NULL) {
            temp = tok + 2; // skip the first part ("\[")
            if ( (tok = strstr(temp, em_pattern_end)) != NULL) {
              em_offset = (int)(tok - temp);
              char *s = strndup(temp, em_offset);
              utarray_push_back(row_spacing_stack, &s);
              free(s);
            }
          }
          // ...otherwise, use the default emphasis
          else {
            if (environment_type == ENV_SMALLMATRIX) {
              em_str = "0.2em";
            } else if (environment_type == ENV_GATHERED) {
              em_str = "1.0ex";
            } else if (environment_type == ENV_EQNARRAY || environment_type == ENV_ALIGNAT || environment_type == ENV_ALIGNED) {
              em_str = "3pt";
            } else if (environment_type == ENV_MULTLINE) {
              em_str = "0.5em";
            } else {
              em_str = "0.5ex";
            }
            utarray_push_back(row_spacing_stack, &em_str);
          }
        }

        // make sure to pop at the end here; it messes with some references in Travis/Ubuntu for some reason
        utarray_pop_back(array_stack);

        // we've reached the top, so stop.
        if (at_top != NULL) {
          break;
        }
      }

      if ((rowlines_stack_len != 0 || utarray_len(row_spacing_stack))) {
        perform_replacement(environment_data_stack, rowlines_stack, environment_type, eqn_number_stack, row_spacing_stack);
      }

      utarray_clear(row_spacing_stack);
      utarray_clear(rowlines_stack);
      rowlines_stack_len = 0;
    }

    line = strtok(NULL, "\n");
  }

  utarray_free(array_stack);
  utarray_free(row_spacing_stack);
  utarray_free(rowlines_stack);
  free(dupe_environment);
}

void perform_replacement(UT_array **environment_data_stack, UT_array *rowlines_stack, envType environment_type, UT_array *eqn_number_stack, UT_array *row_spacing_stack)
{
  char *a, *attr_rowlines, *attr_rowspacing;
  envdata_t env_data;

  // we cut the last char because we can always skip the first row
  utarray_pop_back(rowlines_stack);

  if (utarray_len(eqn_number_stack) != 0) {
    utarray_erase(eqn_number_stack, 0, 1);
  }

  int line_count = utarray_len(rowlines_stack);

  // empty rowlines should be reset
  if (line_count == 0) {
    a = "none";
    utarray_push_back(rowlines_stack, &a);
  }

  // given the row_attribute values, construct an attribute list (separated by spaces)
  UT_string *l;
  utstring_new(l);
  char **o=NULL;
  a = "rowlines=\"";
  utstring_printf(l, "%s", a);
  while ( (o=(char**)utarray_prev(rowlines_stack,o))) {
    utstring_printf(l, "%s ", *o);
  }

  attr_rowlines = utstring_body(l);
  if (strlen(attr_rowlines) > 0) {
    remove_last_char(attr_rowlines); // remove the final space
  }

  // given the row_spacing values, construct an attribute list (separated by spaces)
  UT_string *s;
  utstring_new(s);
  char **p=NULL;
  while ( (p=(char**)utarray_prev(row_spacing_stack,p))) {
    if (environment_type == ENV_SMALLMATRIX && strcmp(*p, "0.5ex") == 0) {
      utstring_printf(s, "%s ", "0.2em");
    } else if (environment_type == ENV_GATHERED && strcmp(*p, "0.5ex") == 0) {
      utstring_printf(s, "%s ", "1.0ex");
    } else {
      utstring_printf(s, "%s ", *p);
    }
  }

  attr_rowspacing = utstring_body(s);
  if (strlen(attr_rowspacing) > 0) {
    remove_last_char(attr_rowspacing); // remove the final space
  } else {
    if (environment_type == ENV_SMALLMATRIX) {
      attr_rowspacing = "0.2em";
    } else if (environment_type == ENV_GATHERED) {
      attr_rowspacing = "1.0ex";
    } else {
      attr_rowspacing = "0.5ex";
    }
  }

  // store pertinent metadata
  env_data.rowspacing = attr_rowspacing;
  env_data.rowlines = attr_rowlines;
  env_data.environment_type = environment_type;
  env_data.eqn_numbers = eqn_number_stack;
  env_data.line_count = line_count;

  utarray_push_back(*environment_data_stack, &env_data);
  utstring_free(l);
  utstring_free(s);
}

const char *vertical_pipe_extract(const char *string)
{
  char *dupe = strdup(string);
  UT_string *columnlines, *border;
  char *previous_column = "", *attr_columnlines, *attr_border;
  int i = 0;

  utstring_new(columnlines);
  utstring_new(border);

  // the first character (if it exists) determines the frame border
  if (strncmp(dupe, "s", 1) == 0) {
    utstring_printf(columnlines, "%s", "frame=\"solid\" columnlines=\"");
    remove_first_char(dupe);
  } else if (strncmp(dupe, "d", 1) == 0) {
    utstring_printf(columnlines, "%s", "frame=\"dashed\" columnlines=\"");
    remove_first_char(dupe);
  } else {
    utstring_printf(columnlines, "%s", "columnlines=\"");
  }

  char *token = strtok(dupe, " ");

  while (token != NULL) {
    if (strncmp(token, "s", 1) == 0) {
      previous_column = "s";
      utstring_printf(border, "%s ", "solid");
    } else if (strncmp(token, "d", 1) == 0) {
      previous_column = "d";
      utstring_printf(border, "%s ", "dashed");
    } else {
      if (i >= 1) { // we must skip the first blank col
        // only if there is no previous border should a border be considered, eg. "cc", not "c|c"
        if (strncmp(previous_column, "s", 1) != 0 && strncmp(previous_column, "d", 1) != 0) {
          utstring_printf(border, "%s ", "none");
        }
        previous_column = "0";
      }
    }

    i++;
    token = strtok(NULL, " ");
  }

  attr_border = utstring_body(border);
  if (strlen(attr_border) > 0) {
    remove_last_char(attr_border); // remove the final space
  }
  utstring_printf(columnlines, "%s", attr_border);

  // an empty string here angers Lasem, so let's remember to add 'none'
  if (utstring_len(border) == 0) {
    utstring_printf(columnlines, "%s", "none");
  }

  attr_columnlines = strdup(utstring_body(columnlines));
  free(dupe);
  utstring_free(border);
  utstring_free(columnlines);

  return attr_columnlines;
}

const char *remove_excess_pipe_chars(const char *string)
{
  UT_string *columnalign;
  utstring_new(columnalign);

  char *dupe = strdup(string);
  char *token = strtok(dupe, " ");
  char *attr_columnalign;

  while (token != NULL) {
    if (strncmp(token, "s", 1) != 0 && strncmp(token, "d", 1) != 0) {
      utstring_printf(columnalign, "%s ", token);
    }
    token = strtok(NULL, " ");
  }

  attr_columnalign = strdup(utstring_body(columnalign));
  free(dupe);
  utstring_free(columnalign);

  if (strlen(attr_columnalign) > 0) {
    remove_last_char(attr_columnalign); // remove the final space
  }

  return attr_columnalign;
}

const char *combine_row_data(UT_array **environment_data_stack)
{
  // if no information was provided, give a standard sizing
  if (utarray_len(*environment_data_stack) == 0) {
    const char* s = "rowspacing=\"0.5ex\" rowlines=\"none\"";
    char* c = (char*)malloc(strlen(s) + 1);
    strcpy(c, s);
    return c;
  }
  envdata_t *row_data_elem = (envdata_t*) utarray_front(*environment_data_stack);

  char *row_spacing_data = row_data_elem->rowspacing,
        *row_lines_data = row_data_elem->rowlines,
         *row_attr;

  UT_string *row_attr_data;
  utstring_new(row_attr_data);

  // combine the row spacing and row lines data
  utstring_printf(row_attr_data, "%s%s\" %s\"", "rowspacing=\"", row_spacing_data, row_lines_data);

  row_attr = strdup(utstring_body(row_attr_data));
  utarray_erase(*environment_data_stack, 0, 1);

  utstring_free(row_attr_data);

  return row_attr;
}

int fetch_eqn_number(UT_array **environment_data_stack)
{
  // if no information was provided, expect nothing
  if (utarray_len(*environment_data_stack) == 0) {
    return 0;
  }

  envdata_t *row_data_elem = (envdata_t*) utarray_back(*environment_data_stack);
  UT_array *eqn_numbers = row_data_elem->eqn_numbers;

  if (utarray_len(eqn_numbers) == 0) {
    return 0;
  }

  int *e = (int*) utarray_back(eqn_numbers);
  utarray_pop_back(eqn_numbers);

  return *e;
}

float extract_number_from_pxstring(const char * str)
{
  float dbl;
  int match = 0;

  match = sscanf (str, "%*[^-0123456789]%f", &dbl);
  if (match == 1) {
    return dbl;
  }

  // must not be a float.
  sscanf (str, "%d", &match);
  return (float) match;
}

const char *extract_string_from_pxstring(const char * str)
{
  char *pixel;
  float dbl;
  pixel = malloc(3*sizeof(char));
  sscanf (str, "%f%s", &dbl, pixel);
  return pixel;
}

const char * dbl2em(const char *str)
{
  UT_string *em;
  utstring_new(em);

  float dbl = extract_number_from_pxstring(str);
  dbl *= 0.056;

  utstring_printf(em, "%.3fem", dbl);
  char * em_str = strdup(utstring_body(em));

  utstring_free(em);

  return em_str;
}

const char * double_pixel(float f, char *pixel)
{
  UT_string *em;
  utstring_new(em);

  float dbl = f * 2;
  utstring_printf(em, "%.3f%s", dbl, pixel);
  char * em_str = strdup(utstring_body(em));

  utstring_free(em);

  return em_str;
}

const char * implement_skew(char *base_str, char *em_skew, char *pattern)
{
  UT_string *skew_mathml;
  utstring_new(skew_mathml);

  utstring_printf(skew_mathml, "%s%s%s", "<mrow><mrow><mrow><mover><mrow>", base_str, "<mspace width=\"");
  utstring_printf(skew_mathml, "%s%s%s", em_skew, "\" /></mrow>", "<mo stretchy=\"false\">");
  utstring_printf(skew_mathml, "%s%s%s", pattern, "</mo></mover></mrow><mspace width=\"-", em_skew);
  utstring_printf(skew_mathml, "%s", "\" /></mrow><mrow></mrow></mrow>");

  char * skew_mathml_str = strdup(utstring_body(skew_mathml));

  utstring_free(skew_mathml);

  return skew_mathml_str;
}

const char * root_pos_to_em(const char * str)
{
  UT_string *em;
  utstring_new(em);

  float dbl = extract_number_from_pxstring(str);
  dbl /= 15;

  utstring_printf(em, "%.3fem", dbl);
  char * em_str = strdup(utstring_body(em));

  utstring_free(em);

  return em_str;
}

envType current_env_type(UT_array **environment_data_stack)
{
  if (utarray_len(*environment_data_stack) == 0) {
    return -1;
  }

  envdata_t *row_data_elem = (envdata_t*) utarray_front(*environment_data_stack);

  return row_data_elem->environment_type;
}

int current_env_line_count(UT_array **environment_data_stack)
{
  if (utarray_len(*environment_data_stack) == 0) {
    return -1;
  }

  envdata_t *row_data_elem = (envdata_t*) utarray_front(*environment_data_stack);

  return row_data_elem->line_count;
}
