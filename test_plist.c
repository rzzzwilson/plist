/*
 *  Test the plist code.
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "plist.h"

/*
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
    return 0;
}

/*
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
    return 0;
}

/*
 * Simple test of PlistCreate/Destroy().
 */
void test_create(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();

    CU_ASSERT(my_plist != NULL);
}

/*
 * Simple test of PlistDestroy().
 */
void test_destroy(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();

    CU_ASSERT(my_plist != NULL);

    PlistDestroy(my_plist);

    CU_ASSERT(my_plist != NULL);
}

/*
 * More complicated test of PListDestroy().
 */
void test_destroy2(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();
    CU_ASSERT(my_plist != NULL);

    PListInsert(my_plist, "abc", "abc-value");
    PListInsert(my_plist, "abc", "abc2-value");
    PListInsert(my_plist, "abc", "abc3-value");

    my_plist = PlistDestroy(my_plist);
    CU_ASSERT(NULL == my_plist);
}

/*
 * Simple test of PListInsert().
 */
void test_insert1(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();

    CU_ASSERT(my_plist != NULL);

    PListInsert(my_plist, "abc", "abc-value");
}

/*
 * Simple test of PListFind() finding an entry.
 */
void test_find1(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();
    CU_ASSERT(my_plist != NULL);

    PListInsert(my_plist, "abc", "abc-value");

    char *value = NULL;
    value = PlistFind(my_plist, "abc");
    CU_ASSERT(value != NULL);
}

/*
 * Simple test of PListFind() NOT finding an entry.
 */
void test_find2(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();
    CU_ASSERT(my_plist != NULL);

    PListInsert(my_plist, "abc", "abc-value");

    char *value = NULL;
    value = PlistFind(my_plist, "xyz");
    CU_ASSERT(value == NULL);
}

/*
 * Simple test of PListFind() finding first of multiple entries.
 */
void test_find3(void)
{
    PLIST my_plist = NULL;

    my_plist = PlistCreate();
    CU_ASSERT(my_plist != NULL);

    PListInsert(my_plist, "abc", "abc-value");
    PListInsert(my_plist, "abc", "abc2-value");
    PListInsert(my_plist, "abc", "abc3-value");

    char *value = NULL;
    value = PlistFind(my_plist, "abc");
    CU_ASSERT(value != NULL);
    CU_ASSERT(strcmp(value, "abc3-value") == 0);
#ifdef DEBUG
    PlistDump(my_plist, NULL);
#endif
}

/*
 * The main() function for setting up and running the tests.
 * Returns CUE_SUCCESS on successful running, other CUnit error code on failure.
 */
int main()
{
    CU_pSuite create_suite = NULL;
    CU_pSuite insert_suite = NULL;
    CU_pSuite find_suite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    create_suite = CU_add_suite("Creation/Destruction", init_suite, clean_suite);
    if (NULL == create_suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(create_suite, "test PlistCreate", test_create)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(create_suite, "test PlistDestroy", test_destroy)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(create_suite, "test PlistDestroy", test_destroy2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    insert_suite = CU_add_suite("Check PListInsert", init_suite, clean_suite);
    if (NULL == insert_suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(insert_suite, "test PlistInsert", test_insert1)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add a suite to the registry */
    find_suite = CU_add_suite("Check PListFind", init_suite, clean_suite);
    if (NULL == find_suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(find_suite, "test PlistFind finding", test_find1)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(find_suite, "test PlistFind finding", test_find1)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(find_suite, "test PlistFind multiple", test_find3)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
