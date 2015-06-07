#ifndef EM_H
#define EM_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* ! EM_H */
