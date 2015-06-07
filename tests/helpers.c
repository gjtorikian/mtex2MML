#include "helpers.h"
#include "deps/file2str/file2str.h"
#include "deps/trim/trim.h"
#include "clar.h"
#include <stdio.h>
#include <string.h>

char * read_fixture_tex(const char *filename)
{
  const char *tex = cl_fixture(filename);
  return file2str(tex);
}

char * read_fixture_mml(const char *filename)
{
  const char *mml = cl_fixture(filename);
  char * data = file2str(mml);

  return trim(data);
}

void write_test_file(char * data)
{
  FILE *fp = fopen(cl_fixture("../test.html"), "w+");
  if (fp != NULL) {
    fputs(data, fp);
    fclose(fp);
  }
}
