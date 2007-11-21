/*             itex2MML 1.3.3
 *   itex2MML.cc last modified 11/21/2007
 */

#include <cstdio>

#include <string>

#include "itex2MML.h"

int main (int argc, char ** argv)
{
	bool bPrintItex = false;
	bool bRawFilter = false;
	bool bInline    = false;
	bool bDisplay   = false;

	bool bStop = false;
	bool bForbidMarkup = false;

	for (int arg = 1; arg < argc; arg++)
		{
			std::string args = argv[arg];

			if (args == "--version" || args == "-v")
				{
					fputs("itex2MML version " ITEX2MML_VERSION "\n"
					      "See http://golem.ph.utexas.edu/~distler/blog/itex2MML.html for more information.\n", stdout);
					bStop = true;
					break;
				}

			if (args == "--help" || args == "-h")
				{
					fputs ("usage: itex2MML [OPTIONS]\n"
						   "\n"
						   "itex2MML filters an input text stream (e.g., an XHTML web page) converting itex expressions\n"
						   "to MathML. Inline itex expressions are delimited either side by single dollar symbols ($):\n"
						   "\n"
						   "\t<p>The parameters $\\alpha$ and $\\beta$ in the function $f(x)$ are defined below.</p>\n"
						   "\n"
						   "For normal display of equations, etc., itex expressions can be delimited with double dollar\n"
						   "symbols ($$) either side or by \\[ to the left and \\] to the right:\n"
						   "\n"
						   "\t<p class=\"equation\">\\[\n"
						   "\t\tf(x) = \\alpha x + \\frac{\\beta}{1+|x|}\n"
						   "\t\\]</p>\n"
						   "\n"
						   "itex2MML Options:\n"
						   "\n"
						   "  --raw-filter    filter input stream, converting equations as found to MathML [stops on error]\n"
						   "  --inline        converts a single itex equation, without any $ symbols, to inline MathML\n"
						   "  --display       converts a single itex equation, without any $ symbols, to display-mode MathML\n"
						   "  --forbid-markup forbid markup (more precisely, the '<' and '>' characters) in itex equations\n"
						   "  --print-itex    used in conjuction with --inline or --display: prints the itex string\n"
						   "\n"
						   "For further information, see http://golem.ph.utexas.edu/~distler/blog/itex2MML.html\n", stdout);

					bStop = true;
					break;
				}
			if (args == "--print-itex")
				{
					bPrintItex = true;
					bRawFilter = false;
					continue;
				}
			if (args == "--forbid-markup")
				{
					bRawFilter = false;
					bForbidMarkup = true;
					continue;
				}
			if (args == "--inline")
				{
					bRawFilter = false;
					bInline    = true;
					bDisplay   = false;
					continue;
				}
			if (args == "--display")
				{
					bRawFilter = false;
					bInline    = false;
					bDisplay   = true;
					continue;
				}
			if (args == "--raw-filter")
				{
					bRawFilter = true;
					bPrintItex = false;
					bInline    = false;
					bDisplay   = false;
					continue;
				}
		}
	if (bStop) return 0;

	std::string itex;

	if (bInline)  itex += "$";
	if (bDisplay) itex += "$$";

#define BUFSIZE 1024
	char buffer[BUFSIZE];
	while (fgets (buffer, BUFSIZE, stdin)) itex += buffer;

	if (bInline)  itex += "$";
	if (bDisplay) itex += "$$";

	if (bPrintItex)
		{
			fputs (itex.c_str (), stdout);
			fputs ("\n", stdout);
			fflush (stdout);
		}

	if (!bInline && !bDisplay)
		{
			if (bRawFilter)
				itex2MML_filter (itex.c_str(), itex.size());
			else
				if (bForbidMarkup)
					itex2MML_strict_html_filter (itex.c_str(), itex.size());
				else
					itex2MML_html_filter (itex.c_str(), itex.size());
			return 0;
		}

	char * mathml = itex2MML_parse (itex.c_str(), itex.size());

	if (mathml)
		{
			fputs (mathml, stdout);
			fputs ("\n", stdout);

			itex2MML_free_string (mathml);
			mathml = 0;
		}
	else
		{
			fputs ("itex2MML: itex parser failed to generate MathML from itex!\n", stderr);
		}
	return 0;
}
