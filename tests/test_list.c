#include <aiv/list.h>
#include <stdio.h>
#include <aiv/error.h>

#define test(x) if (x())                                                                                     \
    {                                                                                                        \
        fprintf(stderr, "test failed while running function " #x "() at address %p line %d\n", x, __LINE__); \
        exit(1);                                                                                             \
    \
}\

#define test_equal(x, y) {\
        int ret = x();\
        if (ret != y)\
        {\
            fprintf(stderr, "test failed while running function " #x "() at address %p line %d, expecting %d got %d\n", x, __LINE__, y, ret);\
            exit(1);\
        }\
    }

int test_aiv_list_new()
{
    struct aiv_list *list = aiv_list_new(NULL);
    if (!list)
        return -1;

    aiv_list_destroy(list);
    return 0;
}

int test_aiv_list_append()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if (!list)
        return -1;

    int element = 5;

    int ret = aiv_list_append(list, &element);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_append_null()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if (!list)
        return -1;

    int ret = aiv_list_append(list, NULL);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_empty()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;
    
    int ret = aiv_list_remove(list, NULL);
    aiv_list_destroy(list);
    return ret;
}


int test_aiv_list_remove()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    int ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }
    ret = aiv_list_remove(list, &a);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_two()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    const char* c = "ciao";
    int ret = 0;

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_append(list, (void *)c);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, (void *)c);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_non_exsistent()
{
    struct aiv_list *list = aiv_list_new(NULL);

    if(!list)
        return -1;

    int a = 3;
    const char* c = "ciao";
    int ret = 0;

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove(list, (void *)c);
    aiv_list_destroy(list);
    return ret;
}

int main(int argc, char **argv)
{
    test(test_aiv_list_new);
    test(test_aiv_list_append);
    test(test_aiv_list_append_null);
    test_equal(test_aiv_list_remove_empty, AIV_NOT_FOUND);
    test(test_aiv_list_remove);
    test(test_aiv_list_remove_two);
    test_equal(test_aiv_list_remove_non_exsistent, AIV_NOT_FOUND);
    

    fprintf(stdout, "all tests passed\n");
    return 0;
}