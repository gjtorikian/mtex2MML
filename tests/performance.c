#include "clar.h"
#include "clar_test.h"
#include "deps/trim/trim.h"
#include <stdio.h>
#include <string.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_performance__initialize(void)
{
  global_test_counter++;
}

void test_performance__cleanup(void)
{
  if (fixture_tex != NULL) {
    free(fixture_tex);
  }

  if (fixture_mml != NULL) {
    free(fixture_mml);
  }

  if (result != NULL) {
    free(result);
  }
}

void test_performance__big_file(void)
{
  fixture_tex = read_fixture_tex("performance/big_file.txt");
  fixture_mml = read_fixture_mml("performance/big_file.html");
  mtex2MML_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, result);
}
