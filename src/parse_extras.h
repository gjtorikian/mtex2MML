/* Added methods for string manipulation */

#ifndef PARSE_EXTRAS_H
#define PARSE_EXTRAS_H

#define ITEX2MML_VERSION "1.5.2"

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

  // Replace a substring (`old`) with some text (`new`) in the string `str`.
  extern char *replace_str(const char *str, const char *old, const char *new);

  // Fetches a substring within `inpStr`, starting at `startPos` and as long as `strLen`
  extern char *substring(char *inpStr, int startPos, int strLen);

  // Join two strings together
  // fuck strncpy
  extern char *join(char* s1, char* s2);

  // Remove the final character in a string
  extern void remove_last_char(char* str);

  // Insert a substring (`ins`) into a string (`dest`) at `location`
  extern void insert_substring(char **dest, char *ins, size_t location);

  // Reverse the substring
  extern void strrev(char *str);

  // set up array of hlineData
  extern void initHlineDataArray(hlineDataArray *a, size_t initialSize);

  // insert into hlineData array
  extern void insertHlineDataArray(hlineDataArray *a, hlineData element);

  // sort the array based on offset_pos
  extern void sortHLineDataArray(hlineDataArray *a);

  // destroyes the array
  extern void deleteHlineDataArray(hlineDataArray *a);

  // Move the `hline` and `hlinedash` symbols inline with the `\begin{array}` line
  // This is so that the Bison parser can properly act on these
  extern char * hline_replace (const char *string);

  // determines the column border arrangement
  extern const char *vertical_pipe_extract(const char *string);

  // removes placeholder pipe characters from columnalign
  extern const char *remove_excess_pipe_chars(const char *string);
#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_EXTRAS_H */
