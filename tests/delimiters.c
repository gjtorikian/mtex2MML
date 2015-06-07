#include "clar.h"
#include "clar_test.h"
#include "deps/trim/trim.h"
#include <stdio.h>
#include <string.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_delimiters__initialize(void)
{
  global_test_counter++;
}

void test_delimiters__cleanup(void)
{
  if (fixture_mml != NULL) {
    free(fixture_mml);
  }

  if (result != NULL) {
    free(result);
  }
}

void test_delimiters__single_dollar(void)
{
  fixture_tex = "$\\pi$";
  fixture_mml = read_fixture_mml("delimiters/single_dollar.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__double_dollar(void)
{
  fixture_tex = "$$\\pi$$";
  fixture_mml = read_fixture_mml("delimiters/double_dollar.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__parens(void)
{
  fixture_tex = "\\(\\pi\\)";
  fixture_mml = read_fixture_mml("delimiters/parens.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__brackets(void)
{
  fixture_tex = "\\[\\pi\\]";
  fixture_mml = read_fixture_mml("delimiters/brackets.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__imbalanced_dollar(void)
{
  fixture_tex = "$\\pi$$";
  fixture_mml = read_fixture_mml("delimiters/double_dollar.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}
