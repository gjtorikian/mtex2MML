#include "clar.h"
#include "clar_test.h"
#include <stdio.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;
static char *huge;

void test_maliciousness__initialize(void)
{
  global_test_counter++;
}

void test_maliciousness__cleanup(void)
{
  if (fixture_tex != NULL)
    free(fixture_tex);

  if (fixture_mml != NULL)
    free(fixture_mml);

  if (result != NULL)
    free(result);
}

void test_maliciousness__parsing(void)
{
  fixture_tex = read_fixture_tex("maliciousness/just_enough_parsing.txt");
  fixture_mml = read_fixture_mml("maliciousness/just_enough_parsing.html");
  result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));

  cl_assert_equal_s(fixture_mml, result);
}

// void test_maliciousness__excess_parsing(void)
// {
//   fixture_tex = read_fixture_tex("maliciousness/excess_parsing.txt");
//   fixture_mml =  read_fixture_mml("maliciousness/just_enough_parsing.html");
//   result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));
//
//   cl_must_fail(mtex2MML_parse(fixture_tex, strlen(fixture_tex)));
// }

// void test_maliciousness__unknown_command(void)
// {
//   fixture_tex = read_fixture_tex("maliciousness/just_enough_parsing.txt");
//   fixture_mml = read_fixture_mml("maliciousness/just_enough_parsing.html");
//
//   char *s = "$\not__thisisnotreal$";
//   result = mtex2MML_parse(s, strlen(s));
//
//   cl_assert(result == NULL);
// }
