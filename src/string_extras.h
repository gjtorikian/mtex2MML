/* Added methods for string manipulation */

#ifndef STRING_EXTRAS_H
#define STRING_EXTRAS_H

#include "deps/str-replace/str-replace.h"

#ifdef __cplusplus
extern "C" {
#endif

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

// Find out if a string is just full of empty RowSpacings (0em)
extern int empty_row_spacings(char *str);

// Duplicates an immutable string
extern char * dupe_string(const char * s);

// Duplicates an immutable string (up to n bytes)
extern char * dupe_string_n(const char * s, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* ! STRING_EXTRAS_H */
