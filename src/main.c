#include <string.h>
#include <stdio.h>
#include "mtex2MML.h"
#include "../deps/uthash/utstring.h"

int main (int argc, char ** argv)
{
  int bPrintMtex = 0;
  int bRawFilter = 0;
  int bInline    = 0;
  int bDisplay   = 0;

  int bStop = 0;
  int bForbidMarkup = 0;

  for (int arg = 1; arg < argc; arg++) {
    char* args = argv[arg];

    if (strcmp(args, "--version") == 0 || strcmp(args, "-v") == 0) {
      fputs("mtex2MML version " MTEX2MML_VERSION "\n", stdout);
      bStop = 1;
      break;
    }

    if (strcmp(args, "--help") == 0 || strcmp(args, "-h") == 0) {
      fputs ("usage: mtex2MML [OPTIONS]\n"
             "\n"
             "mtex2MML filters an input text stream (e.g., an XHTML web page) converting mtex expressions\n"
             "to MathML. Inline mtex expressions are delimited either side by single dollar symbols ($):\n"
             "\n"
             "\t<p>The parameters $\\alpha$ and $\\beta$ in the function $f(x)$ are defined below.</p>\n"
             "\n"
             "For normal display of equations, etc., mtex expressions can be delimited with double dollar\n"
             "symbols ($$) either side or by \\[ to the left and \\] to the right:\n"
             "\n"
             "\t<p class=\"equation\">\\[\n"
             "\t\tf(x) = \\alpha x + \\frac{\\beta}{1+|x|}\n"
             "\t\\]</p>\n"
             "\n"
             "mtex2MML Options:\n"
             "\n"
             "  --raw-filter    filter input stream, converting equations as found to MathML [stops on error]\n"
             "  --inline        converts a single mtex equation, without any $ symbols, to inline MathML\n"
             "  --display       converts a single mtex equation, without any $ symbols, to display-mode MathML\n"
             "  --forbid-markup forbid markup (more precisely, the '<' and '>' characters) in mtex equations\n"
             "  --print-mtex    used in conjuction with --inline or --display: prints the mtex string\n"
             "\n"
             "For further information, see https://github.com/gjtorikian/mtex2MML\n", stdout);

      bStop = 1;
      break;
    }
    if (strcmp(args, "--print-mtex") == 0) {
      bPrintMtex = 1;
      bRawFilter = 0;
      continue;
    }
    if (strcmp(args, "--forbid-markup") == 0) {
      bRawFilter = 0;
      bForbidMarkup = 1;
      continue;
    }
    if (strcmp(args, "--inline") == 0) {
      bRawFilter = 0;
      bInline    = 1;
      bDisplay   = 0;
      continue;
    }
    if (strcmp(args, "--display") == 0) {
      bRawFilter = 0;
      bInline    = 0;
      bDisplay   = 1;
      continue;
    }
    if (strcmp(args, "--raw-filter") == 0) {
      bRawFilter = 1;
      bPrintMtex = 0;
      bInline    = 0;
      bDisplay   = 0;
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
  while (fgets (buffer, BUFSIZE, stdin)) { utstring_printf(mtex, "%s", buffer); }

  if (bInline) { utstring_printf(mtex, "$" ); }
  if (bDisplay) {utstring_printf(mtex, "$$" ); }

  if (bPrintMtex) {
    char *s = utstring_body(mtex);
    fputs (s, stdout);
    fputs ("\n", stdout);
    utstring_free(mtex);
    fflush (stdout);
  }

  if (!bInline && !bDisplay) {
    char *s = utstring_body(mtex);
    int len = utstring_len(mtex);
    if (bRawFilter) {
      mtex2MML_filter (s, len);
    } else if (bForbidMarkup) {
      mtex2MML_strict_html_filter (s, len);
    } else {
      mtex2MML_html_filter (s, len);
    }
    utstring_free(mtex);
    return 0;
  }

  char *s = utstring_body(mtex);
  int len = utstring_len(mtex);
  char * mathml = mtex2MML_parse (s, len);

  if (mathml) {
    fputs (mathml, stdout);
    fputs ("\n", stdout);

    mtex2MML_free_string (mathml);
    mathml = 0;
  } else {
    fputs ("mtex2MML: mtex parser failed to generate MathML from mtex!\n", stderr);
  }
  utstring_free(mtex);
  return 0;
}
