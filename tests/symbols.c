#include "clar.h"
#include "clar_test.h"
#include "deps/trim/trim.h"
#include <stdio.h>
#include <string.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_symbols__initialize(void)
{
  global_test_counter++;
}

void test_symbols__cleanup(void)
{
  if (fixture_mml != NULL) {
    free(fixture_mml);
  }

  if (result != NULL) {
    free(result);
  }
}

void test_symbols__textgreater(void)
{
  fixture_tex = read_fixture_tex("symbols/textgreater.txt");
  fixture_mml = read_fixture_mml("symbols/textgreater.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DOLLAR);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_symbols__textless(void)
{
  fixture_tex = read_fixture_tex("symbols/textless.txt");
  fixture_mml = read_fixture_mml("symbols/textless.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DOLLAR);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}
