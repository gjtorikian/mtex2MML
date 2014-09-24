#ifndef PARSE_EXTRAS_H
#define PARSE_EXTRAS_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    char *attr_strings;
    int  offset_pos;
  } hlineData;

  // array of structs
  typedef struct
  {
    hlineData *array;
    size_t used;
    size_t size;
  } hlineDataArray;

  // set up array of hlineData
  extern void initHlineDataArray(hlineDataArray *a, size_t initialSize);

  // insert into hlineData array
  extern void insertHlineDataArray(hlineDataArray *a, hlineData element);

  // sort the array based on offset_pos
  extern void sortHLineDataArray(hlineDataArray *a);

  // destroyes the array
  extern void deleteHlineDataArray(hlineDataArray *a);

  // Move the `hline` and `hlinedash` symbols inline with the `\begin{array}` line
  // This is so that the Bison parser can properly act on these.

  // In order to properly address arrays, we need to parse them, find their hlines, and then
  // modify the starting environment declaration to point out where those hlines are.
  //
  // Suppose there is an array like:
  //
  // \begin{array}{c:c}
  //   \begin{array}{c|cclc}
  //     \text{min} & 0 & 1 & 2 & 3\\\\
  //     \hline
  //     0 & 0 & 0 & 0 & 0\\\\
  //     1 & 0 & 1 & 1 & 1\\\\
  //     2 & 0 & 1 & 2 & 2\\\\
  //     3 & 0 & 1 & 2 & 3
  //   \end{array}
  // &
  //   \begin{array}{c|cccl}
  //     \text{max}&0&1&2&3\\\\
  //     \hline
  //     0 & 0 & 1 & 2 & 3\\\\
  //     1 & 1 & 1 & 2 & 3\\\\
  //     2 & 2 & 2 & 2 & 3\\\\
  //     3 & 3 & 3 & 3 & 3
  //   \end{array}
  // \end{array}
  //
  // The hline_replace function will push every line onto a stack. When an \end
  // is detected, it starts popping off the stack until it reaches the corresponding
  // \begin. It then modifies that line with attr_strings, an arrangement of the
  // the \hlines encountered while popping lines off.

  extern char * hline_replace (const char *string);

  // determines the column border arrangement from the array environment definition
  extern const char *vertical_pipe_extract(const char *string);

  // removes placeholder pipe characters from columnalign
  extern const char *remove_excess_pipe_chars(const char *string);
#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_EXTRAS_H */
