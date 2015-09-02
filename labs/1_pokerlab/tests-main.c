

/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "CuTest.h"


extern void test_hand_to_string (CuTest*);
extern void test_string_to_hand (CuTest*);
extern void test_sort_hand (CuTest*);
extern void test_is_onepair (CuTest*);
extern void test_is_twopairs (CuTest*);
extern void test_is_threeofakind (CuTest*);
extern void test_is_straight (CuTest*);
extern void test_is_fullhouse (CuTest*);
extern void test_is_flush (CuTest*);
extern void test_is_straightflush (CuTest*);
extern void test_is_fourofakind (CuTest*);
extern void test_is_royalflush (CuTest*);
extern void test_compare_hands (CuTest*);
extern void test_compare_highcards (CuTest*);


void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();


    SUITE_ADD_TEST(suite, test_hand_to_string );
    SUITE_ADD_TEST(suite, test_string_to_hand );
    SUITE_ADD_TEST(suite, test_sort_hand );
    SUITE_ADD_TEST(suite, test_is_onepair );
    SUITE_ADD_TEST(suite, test_is_twopairs );
    SUITE_ADD_TEST(suite, test_is_threeofakind );
    SUITE_ADD_TEST(suite, test_is_straight );
    SUITE_ADD_TEST(suite, test_is_fullhouse );
    SUITE_ADD_TEST(suite, test_is_flush );
    SUITE_ADD_TEST(suite, test_is_straightflush );
    SUITE_ADD_TEST(suite, test_is_fourofakind );
    SUITE_ADD_TEST(suite, test_is_royalflush );
    SUITE_ADD_TEST(suite, test_compare_hands );
    SUITE_ADD_TEST(suite, test_compare_highcards );

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void)
{
    RunAllTests();
    return 0;
}

