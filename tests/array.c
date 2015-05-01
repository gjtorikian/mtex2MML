#include "clar.h"
#include "clar_test.h"
#include <stdio.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_array__initialize(void)
{
  global_test_counter++;
}

void test_array__cleanup(void)
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

void test_array__basic_array(void)
{
  fixture_tex = read_fixture_tex("array/basic_array.text");
  fixture_mml = read_fixture_mml("array/basic_array.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_with_hline(void)
{
  fixture_tex = read_fixture_tex("array/array_with_hline.text");
  fixture_mml = read_fixture_mml("array/array_with_hline.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_with_hline_and_hdashline(void)
{
  fixture_tex = read_fixture_tex("array/array_with_hline_and_hdashline.text");
  fixture_mml = read_fixture_mml("array/array_with_hline_and_hdashline.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_pos_alignment(void)
{
  fixture_tex = read_fixture_tex("array/array_pos_alignment.text");
  fixture_mml = read_fixture_mml("array/array_pos_alignment.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_pos_alignment_with_hline(void)
{
  fixture_tex = read_fixture_tex("array/array_pos_alignment_with_hline.text");
  fixture_mml = read_fixture_mml("array/array_pos_alignment_with_hline.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_vertical_column(void)
{
  fixture_tex = read_fixture_tex("array/array_vertical_column.text");
  fixture_mml = read_fixture_mml("array/array_vertical_column.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_vertical_column_with_align(void)
{
  fixture_tex = read_fixture_tex("array/array_vertical_column_with_align.text");
  fixture_mml = read_fixture_mml("array/array_vertical_column_with_align.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_with_vertical_and_horizontal_dashes(void)
{
  fixture_tex = read_fixture_tex("array/array_with_vertical_and_horizontal_dashes.text");
  fixture_mml = read_fixture_mml("array/array_with_vertical_and_horizontal_dashes.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__array_nesting(void)
{
  fixture_tex = read_fixture_tex("array/array_nesting.text");
  fixture_mml = read_fixture_mml("array/array_nesting.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__strip_excess_whitespace_in_array_attributes(void)
{
  fixture_tex = read_fixture_tex("array/strip_excess_whitespace_in_array_attributes.text");
  fixture_mml = read_fixture_mml("array/strip_excess_whitespace_in_array_attributes.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_array__augmented_matrix(void)
{
  fixture_tex = read_fixture_tex("array/augmented_matrix.text");
  fixture_mml = read_fixture_mml("array/augmented_matrix.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}
