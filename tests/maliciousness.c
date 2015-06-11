#include "clar.h"
#include "clar_test.h"
#include <stdio.h>
#include <string.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_maliciousness__initialize(void)
{
  global_test_counter++;
}

void test_maliciousness__cleanup(void)
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

void test_maliciousness__parsing(void)
{
  fixture_tex = read_fixture_tex("maliciousness/just_enough_parsing.txt");
  fixture_mml = read_fixture_mml("maliciousness/just_enough_parsing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), 0);

  cl_assert_equal_s(fixture_mml, result);
}

void test_maliciousness__excess_parsing(void)
{
  fixture_tex = read_fixture_tex("maliciousness/excess_parsing.txt");
  fixture_mml =  read_fixture_mml("maliciousness/just_enough_parsing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex), 0);

  cl_assert(result == NULL);
}

void test_maliciousness__unknown_command_with_parse(void)
{
  /* lazy way to continue with the free in cleanup */
  fixture_tex = malloc(1);
  fixture_mml = malloc(1);

  char *s1 = "$\\not__thisisnotreal$";
  result = mtex2MML_parse(s1, strlen(s1), 0);
  cl_assert(result == NULL);
  free(result);

  char *s2 = "$x$";
  result = mtex2MML_parse(s2, strlen(s2), 0);
  cl_assert(result != NULL);
}

void test_maliciousness__unknown_command_with_filter(void)
{
  /* lazy way to continue with the free in cleanup */
  fixture_tex = malloc(1);
  fixture_mml = malloc(1);

  char *s1 = "$\\not__thisisnotreal$";
  int status1 = mtex2MML_filter(s1, strlen(s1), 0);
  result = mtex2MML_output();
  cl_assert(status1 == 1);
  cl_assert(strlen(result) == 0);
  free(result);

  char *s2 = "$x$";
  int status2 = mtex2MML_filter(s2, strlen(s2), 0);
  result = mtex2MML_output();
  cl_assert(status2 == 0);
  cl_assert(strlen(result) > 0);
}

void test_maliciousness__bad_options(void)
{
  /* lazy way to continue with the free in cleanup */
  fixture_tex = malloc(1);
  fixture_mml = malloc(1);

  char *s1 = "$\\pi";
  int status = mtex2MML_filter(s1, strlen(s1), 9000);
  result = mtex2MML_output();
  cl_assert(status == 0);
  cl_assert(strlen(result) == 0);
}
