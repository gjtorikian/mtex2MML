%module mtex2MML 
%{
#include "mtex2MML.h"
extern const char * mtex2MML_output ();
%}
extern int    mtex2MML_filter (const char * buffer, unsigned long length);
extern int    mtex2MML_html_filter (const char * buffer, unsigned long length);
extern const char * mtex2MML_output ();
