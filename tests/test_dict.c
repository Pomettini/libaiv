#include "test.h"

#include <aiv/dict.h>

int test_dict_new()
{
    aiv_dict_t *dict = aiv_dict_new(1, NULL);
    if (!dict)
        return -1;

    return 0;
}

int test_dict_new_zero_hash_map_size()
{
    int err;
    aiv_dict_t *dict = aiv_dict_new(0, &err);
    if (!dict)
        return err;

    return -1;
}

int test_dict_add()
{

    aiv_dict_t *dict = aiv_dict_new(10, NULL);
    if (!dict)
        return -1;

    const char *foo = "hello";
    aiv_dict_add(dict, (void *)foo, strlen(foo), "bo");

    const char *foo2 = "ciao";
    aiv_dict_add(dict, (void *)foo2, strlen(foo2), "bo");

    const char *foo3 = "hello_world";
    aiv_dict_add(dict, (void *)foo3, strlen(foo3), "bo");

    return 0;
}

int test_dict_get()
{

    aiv_dict_t *dict = aiv_dict_new(10, NULL);
    if (!dict)
        return -1;

    const char *foo = "hello";
    aiv_dict_add(dict, (void *)foo, strlen(foo), "bo");

    void *data = aiv_dict_get(dict, "hello", 5);

    return 0;
}

void test_dict_run()
{
    test(test_dict_new);
    test_equal(test_dict_new_zero_hash_map_size, AIV_INVALID_SIZE);
    test(test_dict_add);
}