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

void test_delimiters__single_dollar(void)
{
  fixture_tex = "$\\pi$";
  fixture_mml = read_fixture_mml("delimiters/single_dollar.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__double_dollar(void)
{
  fixture_tex = "$$\\pi$$";
  fixture_mml = read_fixture_mml("delimiters/double_dollar.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__parens(void)
{
  fixture_tex = "\\(\\pi\\)";
  fixture_mml = read_fixture_mml("delimiters/parens.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_PARENS);

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__brackets(void)
{
  fixture_tex = "\\[\\pi\\]";
  fixture_mml = read_fixture_mml("delimiters/brackets.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_BRACKETS);

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__mixed(void)
{
  fixture_tex = "\\[\\alpha\\] $$\\beta$$";
  fixture_mml = read_fixture_mml("delimiters/mixed.html");
  mtex2MML_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DOUBLE | MTEX2MML_DELIMITER_PARENS | MTEX2MML_DELIMITER_BRACKETS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, result);
}

void test_delimiters__dollar_spacings_with_text_filter(void)
{
  fixture_tex = read_fixture_tex("delimiters/dollar_spacings_text_filter.txt");
  fixture_mml = read_fixture_mml("delimiters/dollar_spacings_text_filter.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__dollar_spacings_with_filter(void)
{
  fixture_tex = read_fixture_tex("delimiters/dollar_spacings_filter.txt");
  fixture_mml = read_fixture_mml("delimiters/dollar_spacings_filter.html");
  mtex2MML_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__escaping_with_dollars(void)
{
  fixture_tex = read_fixture_tex("delimiters/escaping.txt");
  fixture_mml = read_fixture_mml("delimiters/escaping_with_dollars.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DEFAULT);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__escaping_with_brackets(void)
{
  fixture_tex = read_fixture_tex("delimiters/escaping.txt");
  fixture_mml = read_fixture_mml("delimiters/escaping_with_brackets.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_BRACKETS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__escaping_with_parens(void)
{
  fixture_tex = read_fixture_tex("delimiters/escaping.txt");
  fixture_mml = read_fixture_mml("delimiters/escaping_with_parens.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_PARENS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__parse_environment_align(void)
{
  fixture_tex = read_fixture_tex("delimiters/align.txt");
  fixture_mml = read_fixture_mml("delimiters/align.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);

  cl_assert_equal_s(fixture_mml, trim(result));
}

void test_delimiters__filter_environment_align(void)
{
  fixture_tex = read_fixture_tex("delimiters/align.txt");
  fixture_mml = read_fixture_mml("delimiters/align.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__parse_environment_basic_array(void)
{
  fixture_tex = read_fixture_tex("delimiters/basic_array.txt");
  fixture_mml = read_fixture_mml("delimiters/basic_array.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);

  cl_assert_equal_s(fixture_mml, trim(result));
}

void test_delimiters__filter_environment_basic_array(void)
{
  fixture_tex = read_fixture_tex("delimiters/basic_array.txt");
  fixture_mml = read_fixture_mml("delimiters/basic_array.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__parse_environment_aligned_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("delimiters/aligned_ex_spacing.txt");
  fixture_mml = read_fixture_mml("delimiters/aligned_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);

  cl_assert_equal_s(fixture_mml, trim(result));
}

void test_delimiters__filter_environment_aligned_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("delimiters/aligned_ex_spacing.txt");
  fixture_mml = read_fixture_mml("delimiters/aligned_ex_spacing.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__parse_environment_alignat_1a_spacing(void)
{
  fixture_tex = read_fixture_tex("delimiters/alignat-1a.txt");
  fixture_mml = read_fixture_mml("delimiters/alignat-1a.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);

  cl_assert_equal_s(fixture_mml, trim(result));
}

void test_delimiters__filter_environment_alignat_1a_spacing(void)
{
  fixture_tex = read_fixture_tex("delimiters/alignat-1a.txt");
  fixture_mml = read_fixture_mml("delimiters/alignat-1a.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_ENVIRONMENTS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}

void test_delimiters__filter_mixed_environment(void)
{
  fixture_tex = read_fixture_tex("delimiters/mixed_env.txt");
  fixture_mml = read_fixture_mml("delimiters/mixed_env.html");
  mtex2MML_text_filter(fixture_tex, strlen(fixture_tex), MTEX2MML_DELIMITER_DOUBLE | MTEX2MML_DELIMITER_ENVIRONMENTS);
  result = mtex2MML_output();

  cl_assert_equal_s(fixture_mml, trim(result));
  free(fixture_tex);
}
