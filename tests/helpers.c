#include "deps/file2str/file2str.h"
#include "clar.h"
#include <stdio.h>
#include <string.h>

char * read_fixture_tex(char *filename)
{
  return file2str(cl_fixture(filename));
}

char * read_fixture_mml(char *filename)
{
  char * answer = file2str(cl_fixture(filename));

  answer[strlen(answer)-1] = 0; // remove extra newline

  return answer;
}

void write_test_file(char * data)
{
  FILE *fp = fopen(cl_fixture("../test.html"), "w+");
  if (fp != NULL) {
    fputs(data, fp);
    fclose(fp);
  }
}
