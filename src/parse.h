#ifndef PARSE_H
#define PARSE_H

#include "../deps/uthash/uthash.h"
#include "../deps/uthash/utarray.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {NONE = 0, TOPENCLOSE} encaseType;
typedef enum {OTHER = 0, ENV_ALIGN, ENV_ALIGNAT, ENV_ALIGNED, ENV_EQUATION, ENV_GATHER, ENV_GATHERED, ENV_EQNARRAY, ENV_MULTLINE, ENV_MULTLINESTAR, ENV_SMALLMATRIX} envType;

typedef struct {
  char *rowspacing;
  char *rowlines;
  envType environment_type;
  UT_array *eqn_numbers;
  int line_count;
} envdata_t;

/* Move various symbols not easily supported inline within the `\begin` line
This is so that the Bison parser can properly act on these. For example,
`\hline`, `\hlinedash`, or `\\[2ex]` declerations.

In order to properly address these situations, we need to parse them, find their symbols,
and then modify the starting environment declaration to point out where those symbols are.

Suppose there is an array like:

\begin{array}{c:c}
  \begin{array}{c|cclc}
    \text{min} & 0 & 1 & 2 & 3\\
    \hline
    0 & 0 & 0 & 0 & 0\\
    1 & 0 & 1 & 1 & 1\\
    2 & 0 & 1 & 2 & 2\\
    3 & 0 & 1 & 2 & 3
  \end{array}
&
  \begin{array}{c|cccl}
    \text{max}&0&1&2&3\\
    \hline
    0 & 0 & 1 & 2 & 3\\
    1 & 1 & 1 & 2 & 3\\
    2 & 2 & 2 & 2 & 3\\
    3 & 3 & 3 & 3 & 3
  \end{array}
\end{array}

The env_replacements function will push every line onto a stack. When an \end
is detected, it starts popping off the stack until it reaches the corresponding
\begin. It then modifies that stack with attribute strings, an arrangement of
the symbols encountered while popping lines off. */
extern void mtex2MML_env_replacements(UT_array **environment_data_stack, encaseType **encase, const char *environment);

extern int mtex2MML_determine_environment(const char *environment);

extern int mtex2MML_identify_eqn_number(envType environment_type, char *line);

extern void mtex2MML_perform_replacement(UT_array **environment_data_stack, UT_array *rowlines_stack, envType environment_type, UT_array *has_eqn_number, UT_array *row_spacing_stack);

// determines the column border arrangement from the array environment definition (c|cc|c...)
extern char *mtex2MML_vertical_pipe_extract(char *string);

// removes placeholder pipe characters from columnalign (for example, c|c:c becomes "center s center d center")--
// we need to remove the "s" and "d" characters
extern char *mtex2MML_remove_excess_pipe_chars(char *string);

// return the proper rowlines information
extern char *mtex2MML_combine_row_data(UT_array **environment_data_stack);

// return the has_eqn_number value of the last row
extern int mtex2MML_fetch_eqn_number(UT_array **environment_data_stack);

// given a pixel string, retrieve the numeric portion from it
extern float mtex2MML_extract_number_from_pxstring(char * str);

// given a pixel string, retrieve the pixel type portion from it
extern char *mtex2MML_extract_string_from_pxstring(char * str);

// given a number, return it as an em
extern char *mtex2MML_dbl2em(char *str);

// given a number, return it as a root position
// taken straight from MathJax
extern char *mtex2MML_root_pos_to_em(char * str);

// given a number and a pixel string, return the doubled number
extern char *mtex2MML_double_pixel(float f, char *pixel);

// construct a skew sequence
extern char *mtex2MML_implement_skew(char *base_str, char *em_skew, char *pattern);

// get the environment type of the top-most item
extern envType mtex2MML_current_env_type(UT_array **environment_data_stack);

// get the line count of the top-most item
extern int mtex2MML_current_env_line_count(UT_array **environment_data_stack);

#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_H */
