#include "clar.h"
#include "clar_test.h"
#include <stdio.h>
#include <string.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_functions__initialize(void)
{
  global_test_counter++;
}

void test_functions__cleanup(void)
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

void test_functions__max_limits(void)
{
  fixture_tex = read_fixture_tex("functions/max_limits.txt");
  fixture_mml = read_fixture_mml("functions/max_limits.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);

  cl_assert_equal_s(fixture_mml, result);
}

void test_functions__min_limits(void)
{
  fixture_tex = read_fixture_tex("functions/min_limits.txt");
  fixture_mml = read_fixture_mml("functions/min_limits.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);

  cl_assert_equal_s(fixture_mml, result);
}

void test_functions__prod_limits(void)
{
  fixture_tex = read_fixture_tex("functions/prod_limits.txt");
  fixture_mml = read_fixture_mml("functions/prod_limits.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);

  cl_assert_equal_s(fixture_mml, result);
}
