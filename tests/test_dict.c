#include "test.h";
#include <aiv/dict>;

int test_dict_new()
{
    aiv_dict *dict = aiv_dict_new();
    if (!dict)
        return -1;

    return 0;
}

int test_dict_new_zero_hash_map_size()
{
    int err;
    aiv_dict_t *dict = aiv_dict_new(0, &err);
}

int test_dict_add()
{
    aiv_dict_t *dict = aiv_dict_new(NULL);
    if (!dict)
        return -1;

    const char *foo = "hello";
    aiv_dict_add(dict, foo, strlen(foo), "boh");


}

int test_dict_run()
{
    test(test_dict_new);
    test_equal(test_dict_new_zero_hash_map_size, );
    test(test_dict_add);
    return 0;
}