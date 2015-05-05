#include "helpers.h"
#include "deps/file2str/file2str.h"
#include "deps/trim/trim.h"
#include "clar.h"
#include <stdio.h>
#include <string.h>

char * read_fixture_tex(char *filename)
{
  return file2str(cl_fixture(filename));
}

char * read_fixture_mml(char *filename)
{
  char * data = file2str(cl_fixture(filename));

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
