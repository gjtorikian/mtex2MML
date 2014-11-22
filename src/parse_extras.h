#ifndef PARSE_EXTRAS_H
#define PARSE_EXTRAS_H

#include "deps/uthash/uthash.h"
#include "deps/uthash/utarray.h"
#include "deps/str-replace/str-replace.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char *rowspacing;
  char *rowlines;
  int empty;
} envdata_t;

typedef struct {
  char *attribute;
  int  offset_pos;
} symbolData;

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
// \begin. It then modifies that stack with attribute strings, an arrangement of the
// the symbols encountered while popping lines off.
extern void env_replacements(UT_array **environment_data_stack, const char *environment);

extern void perform_replacement(UT_array **environment_data_stack, UT_array *rowlines_stack, char *attr_rowspacing, const char *is_smallmatrix, const char *is_gathered, UT_array *row_spacing_stack);

// determines the column border arrangement from the array environment definition (c|cc|c...)
extern const char *vertical_pipe_extract(const char *string);

// removes placeholder pipe characters from columnalign
extern const char *remove_excess_pipe_chars(const char *string);

// return the proper rowlines information
extern const char *combine_row_data(UT_array **environment_data_stack);

#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_EXTRAS_H */
