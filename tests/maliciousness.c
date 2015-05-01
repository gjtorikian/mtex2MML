#include "clar.h"
#include "clar_test.h"
#include <stdio.h>

static char *fixture_tex;
static char *fixture_mml;
static char *result;

void test_maliciousness__initialize(void)
{
  global_test_counter++;
}

void test_maliciousness__cleanup(void)
{
  // if (fixture_tex != NULL)
  //   free(fixture_tex);
  //
  // if (fixture_mml != NULL)
  //   free(fixture_mml);
  //
  // if (result != NULL)
  //   free(result);
}

// void test_maliciousness__chained_monstrosity(void)
// {
//   fixture_tex = read_fixture_tex("maliciousness/chained_monstrosity.text");
//   fixture_mml = read_fixture_mml("maliciousness/chained_monstrosity.html");
//   result = mtex2MML_parse(fixture_tex, strlen(fixture_tex));
//
//   cl_assert_equal_s(fixture_mml, result);
// }

// void test_maliciousness__unknown_command(void)
// {
//   result = "$\not__thisisnotreal$";
//   result = mtex2MML_parse(result, strlen(result));
//
//   cl_assert(result == NULL);
// }
