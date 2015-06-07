#include "clar.h"
#include "clar_test.h"
#include <stdio.h>
#include <string.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_env__initialize(void)
{
  global_test_counter++;
}

void test_env__cleanup(void)
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

void test_env__matrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/matrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/matrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__matrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/matrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/matrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__matrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/matrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/matrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__pmatrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/pmatrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/pmatrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__pmatrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/pmatrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/pmatrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__pmatrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/pmatrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/pmatrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__bmatrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/bmatrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/bmatrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__bmatrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/bmatrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/bmatrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__bmatrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/bmatrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/bmatrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__bbmatrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/bbmatrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/bbmatrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__bbmatrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/bbmatrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/bbmatrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__bbmatrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/bbmatrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/bbmatrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__vmatrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/vmatrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/vmatrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__vmatrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/vmatrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/vmatrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__vmatrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/vmatrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/vmatrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__vvmatrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/vvmatrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/vvmatrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__vvmatrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/vvmatrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/vvmatrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__vvmatrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/vvmatrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/vvmatrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__smallmatrix_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/smallmatrix_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/smallmatrix_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__smallmatrix_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/smallmatrix_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/smallmatrix_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__smallmatrix_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/smallmatrix_no_lines.txt");
  fixture_mml = read_fixture_mml("env/smallmatrix_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__aligned_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/aligned_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/aligned_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__aligned_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/aligned_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/aligned_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__aligned_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/aligned_no_lines.txt");
  fixture_mml = read_fixture_mml("env/aligned_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__gathered_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/gathered_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/gathered_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__gathered_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/gathered_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/gathered_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__gathered_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/gathered_no_lines.txt");
  fixture_mml = read_fixture_mml("env/gathered_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__split_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/split_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/split_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__split_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/split_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/split_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__split_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/split_no_lines.txt");
  fixture_mml = read_fixture_mml("env/split_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__spaces_after_rowsep(void)
{
  fixture_tex = read_fixture_tex("env/spaces_after_rowsep.txt");
  fixture_mml = read_fixture_mml("env/spaces_after_rowsep.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__cases_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/cases_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/cases_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__cases_no_ex_spacing(void)
{
  fixture_tex = read_fixture_tex("env/cases_no_ex_spacing.txt");
  fixture_mml = read_fixture_mml("env/cases_no_ex_spacing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

void test_env__cases_no_lines(void)
{
  fixture_tex = read_fixture_tex("env/cases_no_lines.txt");
  fixture_mml = read_fixture_mml("env/cases_no_lines.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}
