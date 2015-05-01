#ifndef MTEX2MML_H
#define MTEX2MML_H

#define MTEX2MML_VERSION "1.0.0"

#ifdef __cplusplus
extern "C" {
#endif

// #define mtex2MML_CAPTURE 1

/* Step 1. Parse a buffer with mtex source; return value is mathml, or 0 on failure (e.g., parse error).
 */
extern char * mtex2MML_parse (const char * buffer, unsigned long length);

/* Step 2. Free the string from Step 1.
 */
extern void   mtex2MML_free_string (char * str);


/* Alternatively, to filter generic source and converting embedded equations, use:
 */
extern int    mtex2MML_filter (const char * buffer, unsigned long length);

extern int    mtex2MML_html_filter (const char * buffer, unsigned long length);
extern int    mtex2MML_strict_html_filter (const char * buffer, unsigned long length);


/* To change output methods:
 *
 * Note: If length is 0, then buffer is treated like a string; otherwise only length bytes are written.
 */
extern void (*mtex2MML_write) (const char * buffer, unsigned long length); /* default writes to stdout */
extern void (*mtex2MML_write_mathml) (const char * mathml);                /* default calls mtex2MML_write(mathml,0) */
extern void (*mtex2MML_error) (const char * msg);                          /* default writes to stderr */


/* Other stuff:
 */

extern char * mtex2MML_global_parse (const char * buffer, unsigned long length, int global_start);

extern void   mtex2MML_setup (const char * buffer, unsigned long length);

extern void   mtex2MML_restart ();

extern int mtex2MML_do_capture_eqn();
extern int mtex2MML_capture_eqn_src();

extern char * mtex2MML_copy_string (const char * str);
extern char * mtex2MML_copy_string_extra (const char * str, unsigned extra);
extern char * mtex2MML_copy2 (const char * first, const char * second);
extern char * mtex2MML_copy3 (const char * first, const char * second, const char * third);
extern char * mtex2MML_copy_escaped (const char * str);

extern char * mtex2MML_empty_string;

extern int    mtex2MML_lineno;

extern int    mtex2MML_rowposn;
extern int    mtex2MML_displaymode;
extern int    display_style;

extern int    global_label;
extern int    line_counter;

#ifdef __cplusplus
}
#endif

#endif /* ! MTEX2MML_H */
