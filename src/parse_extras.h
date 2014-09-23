/* Added methods for string maniuplation */
#ifndef PARSE_EXTRAS_H
#define PARSE_EXTRAS_H

#define ITEX2MML_VERSION "1.5.2"

#ifdef __cplusplus
extern "C" {
#endif
  // Replace a substring (`old`) with some text (`new`) in the string `str`.
  extern char *replace_str(const char *str, const char *old, const char *new);

  // Fetches a substring within `inpStr`, starting at `startPos` and as long as `strLen`
  extern char *substring(char *inpStr, int startPos, int strLen);

  // Join two strings together
  // fuck strncpy
  extern char *join(char* s1, char* s2);

  // Remove the final character in a string
  extern void remove_last_char(char* str);

  // Insert a substring (`new_str`) into a string (`str`) at `position`
  extern void insert_substring(char *str, char *new_str, int position);

  // Move the `hline` and `hlinedash` symbols inline with the `\begin{array}` line
  // This is so that the Bison parser can properly act on these
  extern char * hline_replace (const char *string);

  extern const char *vertical_pipe_replace(const char *string);
#ifdef __cplusplus
}
#endif

#endif /* ! PARSE_EXTRAS_H */
