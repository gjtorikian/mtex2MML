/* adding.c for the "Adding" suite */
#include "clar.h"
#include "../src/mtex2MML.h"
#include <stdio.h>

static int *answer;

void test_basic__initialize(void)
{
    answer = malloc(sizeof(int));
    cl_assert_(answer != NULL, "No memory left?");
    *answer = 42;
}

void test_basic__cleanup(void)
{
    free(answer);
}

void test_basic__make_sure_math_still_works(void)
{
    char * x = mtex2MML_parse("$x$", 3);
    printf("%s", x);

    cl_assert_(5 > 3, "Five should probably be greater than three");
    cl_assert_(-5 < 2, "Negative numbers are small, I think");
    cl_assert_(*answer == 42, "The universe is doing OK. And the initializer too.");
}
