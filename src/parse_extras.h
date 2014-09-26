#ifndef PARSE_EXTRAS_H
#define PARSE_EXTRAS_H

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    char *attribute;
    int  offset_pos;
  } symbolData;

  // array of structs
  typedef struct
  {
    symbolData *array;
    size_t used;
    size_t size;
  } symbolDataArray;

  // set up array of symbols (like hlines)
  extern void initSymbolDataArray(symbolDataArray *a, size_t initialSize);

  // insert into symbol array
  extern void insertSymbolDataArray(symbolDataArray *a, symbolData element);

  // sort the array based on offset_pos
  extern void sortSymbolDataArray(symbolDataArray *a);

  // destroyes the array
  extern void deleteSymbolDataArray(symbolDataArray *a);

  // Move various symbols not easily supported inline with the `\begin` line
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
  // The env_replacements function will push every line onto a stack. When an \end
  // is detected, it starts popping off the stack until it reaches the corresponding
  // \begin. It then modifies that line with attribute strings, an arrangement of the
  // the symbols encountered while popping lines off.
  extern char * env_replacements(const char *string);

  // determines the column border arrangement from the array environment definition
  extern const char *vertical_pipe_extract(const char *string);

  // removes placeholder pipe characters from columnalign
  extern const char *remove_excess_pipe_chars(const char *string);
#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_EXTRAS_H */
