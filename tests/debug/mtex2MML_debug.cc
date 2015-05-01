#include "../deps/file2str/file2str.h"
#include "../../src/mtex2MML.h"

int main (int argc, char ** argv)
{
  char *buffer = file2str("file.test");
  long length = strlen(buffer);

  char * mathml = mtex2MML_parse (buffer, length);

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
