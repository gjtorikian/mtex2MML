#include <cstdio>
#include <stdlib.h>
#include <string>

#include "mtex2MML.h"

int main (int argc, char ** argv)
{
  char *buffer = 0;
  long length;
  FILE * f = fopen ("file.test", "rb");

  if (f)
  {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = new char[length];
    if (buffer)
    {
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }

  char * mathml = mtex2MML_parse (buffer, length);

  if (mathml)
  {
    fputs (mathml, stdout);
    fputs ("\n", stdout);

    mtex2MML_free_string (mathml);
    mathml = 0;
  }
  else
  {
    fputs ("mtex2MML: mtex parser failed to generate MathML from mtex!\n", stderr);
  }
  return 0;
}
