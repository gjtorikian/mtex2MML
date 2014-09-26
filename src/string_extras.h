/* Added methods for string manipulation */

#ifndef STRING_EXTRAS_H
#define STRING_EXTRAS_H

#ifdef __cplusplus
extern "C" {
#endif

  // Replace a substring (`old`) with some text (`new`) in the string `str`.
  extern char *replace_str(const char *str, const char *old, const char *new);

  // Join two strings together
  // fuck strncpy
  extern char *join(char* s1, char* s2);

  // Remove the final character in a string
  extern void remove_last_char(char* str);

  // Remove the first character in a string
  extern void remove_first_char(char* str);

  // Insert a substring (`ins`) into a string (`dest`) at `location`
  extern void insert_substring(char **dest, char *ins, size_t location);

  // Reverse the substring
  extern void strrev(char *str);

#ifdef __cplusplus
}
#endif

#endif /* ! STRING_EXTRAS_H */
