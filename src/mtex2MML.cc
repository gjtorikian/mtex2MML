#include <cstdio>

#include <string>

#include "mtex2MML.h"

int main (int argc, char ** argv)
{
  bool bPrintMtex = false;
  bool bRawFilter = false;
  bool bInline    = false;
  bool bDisplay   = false;

  bool bStop = false;
  bool bForbidMarkup = false;

  for (int arg = 1; arg < argc; arg++) {
    std::string args = argv[arg];

    if (args == "--version" || args == "-v") {
      fputs("mtex2MML version " MTEX2MML_VERSION "\n", stdout);
      bStop = true;
      break;
    }

    if (args == "--help" || args == "-h") {
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

      bStop = true;
      break;
    }
    if (args == "--print-mtex") {
      bPrintMtex = true;
      bRawFilter = false;
      continue;
    }
    if (args == "--forbid-markup") {
      bRawFilter = false;
      bForbidMarkup = true;
      continue;
    }
    if (args == "--inline") {
      bRawFilter = false;
      bInline    = true;
      bDisplay   = false;
      continue;
    }
    if (args == "--display") {
      bRawFilter = false;
      bInline    = false;
      bDisplay   = true;
      continue;
    }
    if (args == "--raw-filter") {
      bRawFilter = true;
      bPrintMtex = false;
      bInline    = false;
      bDisplay   = false;
      continue;
    }
  }
  if (bStop) { return 0; }

  std::string mtex;

  if (bInline) { mtex += "$"; }
  if (bDisplay) { mtex += "$$"; }

#define BUFSIZE 1024
  char buffer[BUFSIZE];
  while (fgets (buffer, BUFSIZE, stdin)) { mtex += buffer; }

  if (bInline) { mtex += "$"; }
  if (bDisplay) { mtex += "$$"; }

  if (bPrintMtex) {
    fputs (mtex.c_str (), stdout);
    fputs ("\n", stdout);
    fflush (stdout);
  }

  if (!bInline && !bDisplay) {
    if (bRawFilter) {
      mtex2MML_filter (mtex.c_str(), mtex.size());
    } else if (bForbidMarkup) {
      mtex2MML_strict_html_filter (mtex.c_str(), mtex.size());
    } else {
      mtex2MML_html_filter (mtex.c_str(), mtex.size());
    }
    return 0;
  }

  char * mathml = mtex2MML_parse (mtex.c_str(), mtex.size());

  if (mathml) {
    fputs (mathml, stdout);
    fputs ("\n", stdout);

    mtex2MML_free_string (mathml);
    mathml = 0;
  } else {
    fputs ("mtex2MML: mtex parser failed to generate MathML from mtex!\n", stderr);
  }
  return 0;
}
