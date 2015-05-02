#include "clar.h"
#include "clar_test.h"
#include "deps/trim/trim.h"
#include <stdio.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_basic__initialize(void)
{
  global_test_counter++;
}

void test_basic__cleanup(void)
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

void test_basic__inline(void)
{
  fixture_tex = read_fixture_tex("basic/inline.txt");
  fixture_mml = read_fixture_mml("basic/inline.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_basic__block(void)
{
  fixture_tex = read_fixture_tex("basic/block.txt");
  fixture_mml = read_fixture_mml("basic/block.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_basic__comments(void)
{
  fixture_tex = read_fixture_tex("basic/comments.txt");
  fixture_mml = read_fixture_mml("basic/comments.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_basic__filter(void)
{
  fixture_tex = read_fixture_tex("basic/filter.txt");
  fixture_mml = read_fixture_mml("basic/filter.html");
  int status = mtex2MML_filter(fixture_tex, strlen(fixture_tex));
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, result);
}

void test_basic__html_filter(void)
{
  fixture_tex = read_fixture_tex("basic/html_filter.txt");
  fixture_mml = read_fixture_mml("basic/html_filter.html");
  mtex2MML_html_filter(fixture_tex, strlen(fixture_tex));
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
}

void test_basic__strict_html_filter(void)
{
  fixture_tex = read_fixture_tex("basic/strict_html_filter.txt");
  fixture_mml = read_fixture_mml("basic/strict_html_filter.html");
  mtex2MML_strict_html_filter(fixture_tex, strlen(fixture_tex));
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
}
