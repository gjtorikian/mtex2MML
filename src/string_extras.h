/* Added methods for string manipulation */

#ifndef STRING_EXTRAS_H
#define STRING_EXTRAS_H

#include "deps/uthash/utstring.h"

// all for str_replace
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Remove the final character in a string
extern void remove_last_char(char* str);

// Remove the first character in a string
extern void remove_first_char(char* str);

// Duplicates an immutable string
extern char * dupe_string(const char * str);

// Duplicates an immutable string (up to n bytes)
extern char * dupe_string_n(const char * s, size_t n);

extern char * str_replace(char *string, const char *substr, const char *replacement);

#ifdef __cplusplus
}
#endif

#endif /* ! STRING_EXTRAS_H */
