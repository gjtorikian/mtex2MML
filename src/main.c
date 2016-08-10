#include <string.h>
#include <stdio.h>
#include "mtex2MML.h"
#include "../deps/uthash/utstring.h"

int main (int argc, char ** argv)
{
  int bPrintMtex = 0;
  int bInline    = 0;
  int bDisplay   = 0;
  int bDelimiters   = 0;

  int bStop = 0;
  int bForbidMarkup = 0;
  int arg = 1;

  for (; arg < argc; arg++) {
    char* args = argv[arg];

    if (strcmp(args, "--version") == 0 || strcmp(args, "-v") == 0) {
      fputs("mtex2MML version " MTEX2MML_VERSION "\n", stdout);
      bStop = 1;
      break;
    }

    if (strcmp(args, "--help") == 0 || strcmp(args, "-h") == 0) {
      fputs ("usage: mtex2MML [OPTIONS]\n"
             "\n"
             "mtex2MML filters an input text stream (e.g., an XHTML web page) converting TeX expressions\n"
             "to MathML. Inline TeX expressions are delimited either side by single dollar symbols ($):\n"
             "\n"
             "\t<p>The parameters $\\alpha$ and $\\beta$ in the function $f(x)$ are defined below.</p>\n"
             "\n"
             "Display TeX expressions can be delimited with double dollar\n"
             "symbols ($$) on either side or by \\[ to the left and \\] to the right:\n"
             "\n"
             "\t<p class=\"equation\">\\[\n"
             "\t\tf(x) = \\alpha x + \\frac{\\beta}{1+|x|}\n"
             "\t\\]</p>\n"
             "\n"
             "mtex2MML Options:\n"
             "\n"
             "  --inline                  converts a single TeX equation, without any $ symbols, to inline MathML\n"
             "  --display                 converts a single TeX equation, without any $$ symbols, to display-mode MathML\n"
             "  --forbid-markup           forbid markup (more precisely, the '<' and '>' characters) in TeX equations\n"
             "  --print-mtex              prints the TeX-formatted string\n"
             "  --use-dollar              uses `$..$` for inline math\n"
             "  --use-double              uses `$$..$$` for display math\n"
             "  --use-parens              uses `\\(..\\)` for inline math\n"
             "  --use-brackets            uses `\\[..\\]` for display math\n"
             "\n"
             "For more information, see https://github.com/gjtorikian/mtex2MML\n", stdout);

      bStop = 1;
      break;
    }
    if (strcmp(args, "--print-mtex") == 0) {
      bPrintMtex = 1;
      continue;
    }
    if (strcmp(args, "--forbid-markup") == 0) {
      bForbidMarkup = 1;
      continue;
    }
    if (strcmp(args, "--inline") == 0) {
      bInline    = 1;
      bDisplay   = 0;
      continue;
    }
    if (strcmp(args, "--display") == 0) {
      bInline    = 0;
      bDisplay   = 1;
      continue;
    }
    if (strcmp(args, "--use-dollar") == 0) {
      bDelimiters |= MTEX2MML_DELIMITER_DOLLAR;
      continue;
    }
    if (strcmp(args, "--use-double") == 0) {
      bDelimiters |= MTEX2MML_DELIMITER_DOUBLE;
      continue;
    }
    if (strcmp(args, "--use-parens") == 0) {
      bDelimiters |= MTEX2MML_DELIMITER_PARENS;
      continue;
    }
    if (strcmp(args, "--use-brackets") == 0) {
      bDelimiters |= MTEX2MML_DELIMITER_BRACKETS;
      continue;
    }
  }
  if (bStop) { return 0; }

  UT_string *mtex;

  utstring_new(mtex);

  if (bInline) { utstring_printf(mtex, "$" ); }
  if (bDisplay) { utstring_printf(mtex, "$$" ); }

#define BUFSIZE 1024
  char buffer[BUFSIZE];
  int buffer_len;

  fgets (buffer, BUFSIZE, stdin);
  buffer_len = strlen(buffer);

  if (bPrintMtex == 1 && buffer[buffer_len - 1] == '\n') {
    buffer[buffer_len - 1] = '\0';
  }

  if (buffer_len > 1) {
    if (buffer[0] == '$' && buffer[1] == '$') {
      bDelimiters |= MTEX2MML_DELIMITER_DOUBLE;
    } else if (buffer[0] == '\\' && buffer[1] == '(') {
      bDelimiters |= MTEX2MML_DELIMITER_PARENS;
    } else if (buffer[0] == '\\' && buffer[1] == '[') {
      bDelimiters |= MTEX2MML_DELIMITER_BRACKETS;
    }
  } else if (buffer_len > 0 && buffer[0] == '$') {
    bDelimiters |= MTEX2MML_DELIMITER_DOLLAR;
  }

  utstring_printf(mtex, "%s", buffer);

  if (bInline) { utstring_printf(mtex, "$" ); }
  if (bDisplay) {utstring_printf(mtex, "$$" ); }

  if (bPrintMtex) {
    char *s = utstring_body(mtex);
    fputs (s, stdout);

    utstring_free(mtex);
    fflush (stdout);

    return 0;
  } else if (!bInline && !bDisplay) {
    char *s = utstring_body(mtex);
    int len = utstring_len(mtex);
    static char *result;

    if (bForbidMarkup) {
      mtex2MML_strict_filter (s, len, bDelimiters);
    } else {
      mtex2MML_text_filter (s, len, bDelimiters);
    }

    result = mtex2MML_output();

    if (strlen(result) == 0) {
      fputs ("mtex2MML: mtex parser failed to generate MathML from mtex!\n", stderr);
      return -1;
    }

    fputs (result, stdout);

    utstring_free(mtex);
    free(result);
    fflush (stdout);

    return 0;
  } else {
    char *s = utstring_body(mtex);
    int len = utstring_len(mtex);
    char * mathml = mtex2MML_parse(s, len, bDelimiters);

    if (mathml) {
      fputs (mathml, stdout);

      mtex2MML_free_string (mathml);
      mathml = 0;
      return 0;
    } else {
      fputs ("mtex2MML: mtex parser failed to generate MathML from mtex!\n", stderr);
      return -1;
    }
  }
}
