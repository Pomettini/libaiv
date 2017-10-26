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

int test_aiv_list_remove_index_empty()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
        if(!list)
            return -1;

    int ret = aiv_list_remove_index(list, 100);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_index()
{
    struct aiv_list *list = aiv_list_new(NULL);
    
        if(!list)
            return -1;

    int ret = 0;
    int a = 768;

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove_index(list, 0);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_remove_index_two()
{
    struct aiv_list *list = aiv_list_new(NULL);
    if(!list)
        return -1;

    int ret = 0;
    int a = 768;
    const char* c = "hello";

    ret = aiv_list_append(list, (void*)c);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove_index(list, 0);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    ret = aiv_list_remove_index(list, 0);
    aiv_list_destroy(list);
    return ret;
}

int test_aiv_list_iter()
{   

    struct aiv_list *list = aiv_list_new(NULL);
    if(!list)
        return -1;

    struct aiv_list_item *context = NULL;
    struct aiv_list_item *item = NULL;
    int counter = 0;

    int a = 345;

    int ret = aiv_list_append(list, &a);
    if(ret)
    {
        aiv_list_destroy(list);
        return ret;
    }

    while((item = aiv_list_iter(list, &context)))
    {
        counter++;
    }

    aiv_list_destroy(list);
    return counter;
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
    test_equal(test_aiv_list_remove_index_empty, AIV_NOT_FOUND);
    test(test_aiv_list_remove_index);
    test(test_aiv_list_remove_index_two);
    test_equal(test_aiv_list_iter, 1);

    fprintf(stdout, "all tests passed\n");
    return 0;
}