#ifndef PARSE_EXTRAS_H
#define PARSE_EXTRAS_H

#include "deps/uthash/uthash.h"
#include "deps/uthash/utarray.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {NONE = 0, TOPENCLOSE} encaseType;
typedef enum {OTHER = 0, ENV_ALIGNAT, ENV_GATHERED, ENV_EQNARRAY, ENV_MULTLINE, ENV_SMALLMATRIX} envType;

typedef struct {
  char *rowspacing;
  char *rowlines;
  envType environmentType;
  int line_count;
} envdata_t;

struct css_colors {
  char name[22];             /* key */
  char color[10];
  UT_hash_handle hh;         /* makes this structure hashable */
};

// Move various symbols not easily supported inline within the `\begin` line
// This is so that the Bison parser can properly act on these. For example,
// `\hline`, `\hlinedash`, or `\\[2ex]` declerations.
//
// In order to properly address these situations, we need to parse them, find their symbols,
// and then modify the starting environment declaration to point out where those symbols are.
//
// Suppose there is an array like:
//
// \begin{array}{c:c}
//   \begin{array}{c|cclc}
//     \text{min} & 0 & 1 & 2 & 3\\
//     \hline
//     0 & 0 & 0 & 0 & 0\\
//     1 & 0 & 1 & 1 & 1\\
//     2 & 0 & 1 & 2 & 2\\
//     3 & 0 & 1 & 2 & 3
//   \end{array}
// &
//   \begin{array}{c|cccl}
//     \text{max}&0&1&2&3\\
//     \hline
//     0 & 0 & 1 & 2 & 3\\
//     1 & 1 & 1 & 2 & 3\\
//     2 & 2 & 2 & 2 & 3\\
//     3 & 3 & 3 & 3 & 3
//   \end{array}
// \end{array}
//
// The env_replacements function will push every line onto a stack. When an \end
// is detected, it starts popping off the stack until it reaches the corresponding
// \begin. It then modifies that stack with attribute strings, an arrangement of
// the symbols encountered while popping lines off.
extern void env_replacements(UT_array **environment_data_stack, encaseType *encase, const char *environment);

extern void perform_replacement(UT_array **environment_data_stack, UT_array *rowlines_stack, envType environmentType, UT_array *row_spacing_stack);

// determines the column border arrangement from the array environment definition (c|cc|c...)
extern const char *vertical_pipe_extract(const char *string);

// removes placeholder pipe characters from columnalign (for example, c|c:c becomes "center s center d center")--
// we need to remove the "s" and "d" characters
extern const char *remove_excess_pipe_chars(const char *string);

// return the proper rowlines information
extern const char *combine_row_data(UT_array **environment_data_stack);

// given a pixel string, retrieve the numeric portion from it
extern const float extract_number_from_pxstring(const char * str);

// given a pixel string, retrieve the pixel type portion from it
extern const char *extract_string_from_pxstring(const char * str);

// given a number, return it as an em
extern const char * dbl2em(const char *str);

// given a number, return it as a root position
// taken straight from MathJax
extern const char * root_pos_to_em(const char * str);

// given a number and a pixel string, return the doubled number
extern const char * double_pixel(float f, char *pixel);

// construct a skew sequence
extern const char * implement_skew(char *base_str, char *em_skew, char *pattern);

// get the environment type of the top-most item
extern envType current_env_type(UT_array **environment_data_stack);

// get the line count of the top-most item
extern int current_env_line_count(UT_array **environment_data_stack);

#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_EXTRAS_H */
